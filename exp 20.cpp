#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encryptECB(const char *plaintext, const char *key, char *ciphertext);
void decryptECB(const char *ciphertext, const char *key, char *decryptedtext);
void encryptCBC(const char *plaintext, const char *key, const char *iv, char *ciphertext);
void decryptCBC(const char *ciphertext, const char *key, const char *iv, char *decryptedtext);

int main() {
    const char plaintext[] = "CRYPTOGRAPHY12345";  
    const char key[] = "SECRETKEY";                  
    const char iv[] = "INITIALIV";                  

    char ciphertextECB[100];
    char decryptedtextECB[100];

    char ciphertextCBC[100];
    char decryptedtextCBC[100];
    encryptECB(plaintext, key, ciphertextECB);
    decryptECB(ciphertextECB, key, decryptedtextECB);

    printf("ECB Mode:\n");
    printf("Original Text:  %s\n", plaintext);
    printf("Ciphertext:     %s\n", ciphertextECB);
    printf("Decrypted Text: %s\n\n", decryptedtextECB);
    encryptCBC(plaintext, key, iv, ciphertextCBC);
    decryptCBC(ciphertextCBC, key, iv, decryptedtextCBC);

    printf("CBC Mode:\n");
    printf("Original Text:  %s\n", plaintext);
    printf("Ciphertext:     %s\n", ciphertextCBC);
    printf("Decrypted Text: %s\n", decryptedtextCBC);

    return 0;
}

void encryptECB(const char *plaintext, const char *key, char *ciphertext) {
    
    strcpy(ciphertext, plaintext);
}

void decryptECB(const char *ciphertext, const char *key, char *decryptedtext) {
    
    strcpy(decryptedtext, ciphertext);
}


void encryptCBC(const char *plaintext, const char *key, const char *iv, char *ciphertext) {
    int len = strlen(plaintext);
    char previousBlock[16];
    strcpy(previousBlock, iv);
    for (int i = 0; i < len; i += 16) {
        char block[16];
        strncpy(block, plaintext + i, 16);
        for (int j = 0; j < 16; j++) {
            block[j] ^= previousBlock[j];
        }
        strncpy(ciphertext + i, block, 16);
        strcpy(previousBlock, ciphertext + i);
    }
}
void decryptCBC(const char *ciphertext, const char *key, const char *iv, char *decryptedtext) {
    

    int len = strlen(ciphertext);
    char previousBlock[16];

    strcpy(previousBlock, iv);

    for (int i = 0; i < len; i += 16) {
        char block[16];

       
        strncpy(block, ciphertext + i, 16);
        strncpy(decryptedtext + i, block, 16);
        for (int j = 0; j < 16; j++) {
            decryptedtext[i + j] ^= previousBlock[j];
        }

    
        strcpy(previousBlock, block);
    }
}

