#ifndef HASHBOOK_H
#define HASHBOOK_H

#include <stddef.h>

#define NAME_LEN  64
#define PHONE_LEN 32
#define FILE_NAME "contacts.db"
// #define INIT_SIZE 8

#define INIT_SIZE 4

// here the typedef have to Contact, kind of speciall, likely to bcs it refers to itself.
typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact *next;
} Contact;

typedef struct {
    Contact **buckets;
    // you shall figure out why there is **
    //buckets is a pointer to a pointer to Contact
    /*
    Contact *
    Contact *bucket[]
    Contact **bucket
    So, there the bucket is the addr of the array
    and each element of the array is a pointer to Contact
     */
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

// i think i should start form here
HashTable* ht_load(void);

#endif
