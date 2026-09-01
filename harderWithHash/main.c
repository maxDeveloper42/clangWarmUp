#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashbook.h"

static void print_menu(void)
{
    printf("\n=== Hash Phonebook ===\n");
    printf("1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Find contact\n");
    printf("4. List all contacts\n");
    printf("5. Save & Exit\n");
    printf("Choice: ");
}

int main(void)
{
    HashTable *ht = ht_load();
    int choice;
    char name[NAME_LEN], phone[PHONE_LEN];

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("Enter name: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';

            printf("Enter phone: ");
            if (!fgets(phone, sizeof(phone), stdin)) break;
            phone[strcspn(phone, "\n")] = '\0';

            ht_add(ht, name, phone);
            printf("Added (load factor: %.2f).\n",
                   (double)ht->count / ht->size);
            break;

        case 2:
            printf("Enter name to delete: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';
            if (ht_delete(ht, name) == 0)
                printf("Deleted.\n");
            else
                printf("Not found.\n");
            break;

        case 3:
            printf("Enter name to find: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';
            Contact *found = ht_find(ht, name);
            if (found)
                printf("Found: %s -> %s\n", found->name, found->phone);
            else
                printf("Not found.\n");
            break;

        case 4:
            ht_list(ht);
            break;

        case 5:
            ht_save(ht);
            ht_destroy(ht);
            printf("Goodbye.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }
}
