#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

static void print_menu(void)
{
    printf("\n=== Phonebook ===\n");
    printf("1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Find contact\n");
    printf("4. List all contacts\n");
    printf("5. Save & Exit\n");
    printf("Choice: ");
}

int main(void)
{
    Contact *book = load_from_file();
    int choice;
    char name[NAME_LEN], phone[PHONE_LEN];

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  /* clear bad input */
            continue;
        }
        while (getchar() != '\n');      /* consume newline */

        switch (choice) {
        case 1:
            printf("Enter name: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';

            printf("Enter phone: ");
            if (!fgets(phone, sizeof(phone), stdin)) break;
            phone[strcspn(phone, "\n")] = '\0';

            book = add_contact(book, name, phone);
            printf("Added.\n");
            break;

        case 2:
            printf("Enter name to delete: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';
            book = delete_contact(book, name);
            break;

        case 3:
            printf("Enter name to find: ");
            if (!fgets(name, sizeof(name), stdin)) break;
            name[strcspn(name, "\n")] = '\0';
            Contact *found = find_contact(book, name);
//            if (found)
//                printf("Found: %s -> %s\n", found->name, found->phone);
//            else
//                printf("Not found.\n");
            printf("Found: %s -> %s\n", found->name, found->phone);  // <-- add this
            break;

        case 4:
            list_contacts(book);
            break;

        case 5:
            save_to_file(book);
            free_all_contacts(book);
            printf("Goodbye.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }
}
