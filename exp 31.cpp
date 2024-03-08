#include <stdio.h>
#include <stdint.h>


#define CONSTANT_64 0x1B
#define CONSTANT_128 0x87


uint8_t left_shift(uint8_t byte) {
 
    return (byte << 1) | ((byte & 0x80) ? 1 : 0);
}


void generate_subkeys(uint8_t *subkey, uint8_t block_size) {
   
    for (int i = 0; i < block_size; i++) {
        if (i == 0) {
            subkey[i] = left_shift(subkey[i]);
            if (block_size == 64) {
                subkey[i] ^= CONSTANT_64;
            } else if (block_size == 128) {
                subkey[i] ^= CONSTANT_128;
            }
        } else if (i < block_size - 1) {
            subkey[i] = subkey[i - 1];
            subkey[i] = left_shift(subkey[i]);
            if (block_size == 64) {
                subkey[i] ^= (subkey[i - 1] & 0x80) ? CONSTANT_64 : 0;
            } else if (block_size == 128) {
                subkey[i] ^= (subkey[i - 1] & 0x80) ? CONSTANT_128 : 0;
            }
        } else {
            subkey[i] = left_shift(subkey[i - 1]);
            if (block_size == 64) {
                subkey[i] ^= (subkey[i - 1] & 0x80) ? CONSTANT_64 : 0;
            } else if (block_size == 128) {
                subkey[i] ^= (subkey[i - 1] & 0x80) ? CONSTANT_128 : 0;
            }
        }
    }
}

int main() {
  
    uint8_t block_size_64 = 8;
    uint8_t block_size_128 = 16; 

   
    uint8_t subkey_64[block_size_64];
    uint8_t subkey_128[block_size_128];

   
    for (int i = 0; i < block_size_64; i++) {
        subkey_64[i] = 0x00;
    }
    for (int i = 0; i < block_size_128; i++) {
        subkey_128[i] = 0x00;
    }


    generate_subkeys(subkey_64, block_size_64);


    generate_subkeys(subkey_128, block_size_128);


    printf("Subkey for block size 64: ");
    for (int i = 0; i < block_size_64; i++) {
        printf("%02X ", subkey_64[i]);
    }
    printf("\n");

    printf("Subkey for block size 128: ");
    for (int i = 0; i < block_size_128; i++) {
        printf("%02X ", subkey_128[i]);
    }
    printf("\n");

    return 0;
}
