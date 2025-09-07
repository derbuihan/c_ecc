#include <stdio.h>
#include "ecc.h"

int main() {
    int a = 2, b = 3;
    int p = 1009;

    ECurve *curve = newECurve(a, b, p);

    int x, y;
    ECPointFindOnCurve(curve, &x, &y);

    ECPoint *G = newECPoint(curve);
    ECPointSet(curve, &G, x, y);
    printf("G = (%d, %d)\n", G->x, G->y);

    // Private Key
    int A_private = 123;
    int B_private = 456;

    // Public key
    ECPoint *A_public = newECPoint(curve);
    ECPointMultiply(curve, G, A_private, &A_public);
    printf("A's public key = (%d, %d)\n", A_public->x, A_public->y);

    ECPoint *B_public = newECPoint(curve);
    ECPointMultiply(curve, G, B_private, &B_public);
    printf("B's public key = (%d, %d)\n", B_public->x, B_public->y);

    // Shared secret
    ECPoint *A_shared = newECPoint(curve);
    ECPointMultiply(curve, B_public, A_private, &A_shared);

    ECPoint *B_shared = newECPoint(curve);
    ECPointMultiply(curve, A_public, B_private, &B_shared);

    if (ECPointIsEqual(A_shared, B_shared)) {
        printf("Shared secret established successfully.\n");
    } else {
        printf("Failed to establish shared secret.\n");
    }

    // Discrete Log
    int A_private_ = ECPointDiscreteLog(curve, G, A_public);
    int B_private_ = ECPointDiscreteLog(curve, G, B_public);

    ECPoint *A_public_ = newECPoint(curve);
    ECPointMultiply(curve, G, A_private_, &A_public_);
    if (ECPointIsEqual(A_public_, A_public)) {
        printf("A's public key recovered successfully: (%d, %d)\n", A_public_->x, A_public_->y);
    } else {
        printf("Failed to recover A's public key.\n");
    }

    ECPoint *B_public_ = newECPoint(curve);
    ECPointMultiply(curve, G, B_private_, &B_public_);
    if (ECPointIsEqual(B_public_, B_public)) {
        printf("B's public key recovered successfully: (%d, %d)\n", B_public_->x, B_public_->y);
    } else {
        printf("Failed to recover B's public key.\n");
    }

    return 0;
}

