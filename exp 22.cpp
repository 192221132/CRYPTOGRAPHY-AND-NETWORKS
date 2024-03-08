#include <stdio.h>
unsigned short key = 0b0111111101;
unsigned short iv = 0b10101010;
unsigned short sdes_encrypt(unsigned short plaintext, unsigned short key);
unsigned short sdes_decrypt(unsigned short ciphertext, unsigned short key);
void cbc_encrypt(unsigned short *plaintext, int length);
void cbc_decrypt(unsigned short *ciphertext, int length);

int main() {
    unsigned short plaintext[] = {0b0000, 0b0001, 0b0010, 0b0011};
    int length = sizeof(plaintext) / sizeof(plaintext[0]);
    cbc_encrypt(plaintext, length);
    printf("Encrypted ciphertext:\n");
    for (int i = 0; i < length; i++) {
        printf("%04x ", plaintext[i]);
    }
    printf("\n");
    cbc_decrypt(plaintext, length);
    printf("Decrypted plaintext:\n");
    for (int i = 0; i < length; i++) {
        printf("%04x ", plaintext[i]);
    }
    printf("\n");
    return 0;
}
unsigned short sdes_encrypt(unsigned short plaintext, unsigned short key) {

}
unsigned short sdes_decrypt(unsigned short ciphertext, unsigned short key) {
}
void cbc_encrypt(unsigned short *plaintext, int length) {
    unsigned short previous_block = iv;

    for (int i = 0; i < length; i++) {
        plaintext[i] ^= previous_block;
        plaintext[i] = sdes_encrypt(plaintext[i], key);
        previous_block = plaintext[i];
    }
}
void cbc_decrypt(unsigned short *ciphertext, int length) {
    unsigned short previous_block = iv;

    for (int i = 0; i < length; i++) {
        unsigned short current_block = ciphertext[i];
        ciphertext[i] = sdes_decrypt(ciphertext[i], key);
        ciphertext[i] ^= previous_block;
        previous_block = current_block;
    }
}

