#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

typedef enum { HASHMAP_OK, HASHMAP_ERROR } HashMapStatus;

typedef struct Entry Entry;
struct Entry {
  int key;
  int value;
  Entry *next;
};

typedef struct HashMap HashMap;
struct HashMap {
  size_t size;
  Entry **entries;
};

HashMap *newHashMap(int size);
HashMapStatus insertToHashMap(HashMap *hashmap, const int key, const int value);
HashMapStatus getValueFromHashMap(HashMap *hashmap, int key, int *value);
void freeHashMap(HashMap *hashmap);

#endif
