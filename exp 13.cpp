#include <stdio.h>

#define SIZE 2

int determinant(int matrix[SIZE][SIZE]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}


void inverseMatrix(int key[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = determinant(key);
    int detInv = modInverse(det, 26);

    inverse[0][0] = key[1][1] * detInv % 26;
    inverse[0][1] = (-key[0][1]) * detInv % 26;
    inverse[1][0] = (-key[1][0]) * detInv % 26;
    inverse[1][1] = key[0][0] * detInv % 26;
}

void decrypt(char ciphertext[], int key[SIZE][SIZE], int length) {
    int inverse[SIZE][SIZE];
    inverseMatrix(key, inverse);

    printf("Decrypted message: ");
    for (int i = 0; i < length; i += SIZE) {
        int matrix[SIZE][1];
        int decrypted[SIZE][1];

        for (int j = 0; j < SIZE; j++) {
            matrix[j][0] = ciphertext[i + j] - 'a';
        }

        for (int j = 0; j < SIZE; j++) {
            decrypted[j][0] = 0;
            for (int k = 0; k < SIZE; k++) {
                decrypted[j][0] += inverse[j][k] * matrix[k][0];
            }
            decrypted[j][0] = (decrypted[j][0] + 26) % 26; 
        }

        for (int j = 0; j < SIZE; j++) {
            printf("%c", 'a' + decrypted[j][0]); 
        }
    }
}

int main() {
    char ciphertext[] = "xwcxycnxfqsm";
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    int length = sizeof(ciphertext) - 1;

    decrypt(ciphertext, key, length);
    printf("\n");

    return 0;
}
