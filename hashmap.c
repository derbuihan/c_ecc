#include "hashmap.h"

#include <limits.h>
#include <stdlib.h>

HashMap *newHashMap(int size) {
    HashMap *hashmap = malloc(sizeof(HashMap));
    hashmap->size = size;
    hashmap->entries = malloc(size * sizeof(Entry *));
    for (size_t i = 0; i < size; i++) {
        hashmap->entries[i] = NULL;
    }
    return hashmap;
}

int hash(int key, int size) {
    unsigned int ukey = (unsigned int)key;
    unsigned long long hash = ukey * 2654435761ULL;
    return (int)(hash % size);
}

HashMapStatus insertToHashMap(HashMap *hashmap, const int key, const int value) {
    int index = hash(key, hashmap->size);

    Entry *node = hashmap->entries[index];
    while (node) {
        if (node->key == key) {
            node->value = value;
            return HASHMAP_OK;
        }
        node = node->next;
    }

    Entry *new_node = malloc(sizeof(Entry));
    if (!new_node) return HASHMAP_ERROR;
    new_node->key = key;
    new_node->value = value;

    new_node->next = hashmap->entries[index];
    hashmap->entries[index] = new_node;
    return HASHMAP_OK;
}

HashMapStatus getValueFromHashMap(const HashMap *hashmap, const int key,
                                  int *value) {
    int index = hash(key, hashmap->size);

    Entry *node = hashmap->entries[index];
    while (node) {
        if (node->key == key) {
            *value = node->value;
            return HASHMAP_OK;
        }
        node = node->next;
    }

    return HASHMAP_ERROR;
}

void freeHashMap(HashMap *hashmap) {
    for (size_t i = 0; i < hashmap->size; i++) {
        Entry *node = hashmap->entries[i];
        while (node) {
            Entry *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashmap->entries);
    free(hashmap);
}
