#include <stdio.h>
int gcd(int a, int b);
int mod_inverse(int a, int m);
int main() {
    int n = 3233;
    int e = 17;   
    int plaintext_block = 123;
    int common_factor = gcd(plaintext_block, n);
    printf("Common factor with n: %d\n", common_factor);
    if (common_factor > 1) {
        int p = common_factor;
        int q = n / p;
        int phi_n = (p - 1) * (q - 1);
        int d = mod_inverse(e, phi_n);
        printf("Private key (d): %d\n", d);
    } else {
        printf("No common factor found. The attack is not successful.\n");
    }
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

