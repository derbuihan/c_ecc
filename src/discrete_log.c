#include "discrete_log.h"
#include "hashmap.h"
#include "math.h"

// find x such that A = g^x mod p
int discrete_log(int g, int A, int p) {
    int q = isqrt(p);

    // Baby-step
    HashMap *hashmap = newHashMap(q);
    int b = 1;
    insertToHashMap(hashmap, b, 0);
    for (int i = 1; i <= q; i++) {
        b = (b * g) % p;
        insertToHashMap(hashmap, b, i);
    }

    // Giant-step
    int g_inv = mod_pow(g, p-2, p);
    int g_inv_q = mod_pow(g_inv, q, p);

    int giant_step = A;
    int result = -1;

    for (int a=0; a<q; a++) {
        int b;
        if (getValueFromHashMap(hashmap, giant_step, &b) == HASHMAP_OK) {
            result = a * q + b;
            break;
        }
        giant_step = (giant_step * g_inv_q) % p;
    }

    freeHashMap(hashmap);
    return result;
}
