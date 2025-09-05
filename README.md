# Elliptic Curve Cryptography (ECC) Implementation

A basic implementation of Elliptic Curve Cryptography in C. This project implements elliptic curve operations, ECDH key exchange protocol, and discrete logarithm problem solving.

## Overview

This project provides fundamental elliptic curve cryptography functionalities over finite fields. Key features include:

- **Elliptic Curve Operations**: Point addition, point doubling, and scalar multiplication
- **ECDH Key Exchange**: Implementation of Elliptic Curve Diffie-Hellman key exchange protocol
- **Discrete Logarithm**: Baby-step Giant-step algorithm for solving discrete logarithm problems
- **Modular Arithmetic**: Various mathematical operations over finite fields

## Build and Run

```bash
# Build the project
make

# Run the demo program
make run

# Clean build files
make clean
```

## Program Output

```
G = (0, 149)
A's public key = (903, 436)
B's public key = (537, 213)
Shared secret established successfully.
A's public key recovered successfully: (903, 436)
B's public key recovered successfully: (537, 213)
```

## Project Structure

```
c_ecc/
├── ecc.c / ecc.h           # Elliptic curve basic operations
├── discrete_log.c / .h     # Discrete logarithm solver (Baby-step Giant-step)
├── math.c / math.h         # Mathematical functions for modular arithmetic
├── hashmap.c / hashmap.h   # Generic hashmap data structure
├── ecc_hashmap.c / .h      # ECC-specific hashmap implementation
├── main.c                  # Demo program
├── Makefile               # Build configuration
└── README.md              # This file
```
