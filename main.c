#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    _IDENTIFIER_,
    _KEYWORD_,
    _OPERATOR_,
    _LITERAL_,
    _PUNCTUATION_,
    _UNKNOWN_
} TYPE;

typedef struct {
    TYPE token_type;
    char str[256];
} TOKEN;

// Function prototypes
TYPE determine_type(const char *token, TOKEN *t);
void process_line(char *line);

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
        process_line(line);
    }

    // Close the file
    fclose(file);

    return 0;
}

void process_line(char *line) {
    const char *delimiters = " \t\n";
    const char *punctuations = ":()";
    char token[256] = {0};
    int tokenIndex = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char ch = line[i];

        // Check if the character is a delimiter
        if (strchr(delimiters, ch) != NULL) {
            if (tokenIndex != 0) {
                token[tokenIndex] = '\0';
                TOKEN t;
                determine_type(token, &t);
                printf("Token: '%s', Type: %d\n", token, t.token_type);
                tokenIndex = 0;
                token[0] = '\0';
            }
        } else if (strchr(punctuations, ch) != NULL) {
            // Output the current token if there is one
            if (tokenIndex != 0) {
                token[tokenIndex] = '\0';
                TOKEN t;
                determine_type(token, &t);
                printf("Token: '%s', Type: %d\n", token, t.token_type);
                tokenIndex = 0;
            }

            // Output the punctuation as a separate token
            token[0] = ch;
            token[1] = '\0';
            TOKEN t;
            determine_type(token, &t);
            printf("Token: '%s', Type: %d\n", token, t.token_type);
        } else {
            // Add character to token
            token[tokenIndex++] = ch;
        }
    }

    // Check if there's a token left to output at the end of the line
    if (tokenIndex != 0) {
        token[tokenIndex] = '\0';
        TOKEN t;
        determine_type(token, &t);
        printf("Token: '%s', Type: %d\n", token, t.token_type);
    }
}

TYPE determine_type(const char *token, TOKEN *t) {
    static const char *keywords[] = {"for", "in", "print", NULL};
    static const char *operators = "=/+-*";

    // Check if keyword
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            t->token_type = _KEYWORD_;
            strcpy(t->str, token);
            return _KEYWORD_;
        }
    }

    // Check if operator
    if (strlen(token) == 1 && strchr(operators, token[0]) != NULL) {
        t->token_type = _OPERATOR_;
        strcpy(t->str, token);
        return _OPERATOR_;
    }

    // Check if punctuation
    if (strlen(token) == 1 && strchr(":(),", token[0]) != NULL) {
        t->token_type = _PUNCTUATION_;
        strcpy(t->str, token);
        return _PUNCTUATION_;
    }

    // Check if literal (integer for simplicity)
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        t->token_type = _LITERAL_;
        strcpy(t->str, token);
        return _LITERAL_;
    }

    // Default to identifier
    t->token_type = _IDENTIFIER_;
    strcpy(t->str, token);
    return _IDENTIFIER_;
}
