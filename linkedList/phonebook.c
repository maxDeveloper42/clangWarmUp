#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

Contact* add_contact(Contact *head, const char *name, const char *phone)
{
    Contact *new_contact = malloc(sizeof(Contact));
    if (!new_contact) {
        perror("malloc failed");
        return head;
    }

    strncpy(new_contact->name, name, NAME_LEN - 1);
    new_contact->name[NAME_LEN - 1] = '\0';
    strncpy(new_contact->phone, phone, PHONE_LEN - 1);
    new_contact->phone[PHONE_LEN - 1] = '\0';

    new_contact->next = head;  /* prepend for simplicity */
    return new_contact;
}

Contact* delete_contact(Contact *head, const char *name)
{
    Contact *curr = head, *prev = NULL;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                head = curr->next;
            free(curr);
            printf("Deleted: %s\n", name);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Contact '%s' not found.\n", name);
    return head;
}

Contact* find_contact(Contact *head, const char *name)
{
    while (head) {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

void list_contacts(const Contact *head)
{
    if (!head) {
        printf("Phonebook is empty.\n");
        return;
    }
    printf("\n%-20s %s\n", "Name", "Phone");
    printf("----------------------------------------\n");
    while (head) {
        printf("%-20s %s\n", head->name, head->phone);
        head = head->next;
    }
    printf("\n");
}

void free_all_contacts(Contact *head)
{
    Contact *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int save_to_file(const Contact *head)
{
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    while (head) {
        fprintf(fp, "%s,%s\n", head->name, head->phone);
        head = head->next;
    }
    fclose(fp);
    printf("Saved to %s\n", FILE_NAME);
    return 0;
}

Contact* load_from_file(void)
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp)
        return NULL;  /* no existing file is okay */

    Contact *head = NULL;
    char name[NAME_LEN], phone[PHONE_LEN];

    while (fscanf(fp, "%63[^,],%31[^\n]\n", name, phone) == 2) {
        head = add_contact(head, name, phone);
    }
    fclose(fp);
    printf("Loaded from %s\n", FILE_NAME);
    return head;
}
