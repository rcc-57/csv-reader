#ifndef CSV_H
#define CSV_H

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_CELL_LENGTH 256

extern char* table[MAX_ROWS][MAX_COLS];

int load_csv(const char* filename);
void free_table(int rows);

#endif
