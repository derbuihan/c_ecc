#include <stdio.h>
#include "ecc.h"

int main() {
    int a = 2, b = 3;
    int p = 5;

    ECurve *curve = newECurve(a, b, p);

    ECPoint *P = newECPoint(curve);
    if (ECPointSet(curve, &P, 3, 1) == EC_ERROR) {
        printf("Failed to set point P\n");
        freeECPoint(P);
        freeECurve(curve);
        return 1;
    }
    printf("P = (%d, %d)\n", P->x, P->y);

    ECPoint *Q = newECPoint(curve);
    ECPointSetInfinity(&Q);
    printf("Q = (inf, inf)\n");

    ECPoint *R = newECPoint(curve);
    ECPointSetInfinity(&R);
    printf("R = (inf, inf)\n");

    for (int k = 1; k < 5; k++) {
        printf("---\n");
        ECPointAdd(curve, P, Q, &Q);
        printf("Q = (%d, %d)\n", Q->x, Q->y);

        ECPointMultiply(curve, P, k, &R);
        printf("R = (%d, %d)\n", R->x, R->y);
    }

    freeECPoint(P);
    freeECPoint(Q);
    freeECPoint(R);
    freeECurve(curve);

    return 0;
}

