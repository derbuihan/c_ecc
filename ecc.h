#ifndef ECC_H
#define ECC_H

#include <stdbool.h>

typedef enum { EC_OK, EC_ERROR } ECStatus;

typedef struct ECPoint ECPoint;
struct ECPoint {
  int x;
  int y;
  bool is_infinity;
};

typedef struct ECurve ECurve;
struct ECurve {
  int a;
  int b;
  int p;
};

ECurve *newECurve(int a, int b, int p);
void freeECurve(ECurve *curve);
ECPoint *newECPoint(ECurve *curve, int x, int y);
void freeECPoint(ECPoint *point);

ECStatus ECPointAdd(ECurve *curve, ECPoint *p, ECPoint *q, ECPoint **result);
ECStatus ECPointDouble(ECurve *curve, ECPoint *p, ECPoint **result);
ECStatus ECPointMultiply(ECurve *curve, ECPoint *p, int k, ECPoint **result);

#endif
