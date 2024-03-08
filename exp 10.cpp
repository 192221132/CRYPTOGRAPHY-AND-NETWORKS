#include <stdio.h>
#include <string.h>

#define SIZE 5

void findChar(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (matrix[*row][*col] == ch)
                return;
}

void encryptPlayfair(char matrix[SIZE][SIZE], char message[]) {
    int len = strlen(message);

    for (int i = 0; i < len - 1; i += 2) {
        if (message[i] == message[i + 1]) {
            len++;
            for (int j = len - 1; j > i + 1; j--) {
                message[j] = message[j - 1];
            }
            message[i + 1] = 'X';
        }
    }

    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findChar(matrix, message[i], &row1, &col1);
        findChar(matrix, message[i + 1], &row2, &col2);

        if (row1 == row2) {
            col1 = (col1 + 1) % SIZE;
            col2 = (col2 + 1) % SIZE;
        } else if (col1 == col2) {
            row1 = (row1 + 1) % SIZE;
            row2 = (row2 + 1) % SIZE;
        } else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c", matrix[row1][col1], matrix[row2][col2]);
    }

    printf("\n");
}

int main() {
    char matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char message[] = "Must see you over Cadogan West. Coming at once";

    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nEncrypted Message: ");
    encryptPlayfair(matrix, message);

    return 0;
}

