//
//  main.c
//  csvreader
//
//  Created by Иван Агошков on 22.05.2026.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

char* table[MAX_ROWS][MAX_COLS];

int main() {

    FILE* file = fopen("test_table.csv", "r");

    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char line[1024];

    int row = 0;

    while (fgets(line, sizeof(line), file)) {

        // убрать \n
        line[strcspn(line, "\n")] = 0;

        int col = 0;

        char* token = strtok(line, ",");

        while (token != NULL) {

            table[row][col] = token;

            col++;
            token = strtok(NULL, ",");
        }

        row++;
    }

    fclose(file);

    // --- проверочный вывод таблицы ---
    printf("\nPARSED TABLE:\n");

    for (int i = 0; i < row; i++) {
        for (int j = 0; table[i][j] != NULL && j < MAX_COLS; j++) {
            printf("[%s] ", table[i][j]);
        }
        printf("\n");
    }

    return 0;
}
