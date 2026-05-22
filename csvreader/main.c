#include <stdio.h>

#include "csv.h"
#include "evaluator.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {

        printf("Usage: ./csvreader <file.csv>\n");
        return 1;
    }

    int rows = load_csv(argv[1]);

    if (rows == -1) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < MAX_COLS && table[i][j] != NULL; j++) {

            if (j > 0) {
                printf(",");
            }

            if (i == 0 || j == 0) {

                printf("%s", table[i][j]);
            }
            else {

                double value = evaluate_cell(i, j);

                printf("%.2f", value);
            }
        }

        printf("\n");
    }

    free_table(rows);

    return 0;
}
