#include "math.h"

int isqrt(int n) {
    if (n < 0) return -1; // Invalid input
    if (n == 0 || n == 1) return n;

    unsigned long long x = n;
    unsigned long long y = (x + 1) / 2;

    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }

    return (int)x;
}

// result = b^e (mod m)
int mod_pow(int base, int exp, int mod) {
    unsigned long long result = 1;
    unsigned long long b = base % mod;

    while (exp) {
        if (exp & 1) {
            result = (result * b) % mod;
        }
        exp >>= 1;
        b = (b * b) % mod;
    }
    return (int)result;
}

// a^{-1} mod p
int mod_inv(int a, int p) {
    return mod_pow(a, p - 2, p);
}

// val mod p in [0, p-1]
int mod_norm(int val, int p){
    int result = val % p;
    return result < 0 ? result + p : result;
}
