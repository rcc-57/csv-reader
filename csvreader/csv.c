//
//  main.c
//  csvreader
//
//  Created by Иван Агошков on 19.05.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

char* table[MAX_ROWS][MAX_COLS];

void parse_csv_line(char* line, int row) {

    int col = 0;
    int char_index = 0;

    char current_cell[MAX_CELL_LENGTH];

    for (int i = 0;; i++) {

        char c = line[i];

        if (c == ',' || c == '\0') {

            current_cell[char_index] = '\0';

            table[row][col] = strdup(current_cell);

            if (table[row][col] == NULL) {

                printf("Memory allocation failed\n");
                exit(1);
            }

            col++;
            char_index = 0;

            if (c == '\0') {
                break;
            }
        }
        else {

            if (char_index >= MAX_CELL_LENGTH - 1) {

                printf("Cell too long\n");
                exit(1);
            }

            current_cell[char_index++] = c;
        }
    }
}

int load_csv(const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {

        printf("Cannot open file: %s\n", filename);
        return -1;
    }

    char line[1024];

    int row = 0;

    while (fgets(line, sizeof(line), file)) {

        if (row >= MAX_ROWS) {

            printf("Too many rows\n");
            fclose(file);
            return -1;
        }

        line[strcspn(line, "\n")] = '\0';

        parse_csv_line(line, row);

        row++;
    }

    fclose(file);

    return row;
}

void print_table(int rows) {

    printf("\nRESULT TABLE:\n\n");

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < MAX_COLS && table[i][j] != NULL; j++) {

            printf("[%s] ", table[i][j]);
        }

        printf("\n");
    }
}

void free_table(int rows) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < MAX_COLS && table[i][j] != NULL; j++) {

            free(table[i][j]);
        }
    }
}
