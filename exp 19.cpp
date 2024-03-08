#include <stdio.h>
#include <string.h>


void encryptDES3CBC(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext);

int main() {
    const unsigned char plaintext[8] = "01234567"; 
    const unsigned char key[24] = "abcdefghabcdefghabcdefgh"; 
    const unsigned char iv[8] = "initiali"; 

    unsigned char ciphertext[8];

    encryptDES3CBC(plaintext, key, iv, ciphertext);

    printf("Plaintext:  %s\n", plaintext);
    printf("Key:        %s\n", key);
    printf("IV:         %s\n", iv);
    printf("Ciphertext: ");
    for (int i = 0; i < 8; ++i) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

void encryptDES3CBC(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    DES_cblock desKey1, desKey2, desKey3;
    DES_key_schedule ks1, ks2, ks3;

    memcpy(desKey1, key, 8);
    memcpy(desKey2, key + 8, 8);
    memcpy(desKey3, key + 16, 8);

    DES_set_key_checked(&desKey1, &ks1);
    DES_set_key_checked(&desKey2, &ks2);
    DES_set_key_checked(&desKey3, &ks3);

    DES_cblock ivec;
    memcpy(ivec, iv, 8);

    DES_ede3_cbc_encrypt(plaintext, ciphertext, 8, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
}

