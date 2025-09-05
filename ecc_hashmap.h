#ifndef ECC_HASHMAP_H
#define ECC_HASHMAP_H

#include "ecc.h"
#include <stddef.h>

typedef struct ECPointEntry ECPointEntry;
struct ECPointEntry {
  ECPoint key;
  int value;
  ECPointEntry *next;
};

typedef struct ECPointHashMap ECPointHashMap;
struct ECPointHashMap {
  size_t size;
  ECPointEntry **entries;
};

ECPointHashMap *newECPointHashMap(int size);
ECStatus insertToECPointHashMap(ECPointHashMap *hashmap, ECPoint *key,
                                int value);
ECStatus getValueFromECPointHashMap(ECPointHashMap *hashmap, ECPoint *key,
                                    int *value);
void freeECPointHashMap(ECPointHashMap *hashmap);

#endif
