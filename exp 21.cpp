#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 16
void ecb_encrypt(char *plaintext, char *key, int length);
void ecb_decrypt(char *ciphertext, char *key, int length);
void cbc_encrypt(char *plaintext, char *key, char *iv, int length);
void cbc_decrypt(char *ciphertext, char *key, char *iv, int length);
void cfb_encrypt(char *plaintext, char *key, char *iv, int length);
void cfb_decrypt(char *ciphertext, char *key, char *iv, int length);

int main() {
    char plaintext[] = "Hello, world!";
    char key[] = "myencryptionkey";
    char iv[] = "initializationv";

    int length = strlen(plaintext);
    int padding = BLOCK_SIZE - (length % BLOCK_SIZE);
    if (padding != BLOCK_SIZE) {
        for (int i = 0; i < padding; i++) {
            plaintext[length + i] = 0; 
        }
        length += padding;
    }
    printf("ECB Mode:\n");
    ecb_encrypt(plaintext, key, length);
    ecb_decrypt(plaintext, key, length);
    printf("\nCBC Mode:\n");
    cbc_encrypt(plaintext, key, iv, length);
    cbc_decrypt(plaintext, key, iv, length);
    printf("\nCFB Mode:\n");
    cfb_encrypt(plaintext, key, iv, length);
    cfb_decrypt(plaintext, key, iv, length);    return 0;
}
void ecb_encrypt(char *plaintext, char *key, int length) {
    printf("Encrypting...\n");
}
void ecb_decrypt(char *ciphertext, char *key, int length) {
    printf("Decrypting...\n");
}
void cbc_encrypt(char *plaintext, char *key, char *iv, int length) {
    printf("Encrypting...\n");

}
void cbc_decrypt(char *ciphertext, char *key, char *iv, int length) {
    printf("Decrypting...\n");
}
void cfb_encrypt(char *plaintext, char *key, char *iv, int length) {
    printf("Encrypting...\n");
}
void cfb_decrypt(char *ciphertext, char *key, char *iv, int length) {
    printf("Decrypting...\n");
}

