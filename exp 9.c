#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void decryptPlayfair(const char ciphertext[], const char keySquare[5][5], char plaintext[]);

int main() {
    const char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    const char key[] = "KEYWORD";  
    char keySquare[5][5];

    
    generateKeySquare(key, keySquare);

    char plaintext[1000];
    decryptPlayfair(ciphertext, keySquare, plaintext);

    printf("Decrypted Message:\n%s\n", plaintext);

    return 0;
}

void generateKeySquare(const char *key, char keySquare[5][5]) {
    
    int k, i, j;
    char keySet[26] = {0};

    k = 0;
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'J' && keySet[key[i] - 'A'] == 0) {
            keySquare[k / 5][k % 5] = key[i];
            keySet[key[i] - 'A'] = 1;
            k++;
        }
    }

    
    for (i = 0; i < 26; i++) {
        if (keySet[i] == 0) {
            keySquare[k / 5][k % 5] = (char)('A' + i);
            k++;
        }
    }
}

void findPosition(const char keySquare[5][5], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (keySquare[*row][*col] == ch)
                return;
        }
    }
}


void decryptPlayfair(const char ciphertext[], const char keySquare[5][5], char plaintext[]) {
    int i, length = strlen(ciphertext);

    for (i = 0; i < length; i += 3) {
        int row1, col1, row2, col2;
        findPosition(keySquare, ciphertext[i], &row1, &col1);
        findPosition(keySquare, ciphertext[i + 1], &row2, &col2);
        if (row1 == row2) {
            plaintext[i] = keySquare[row1][(col1 - 1 + 5) % 5];
            plaintext[i + 1] = keySquare[row2][(col2 - 1 + 5) % 5];
        }
        
        else if (col1 == col2) {
            plaintext[i] = keySquare[(row1 - 1 + 5) % 5][col1];
            plaintext[i + 1] = keySquare[(row2 - 1 + 5) % 5][col2];
        }
        
        else {
            plaintext[i] = keySquare[row1][col2];
            plaintext[i + 1] = keySquare[row2][col1];
        }
        plaintext[i + 2] = ' ';
    }
    plaintext[length - 1] = '\0';
}

