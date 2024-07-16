#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libcsv.h"

char** splitString(const char* str, const char* delimiter, int* count) {
    char* temp = strdup(str);
    char* token = strtok(temp, delimiter);
    char** tokens = NULL;
    *count = 0;

    while (token) {
        tokens = realloc(tokens, sizeof(char*) * (*count + 1));
        tokens[*count] = strdup(token);
        (*count)++;
        token = strtok(NULL, delimiter);
    }

    free(temp);
    return tokens;
}

void freeSplitStrings(char** strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

void processCsvData(char* data, const char* selectedColumns, const char* rowFilterDefinitions) {
    int columnCount, filterCount;
    char** columns = splitString(selectedColumns, ",", &columnCount);
    char** filters = splitString(rowFilterDefinitions, "\n", &filterCount);

    char* header = strtok(data, "\n");
    int headerCount;
    char** headers = splitString(header, ",", &headerCount);

    int* selectedIndices = malloc(columnCount * sizeof(int));
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < headerCount; j++) {
            if (strcmp(columns[i], headers[j]) == 0) {
                selectedIndices[i] = j;
                break;
            }
        }
    }

    for (int i = 0; i < columnCount; i++) {
        printf("%s", columns[i]);
        if (i < columnCount - 1) {
            printf(",");
        }
    }
    printf("\n");

    char* row;
    while ((row = strtok(NULL, "\n")) != NULL) {
        int rowCount;
        char** rowValues = splitString(row, ",", &rowCount);
        int match = 1;

        for (int i = 0; i < filterCount; i++) {
            char* filter = filters[i];
            char* colName = strtok(filter, "><=");
            char* value = strtok(NULL, "><=");
            char op = filters[i][strlen(colName)];
            for (int j = 0; j < headerCount; j++) {
                if (strcmp(headers[j], colName) == 0) {
                    if ((op == '>' && !(strcmp(rowValues[j], value) > 0)) ||
                        (op == '<' && !(strcmp(rowValues[j], value) < 0)) ||
                        (op == '=' && !(strcmp(rowValues[j], value) == 0))) {
                        match = 0;
                    }
                    break;
                }
            }
            if (!match) break;
        }

        // Print matching rows
        if (match) {
            for (int i = 0; i < columnCount; i++) {
                printf("%s", rowValues[selectedIndices[i]]);
                if (i < columnCount - 1) {
                    printf(",");
                }
            }
            printf("\n");
        }

        freeSplitStrings(rowValues, rowCount);
    }

    freeSplitStrings(headers, headerCount);
    freeSplitStrings(columns, columnCount);
    freeSplitStrings(filters, filterCount);
    free(selectedIndices);
}


void processCsv(const char csv[], const char selectedColumns[], const char rowFilterDefinitions[]) {
    char* csvData = strdup(csv);
    processCsvData(csvData, selectedColumns, rowFilterDefinitions);
    free(csvData);
}


void processCsvFile(const char csvFilePath[], const char selectedColumns[], const char rowFilterDefinitions[]) {
    FILE* file = fopen(csvFilePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", csvFilePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* csvData = malloc(fileSize + 1);
    fread(csvData, 1, fileSize, file);
    csvData[fileSize] = '\0';

    fclose(file);

    processCsvData(csvData, selectedColumns, rowFilterDefinitions);
    free(csvData);
}
