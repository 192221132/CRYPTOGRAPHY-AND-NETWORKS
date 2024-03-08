#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_PLAINTEXTS 10

void frequencyAttack(char ciphertext[], int topPlaintexts);

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

void calculateFrequency(char text[], int frequency[]) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}


void frequencyAttack(char ciphertext[], int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    int key, count;
    char plaintext[1000];  

    calculateFrequency(ciphertext, frequency);
    int sortedIndex[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        sortedIndex[i] = i;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; ++i) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; ++j) {
            if (frequency[sortedIndex[j]] < frequency[sortedIndex[j + 1]]) {
                int temp = sortedIndex[j];
                sortedIndex[j] = sortedIndex[j + 1];
                sortedIndex[j + 1] = temp;
            }
        }
    }

    printf("\nTop %d possible plaintexts:\n", topPlaintexts);
    for (int attempt = 0; attempt < topPlaintexts; ++attempt) {
        key = sortedIndex[attempt] - ('e' - 'a'); 

        strcpy(plaintext, ciphertext);
        for (count = 0; plaintext[count] != '\0'; ++count) {
            if (isalpha(plaintext[count])) {
                char base = isupper(plaintext[count]) ? 'A' : 'a';
                plaintext[count] = ((plaintext[count] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            }
        }

        printf("Key %d: %s\n", key, plaintext);
    }
}

