#ifndef HASHBOOK_H
#define HASHBOOK_H

#include <stddef.h>

#define NAME_LEN  64
#define PHONE_LEN 32
#define FILE_NAME "contacts.db"
#define INIT_SIZE 8

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact *next;
} Contact;

typedef struct {
    Contact **buckets;
    size_t size;
    size_t count;
} HashTable;

/* Lifecycle */
HashTable* ht_create(void);
void ht_destroy(HashTable *ht);

/* CRUD */
void ht_add(HashTable *ht, const char *name, const char *phone);
Contact* ht_find(const HashTable *ht, const char *name);
int ht_delete(HashTable *ht, const char *name);
void ht_list(const HashTable *ht);

/* Persistence */
int ht_save(const HashTable *ht);
HashTable* ht_load(void);

#endif
