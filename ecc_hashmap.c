#include "ecc_hashmap.h"
#include <stdlib.h>


ECPointHashMap *newECPointHashMap(int size) {
    ECPointHashMap *hashmap = malloc(sizeof(ECPointHashMap));
    hashmap->size = size;
    hashmap->entries = malloc(size * sizeof(ECPointEntry *));
    for (size_t i = 0; i < size; i++) {
        hashmap->entries[i] = NULL;
    }
    return hashmap;
}

int ECPointHash(ECPoint *point, int size) {
    unsigned int ukey = (unsigned int)(point->x ^ (point->y << 16) ^ (point->is_infinity ? 0xFFFFFFFF : 0));
    unsigned long long hash = ukey * 2654435761ULL;
    return (int)(hash % size);
}

ECStatus insertToECPointHashMap(ECPointHashMap *hashmap, ECPoint *key,
                                int value) {
    int index = ECPointHash(key, hashmap->size);

    ECPointEntry *node = hashmap->entries[index];
    while (node) {
        if (ECPointIsEqual(&node->key, key)) {
            node->value = value;
            return EC_OK;
        }
        node = node->next;
    }

    ECPointEntry *new_node = malloc(sizeof(ECPointEntry));
    if (!new_node) return EC_ERROR;
    new_node->key = *key;
    new_node->value = value;

    new_node->next = hashmap->entries[index];
    hashmap->entries[index] = new_node;
    return EC_OK;
}

ECStatus getValueFromECPointHashMap(ECPointHashMap *hashmap, ECPoint *key,
                                    int *value){
    if (!hashmap || !key || !value) return EC_ERROR;

    int index = ECPointHash(key, hashmap->size);
    ECPointEntry *node = hashmap->entries[index];

    while (node) {
        if (ECPointIsEqual(&node->key, key)) {
            *value = node->value;
            return EC_OK;
        }
        node = node->next;
    }

    return EC_ERROR;
}

void freeECPointHashMap(ECPointHashMap *hashmap) {
    for (size_t i = 0; i < hashmap->size; i++) {
        ECPointEntry *node = hashmap->entries[i];
        while (node) {
            ECPointEntry *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashmap->entries);
    free(hashmap);
}
