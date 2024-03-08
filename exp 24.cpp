#include <stdio.h>
int gcd(int a, int b);
int mod_inverse(int a, int m);
int main() {
    int e = 31;
    int n = 3599;
    int p, q;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }
    int phi_n = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi_n);
    printf("p: %d\n", p);
    printf("q: %d\n", q);
    printf("Private key (d): %d\n", d);
    return 0;
}
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
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

