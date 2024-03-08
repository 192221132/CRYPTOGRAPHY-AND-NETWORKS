#include <stdio.h>
#include <math.h>
int mod_pow(int base, int exp, int mod);

int main() {
    int q = 23; 
    int a = 5;  
    int x_Alice = 6;
    int x_Bob = 15;
    int y_Alice = mod_pow(a, x_Alice, q);
    int y_Bob = mod_pow(a, x_Bob, q);
    int shared_key_Alice = mod_pow(y_Bob, x_Alice, q);
    int shared_key_Bob = mod_pow(y_Alice, x_Bob, q);
    printf("Alice's private key (x_Alice): %d\n", x_Alice);
    printf("Bob's private key (x_Bob): %d\n", x_Bob);
    printf("Public key for Alice (y_Alice): %d\n", y_Alice);
    printf("Public key for Bob (y_Bob): %d\n", y_Bob);
    printf("Shared key for Alice: %d\n", shared_key_Alice);
    printf("Shared key for Bob: %d\n", shared_key_Bob);
    return 0;
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

