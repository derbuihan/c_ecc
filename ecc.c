#include "ecc.h"
#include <stdlib.h>
#include "math.h"

ECurve *newECurve(int a, int b, int p) {
    ECurve *curve = (ECurve *)malloc(sizeof(ECurve));
    if (!curve) return NULL;
    curve->a = mod_norm(a, p);
    curve->b = mod_norm(b, p);
    curve->p = p;
    return curve;
}

void freeECurve(ECurve *curve) {
    if (curve) {
        free(curve);
    }
}

ECPoint *newECPoint(ECurve *curve) {
    ECPoint *point = (ECPoint *)malloc(sizeof(ECPoint));
    if (!point) return NULL;
    return point;
}

void freeECPoint(ECPoint *point) {
    if (point) {
        free(point);
    }
}

// Check if a point is on the curve
bool ECPointIsOnCurve(ECurve *curve, int x, int y) {
    if (!curve) return false;
    int left = mod_norm(y * y, curve->p);
    int right = mod_norm(x * x * x + curve->a * x + curve->b, curve->p);
    return left == right;
}

ECStatus ECPointSet(ECurve *curve, ECPoint **point, int x, int y) {
    if (!point || !*point) return EC_ERROR;
    if (!ECPointIsOnCurve(curve, x, y)) return EC_ERROR;
    (*point)->x = mod_norm(x, curve->p);
    (*point)->y = mod_norm(y, curve->p);
    (*point)->is_infinity = false;
    return EC_OK;
}

ECStatus ECPointSetInfinity(ECPoint **point) {
    if (!point || !*point) return EC_ERROR;
    (*point)->x = 0;
    (*point)->y = 0;
    (*point)->is_infinity = true;
    return EC_OK;
}

// p == q
int ECPointIsEqual( ECPoint *P,  ECPoint *Q) {
    if (P->is_infinity && Q->is_infinity) return 1;
    if (P->is_infinity || Q->is_infinity) return 0;
    return P->x == Q->x && P->y == Q->y;
}

// result = p + q
ECStatus ECPointAdd( ECurve *curve,  ECPoint *p,  ECPoint *q, ECPoint **result) {
    if (p->is_infinity && q->is_infinity) {
        ECPointSetInfinity(result);
        return EC_OK;
    }

    if (p->is_infinity) {
        ECPointSet(curve, result, q->x, q->y);
        return EC_OK;
    }

    if (q->is_infinity) {
        ECPointSet(curve, result, p->x, p->y);
        return EC_OK;
    }

    if (ECPointIsEqual(p, q)) {
        return ECPointDouble(curve, p, result);
    }

    if (p->x == q->x) {
        ECPointSetInfinity(result);
        return EC_OK;
    }

    int lambda_num = mod_norm(q->y - p->y, curve->p);
    int lambda_den = mod_norm(q->x - p->x, curve->p);
    int lambda = mod_norm(lambda_num * mod_inv(lambda_den, curve->p), curve->p);

    int x_r = mod_norm(lambda * lambda - p->x - q->x, curve->p);
    int y_r = mod_norm(lambda * (p->x - x_r) - p->y, curve->p);

    ECPointSet(curve, result, x_r, y_r);

    return EC_OK;
}

// result = 2 * p
ECStatus ECPointDouble( ECurve *curve,  ECPoint *p, ECPoint **result) {
    if (p->is_infinity) {
        ECPointSetInfinity(result);
        return EC_OK;
    }

    if (p->y == 0) {
        ECPointSetInfinity(result);
        return EC_OK;
    }

    int lambda_num = mod_norm(3 * p->x * p->x + curve->a, curve->p);
    int lambda_den = mod_norm(2 * p->y, curve->p);
    int lambda = mod_norm(lambda_num * mod_inv(lambda_den, curve->p), curve->p);

    int x_r = mod_norm(lambda * lambda - 2 * p->x, curve->p);
    int y_r = mod_norm(lambda * (p->x - x_r) - p->y, curve->p);

    ECPointSet(curve, result, x_r, y_r);

    return EC_OK;
}

// result = k * p
ECStatus ECPointMultiply(ECurve *curve, ECPoint *p, int k, ECPoint **result) {
    if (k < 0) return EC_ERROR;

    ECPointSetInfinity(result);
    ECPoint *base = newECPoint(curve);
    ECPointSet(curve, &base, p->x, p->y);

    while(k) {
        if (k&1) {
            ECStatus status = ECPointAdd(curve, *result, base, result);
            if (status != EC_OK) return status;
        }
        k >>= 1;
        ECPointDouble(curve, base, &base);
    }
    freeECPoint(base);
    return EC_OK;
}

