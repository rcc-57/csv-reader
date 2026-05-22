//
//  Untitled.c
//  csvreader
//
//  Created by Иван Агошков on 22.05.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "evaluator.h"

int visited[MAX_ROWS][MAX_COLS];

int get_column_index(const char* name) {

    for (int i = 1; i < MAX_COLS; i++) {

        if (table[0][i] == NULL) {
            break;
        }

        if (strcmp(table[0][i], name) == 0) {
            return i;
        }
    }

    return -1;
}

double evaluate_formula(const char* formula);

double get_cell_reference_value(const char* ref) {

    char column_name[64];
    int row_number = 0;

    int i = 1;
    int j = 0;

    while (ref[i] && !(ref[i] >= '0' && ref[i] <= '9')) {

        column_name[j++] = ref[i];
        i++;
    }

    column_name[j] = '\0';

    if (ref[i] == '\0') {

        printf("Invalid reference: %s\n", ref);
        return 0;
    }

    row_number = atoi(&ref[i]);

    int col = get_column_index(column_name);

    if (col == -1) {

        printf("Unknown column: %s\n", column_name);
        return 0;
    }

    if (row_number < 0 || row_number >= MAX_ROWS) {

        printf("Invalid row number: %d\n", row_number);
        return 0;
    }

    return evaluate_cell(row_number, col);
}

double evaluate_formula(const char* formula) {

    char left[128];
    char right[128];

    char op = 0;

    int op_pos = -1;

    for (int i = 0; formula[i]; i++) {

        if (formula[i] == '+' ||
            formula[i] == '-' ||
            formula[i] == '*' ||
            formula[i] == '/') {

            op = formula[i];
            op_pos = i;
            break;
        }
    }

    if (op_pos == -1) {

        printf("Invalid formula: %s\n", formula);
        return 0;
    }

    strncpy(left, formula, op_pos);
    left[op_pos] = '\0';

    strcpy(right, formula + op_pos + 1);

    double left_value;
    double right_value;

    if (left[0] == '$') {
        left_value = get_cell_reference_value(left);
    }
    else {
        left_value = atof(left);
    }

    if (right[0] == '$') {
        right_value = get_cell_reference_value(right);
    }
    else {
        right_value = atof(right);
    }

    switch (op) {

        case '+':
            return left_value + right_value;

        case '-':
            return left_value - right_value;

        case '*':
            return left_value * right_value;

        case '/':

            if (right_value == 0) {

                printf("Division by zero\n");
                return 0;
            }

            return left_value / right_value;
    }

    return 0;
}

double evaluate_cell(int row, int col) {

    if (visited[row][col]) {

        printf("Circular dependency detected at [%d][%d]\n", row, col);
        return 0;
    }

    visited[row][col] = 1;

    char* cell = table[row][col];

    if (cell == NULL) {

        visited[row][col] = 0;
        return 0;
    }

    double result;

    if (cell[0] == '$') {

        result = evaluate_formula(cell);
    }
    else {

        result = atof(cell);
    }

    visited[row][col] = 0;

    return result;
}
