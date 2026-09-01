#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashbook.h"

/* djb2 hash: good distribution, fast, simple */
static unsigned long hash_str(const char *str, size_t bucket_count)
{
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash % bucket_count;
}

HashTable* ht_create(void)
{
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->size = INIT_SIZE;
    ht->count = 0;
    ht->buckets = calloc(ht->size, sizeof(Contact *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

static void free_chain(Contact *head)
{
    Contact *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void ht_destroy(HashTable *ht)
{
    if (!ht) return;
    for (size_t i = 0; i < ht->size; i++)
        free_chain(ht->buckets[i]);
    free(ht->buckets);
    free(ht);
}

/* Double the bucket count and rehash every node */
static int ht_resize(HashTable *ht)
{
    size_t old_size = ht->size;
    Contact **old_buckets = ht->buckets;

    size_t new_size = old_size * 2;
    Contact **new_buckets = calloc(new_size, sizeof(Contact *));
    if (!new_buckets) return -1;

    /* Move existing nodes to new buckets — no malloc, just relinking */
    for (size_t i = 0; i < old_size; i++) {
        Contact *curr = old_buckets[i];
        while (curr) {
            Contact *next = curr->next;
            unsigned long h = hash_str(curr->name, new_size);
            curr->next = new_buckets[h];
            new_buckets[h] = curr;
            curr = next;
        }
    }

    free(old_buckets);
    ht->buckets = new_buckets;
    ht->size = new_size;
    return 0;
}

void ht_add(HashTable *ht, const char *name, const char *phone)
{
    /* Load factor > 0.75 ? resize */
    if (ht->count >= ht->size * 0.75) {
        if (ht_resize(ht) != 0) {
            perror("resize failed");
            return;
        }
    }

    unsigned long h = hash_str(name, ht->size);

    /* Check duplicate */
    Contact *curr = ht->buckets[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            strncpy(curr->phone, phone, PHONE_LEN - 1);
            curr->phone[PHONE_LEN - 1] = '\0';
            return;
        }
        curr = curr->next;
    }

    /* Prepend new node */
    Contact *newc = malloc(sizeof(Contact));
    if (!newc) {
        perror("malloc failed");
        return;
    }

    strncpy(newc->name, name, NAME_LEN - 1);
    newc->name[NAME_LEN - 1] = '\0';
    strncpy(newc->phone, phone, PHONE_LEN - 1);
    newc->phone[PHONE_LEN - 1] = '\0';

    newc->next = ht->buckets[h];
    ht->buckets[h] = newc;
    ht->count++;
}

Contact* ht_find(const HashTable *ht, const char *name)
{
    unsigned long h = hash_str(name, ht->size);
    Contact *curr = ht->buckets[h];
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

int ht_delete(HashTable *ht, const char *name)
{
    unsigned long h = hash_str(name, ht->size);
    Contact *curr = ht->buckets[h];
    Contact *prev = NULL;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                ht->buckets[h] = curr->next;
            free(curr);
            ht->count--;
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return -1; /* not found */
}

void ht_list(const HashTable *ht)
{
    if (ht->count == 0) {
        printf("Phonebook is empty.\n");
        return;
    }
    printf("\n%-20s %s     (buckets: %zu, entries: %zu)\n",
           "Name", "Phone", ht->size, ht->count);
    printf("------------------------------------------------\n");

    for (size_t i = 0; i < ht->size; i++) {
        Contact *curr = ht->buckets[i];
        if (!curr) continue;
        printf("[bucket %zu]\n", i);
        while (curr) {
            printf("  %-18s %s\n", curr->name, curr->phone);
            curr = curr->next;
        }
    }
    printf("\n");
}

int ht_save(const HashTable *ht)
{
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    for (size_t i = 0; i < ht->size; i++) {
        Contact *curr = ht->buckets[i];
        while (curr) {
            fprintf(fp, "%s,%s\n", curr->name, curr->phone);
            curr = curr->next;
        }
    }
    fclose(fp);
    printf("Saved to %s\n", FILE_NAME);
    return 0;
}

HashTable* ht_load(void)
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return ht_create();

    HashTable *ht = ht_create();
    if (!ht) return NULL;

    char name[NAME_LEN], phone[PHONE_LEN];
    while (fscanf(fp, "%63[^,],%31[^\n]\n", name, phone) == 2) {
        ht_add(ht, name, phone);
    }
    fclose(fp);
    printf("Loaded from %s\n", FILE_NAME);
    return ht;
}
