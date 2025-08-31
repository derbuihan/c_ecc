#include <stdio.h>
#include "discrete_log.h"
#include "math.h"

int main() {
    int p = 1009;
    int g = 11;

    // private keys
    int a = 123;
    int b = 456;

    // public keys
    int A = mod_pow(g, a, p); // Alice public key
    int B = mod_pow(g, b, p); // Bob public key
    printf("Alice's public key: %d\n", A);
    printf("Bob's public key: %d\n", B);

    // Shared secret
    int s1 = mod_pow(B, a, p);
    int s2 = mod_pow(A, b, p);

    if (s1 == s2) {
        printf("Shared secret established: %d\n", s1);
    } else {
        printf("Shared secret failed.\n");
    }

    // Solve
    int a_ = discrete_log(g, A, p);
    int b_ = discrete_log(g, B, p);

    if (a_ != -1 && b_ != -1) {
        printf("Discrete log found: a = %d, b = %d\n", a_, b_);
    } else {
        printf("Discrete log not found.\n");
    }

    return 0;
}

