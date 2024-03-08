  #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define TOP_PLAINTEXTS 10


void frequencyAttack(char ciphertext[], int key);
int main() {
    char ciphertext[1000]; 
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    size_t len = strlen(ciphertext);
    if (len > 0 && ciphertext[len - 1] == '\n') {
        ciphertext[len - 1] = '\0';
    }


    frequencyAttack(ciphertext, TOP_PLAINTEXTS);
    return 0;
}
void frequencyAttack(char ciphertext[], int topPlaintexts) {
    int key, count;
    char plaintext[1000]; 
    printf("\nTop %d possible plaintexts:\n", topPlaintexts);
    for (key = 1; key <= ALPHABET_SIZE; ++key) {
        strcpy(plaintext, ciphertext);
        for (count = 0; plaintext[count] != '\0'; ++count) {
            if (plaintext[count] >= 'A' && plaintext[count] <= 'Z') {
                plaintext[count] = ((plaintext[count] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
            } else if (plaintext[count] >= 'a' && plaintext[count] <= 'z') {
                plaintext[count] = ((plaintext[count] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            }
        }

        printf("Key %d: %s\n", key, plaintext);

        if (key == topPlaintexts) {
            break;  
        }
    }
}

