#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#define NAME_LEN 64
#define PHONE_LEN 32
#define FILE_NAME "contacts.db"

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact *next;
} Contact;

/* Core list operations */
Contact* add_contact(Contact *head, const char *name, const char *phone);
Contact* delete_contact(Contact *head, const char *name);
Contact* find_contact(Contact *head, const char *name);
void list_contacts(const Contact *head);
void free_all_contacts(Contact *head);

/* Persistence */
int save_to_file(const Contact *head);
Contact* load_from_file(void);

#endif
