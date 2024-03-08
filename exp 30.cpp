#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16


void xor_blocks(unsigned char *block1, unsigned char *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block1[i] ^= block2[i];
    }
}

void cbc_mac(unsigned char *key, unsigned char *message, unsigned char *mac) {

    unsigned char iv[BLOCK_SIZE] = {0};
    
    for (int i = 0; i < BLOCK_SIZE; i++) {
        mac[i] = iv[i] ^ message[i];
    }

    xor_blocks(iv, mac);

    memcpy(mac, key, BLOCK_SIZE);
}

int main() {
    unsigned char key[BLOCK_SIZE] = "1234567890abcdef"; 
    unsigned char message[BLOCK_SIZE] = "Hello, world!"; 
    unsigned char mac[BLOCK_SIZE];

    cbc_mac(key, message, mac);

    printf("MAC for one-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    unsigned char x_xor_t[BLOCK_SIZE];
    memcpy(x_xor_t, message, BLOCK_SIZE);
    xor_blocks(x_xor_t, mac);

    cbc_mac(key, x_xor_t, mac);


    printf("MAC for two-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}
