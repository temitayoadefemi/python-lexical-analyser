#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h> 
#include "bst.c"



typedef enum {
  _KEYWORD_,
  _SEPERATOR_,
  _VALUE_,
} TYPE;


typedef enum {
   _FOR_,
   _IN_,
} KEYWORD;


typedef enum {
    _EQUALS_,
} SEPERATOR;


typedef enum {
    _INT_,
    _FLOAT_,
    _STRING_,
} VALUE;


typedef struct {
    TYPE token_type;
    VALUE token_value;
} TOKEN;



int main() {
    FILE *file;
    char line[256];

    // Open the file
    file = fopen("file.py", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        char value[256] = {0};
        int valueIndex = 0;
        int capturing_value = 0; // Flag to start capturing the value after '='
        int captured = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            if (isalnum(line[i]) || line[i] == '_') { // Accept alphanumeric characters and underscore
                value[valueIndex++] = line[i];
            } else {
                if (valueIndex > 0) {
                    value[valueIndex] = '\0'; // Null-terminate the captured sequence
                    printf("Sequence: %s\n", value);
                    valueIndex = 0; // Reset for next capture
                }
            }
        }

        // Final check at the end of the line
        if (valueIndex > 0) {
            value[valueIndex] = '\0';
            printf("Sequence: %s\n", value);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
