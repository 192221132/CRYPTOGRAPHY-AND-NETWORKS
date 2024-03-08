#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherSequence(char* keyword, char* cipherSequence) {
    int keywordLength = strlen(keyword);
    strcpy(cipherSequence, keyword);
    int used[26] = {0}
    for (int i = 0; i < keywordLength; i++) {
        if (isalpha(keyword[i])) {
            used[toupper(keyword[i]) - 'A'] = 1;
        }
    }
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipherSequence[keywordLength++] = letter;
        }
    }
    cipherSequence[keywordLength] = '\0';
}
int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[27];
    generateCipherSequence(keyword, cipherSequence);
    printf("Keyword: %s\n", keyword);
    printf("Cipher Sequence: %s\n", cipherSequence);
    return 0;
}
