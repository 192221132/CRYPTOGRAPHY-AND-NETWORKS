#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MESSAGE "This is a test message for DSA and RSA signatures."

void dsa_sign_and_verify(DSA *dsa, const uint8_t *message, size_t message_len) {
    // Generate random k for each signature
    unsigned char k[DSA_size(dsa)];
    RAND_bytes(k, DSA_size(dsa));

    // Sign the message using DSA
    unsigned char signature[DSA_size(dsa)];
    DSA_sign(0, message, message_len, signature, NULL, dsa);

    // Verify the signature
    int verified = DSA_verify(0, message, message_len, signature, DSA_size(dsa), dsa);
    if (verified) {
        printf("DSA signature verified.\n");
    } else {
        printf("DSA signature verification failed.\n");
    }
}

void rsa_sign_and_verify(const uint8_t *message, size_t message_len, RSA *rsa) {
    // Sign the message using RSA
    unsigned char signature[RSA_size(rsa)];
    unsigned int signature_len;
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        printf("Error creating EVP_MD_CTX.\n");
        return;
    }

    EVP_SignInit(md_ctx, EVP_sha256());
    EVP_SignUpdate(md_ctx, message, message_len);
    int rsa_sign_result = EVP_SignFinal(md_ctx, signature, &signature_len, rsa);
    EVP_MD_CTX_free(md_ctx);

    if (rsa_sign_result == 1) {
        printf("RSA signature generated.\n");
    } else {
        printf("Error generating RSA signature.\n");
        return;
    }

    // Verify the signature
    EVP_MD_CTX *md_ctx_verify = EVP_MD_CTX_new();
    if (!md_ctx_verify) {
        printf("Error creating EVP_MD_CTX for verification.\n");
        return;
    }

    EVP_VerifyInit(md_ctx_verify, EVP_sha256());
    EVP_VerifyUpdate(md_ctx_verify, message, message_len);
    int rsa_verify_result = EVP_VerifyFinal(md_ctx_verify, signature, signature_len, rsa);
    EVP_MD_CTX_free(md_ctx_verify);

    if (rsa_verify_result == 1) {
        printf("RSA signature verified.\n");
    } else {
        printf("RSA signature verification failed.\n");
    }
}

int main() {
    // Initialize DSA
    DSA *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(dsa);

    // Initialize RSA
    RSA *rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
    
    printf("Message: %s\n", MESSAGE);
    printf("Signing and verifying with DSA:\n");
    dsa_sign_and_verify(dsa, (const uint8_t *)MESSAGE, strlen(MESSAGE));
    printf("\nSigning and verifying with RSA:\n");
    rsa_sign_and_verify((const uint8_t *)MESSAGE, strlen(MESSAGE), rsa);

    // Free memory
    DSA_free(dsa);
    RSA_free(rsa);

    return 0;
}
