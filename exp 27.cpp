#include <stdio.h>
void frequency_analysis_attack(int* encrypted_text, int length);
int main() {
    int encrypted_text[] = {105, 34, 72, 105, 34, 2, 20, 2, 72, 2, 19, 19, 105, 72, 19, 2, 19, 105, 2, 20};

    int length = sizeof(encrypted_text) / sizeof(encrypted_text[0]);
    frequency_analysis_attack(encrypted_text, length);
    return 0;
}

void frequency_analysis_attack(int* encrypted_text, int length) {
    int frequency[26] = {0};
    for (int i = 0; i < length; i++) {
        int encrypted_num = encrypted_text[i];
        frequency[encrypted_num]++;
    }
    int most_frequent_num = 0;
    int max_frequency = 0;
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > max_frequency) {
            max_frequency = frequency[i];
            most_frequent_num = i;
        }
    }
    char guessed_letter = 'A' + (most_frequent_num % 26);
    printf("Most frequent encrypted number: %d\n", most_frequent_num);
    printf("Guessed letter: %c\n", guessed_letter);
}

