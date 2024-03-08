#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b);
int mod_inverse(int a, int m);
int mod_pow(int base, int exp, int mod);
typedef struct {
    int n; // Modulus
    int e; // Public exponent
    int d; // Private exponent
} RSAKeyPair;
RSAKeyPair generate_RSA_keys() {
    RSAKeyPair keys;
    int p, q, phi_n;
    p = 61; 
    q = 53; 
    keys.n = p * q;
    phi_n = (p - 1) * (q - 1);
    keys.e = 17; 
    keys.d = mod_inverse(keys.e, phi_n);
    return keys;
}
int rsa_encrypt(int plaintext, int e, int n) {
    return mod_pow(plaintext, e, n);
}
int rsa_decrypt(int ciphertext, int d, int n) {
    return mod_pow(ciphertext, d, n);
}
int main() {
    RSAKeyPair original_keys = generate_RSA_keys();
    int plaintext = 42; 
    int ciphertext = rsa_encrypt(plaintext, original_keys.e, original_keys.n);
    printf("Original Public Key (e, n): (%d, %d)\n", original_keys.e, original_keys.n);
    printf("Original Private Key (d): %d\n", original_keys.d);
    printf("Encrypted Message: %d\n", ciphertext);
    RSAKeyPair new_keys = generate_RSA_keys();
    int decrypted_message = rsa_decrypt(ciphertext, original_keys.d, original_keys.n);
    printf("\nNew Public Key (e, n): (%d, %d)\n", new_keys.e, new_keys.n);
    printf("New Private Key (d): %d\n", new_keys.d);
    printf("Decrypted Message with Leaked Private Key: %d\n", decrypted_message);

    return 0;
}
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}
int mod_pow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

