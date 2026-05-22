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

        line[strcspn(line, "\n")] = '\0';

        parse_csv_line(line, row);

        row++;
    }

    fclose(file);

    return row;
}

void free_table(int rows) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < MAX_COLS && table[i][j] != NULL; j++) {

            free(table[i][j]);
        }
    }
}
