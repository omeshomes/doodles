// Hash Map -- KPCB Application Coding Challenge
// Omid Rooholfada

/* DISCLAIMER: I had a similar assignment for my Data Structures class last year at Yale. 
My solution here is adapted from that assignment. */

// To run the tests written in main, run the following on the command line:
// make KPCB_Hash
// ./KPCB_Hash

// NOTE: In this hash map, keys (strings) are associated with values that are also strings. 
// However, we could alter the implmentation to make the values non-string objects.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

// structs declared
struct elt {
    struct elt *next;
    char *key;
    char *value;
};

struct dict {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
};

typedef struct dict *Dict;

// function declarations
Dict DictCreate(void);

void DictDestroy(Dict);

bool set(Dict, const char *key, const char *value);

const char * get(Dict, const char *key);

const char * delete(Dict, const char *key);

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

/* dictionary initialization code */
Dict
constructor(int size)
{
    Dict d;
    int i;

    d = malloc(sizeof(*d));

    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->table = malloc(sizeof(struct elt *) * d->size);

    assert(d->table != 0);

    for(i = 0; i < d->size; i++) d->table[i] = 0;

    return d;
}

void
DictDestroy(Dict d)
{
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            free(e->value);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

#define MULTIPLIER (97)

static unsigned long
hash_function(const char *s)
{
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}

static void
grow(Dict d)
{
    Dict d2;            /* new dictionary we'll create */
    struct dict swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    d2 = constructor(d->size * GROWTH_FACTOR);

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside DictInsert
             * to avoid this problem */
            set(d2, e->key, e->value);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call DictDestroy on d2 */
    swap = *d;
    *d = *d2;
    *d2 = swap;

    DictDestroy(d2);
}

/* insert a new key-value pair into an existing dictionary */
bool
set(Dict d, const char *key, const char *value)
{
    struct elt *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = strdup(key);
    e->value = strdup(value);

    h = hash_function(key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;

    /* grow table if there is not enough room */
    if(d->n >= d->size * MAX_LOAD_FACTOR) {
        grow(d);
    }

    return true;
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *
get(Dict d, const char *key)
{
    struct elt *e;

    for(e = d->table[hash_function(key) % d->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
            return e->value;
        }
    }

    return NULL;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
const char *
delete(Dict d, const char *key)
{
    struct elt **prev;          /* what to change when elt is deleted */
    struct elt *e;              /* what to delete */

    for(prev = &(d->table[hash_function(key) % d->size]); 
        *prev != 0; 
        prev = &((*prev)->next)) {
        if(!strcmp((*prev)->key, key)) {
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            free(e->value);
            free(e);

            return key;
        }
    }
    return NULL;
}

/* returns the ratio of (number of elements in hash map)/(size of has map) */
float
load(Dict d) 
{
    float ratio = (float) d->n / (float) d->size;
    return ratio;
}

int
main() {
    Dict hash = constructor(50);
    set(hash, "hello", "a greeting commonly used in English-speaking regions");
    set(hash, "good-bye", "a phrase commonly used in English-speaking regions when individuals are departing");
    printf("%s\n", get(hash, "hello"));
    int i;
    for (i = 0; i < 50; i++) {
        printf("%d: ", i);
        struct elt *e = hash->table[i];
        while (e != NULL) {
            printf("%s, %s; ", e->key, e->value);
            e = e->next;
        }
        printf("\n");
    }
    return 0;
}

