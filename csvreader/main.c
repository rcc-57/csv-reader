//
//  main.c
//  csvreader
//
//  Created by Иван Агошков on 22.05.2026.
//

#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <string.h>

int main() {

    FILE* file = fopen("test_table.csv", "r");

    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file)) {

        char* token = strtok(line, ",");

        while (token != NULL) {

            printf("[%s]\n", token);

            token = strtok(NULL, ",");
        }

        printf("-----\n");
    }

    fclose(file);

    return 0;
}
