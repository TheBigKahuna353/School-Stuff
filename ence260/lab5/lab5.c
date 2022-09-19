#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// int main(void)
// {
//     int c;
//     do {
//         c = getchar();
//         if (c == EOF) {
//             break;
//         }
//         if (c >= 'a') {
//             printf("'%c': Letter %d\n", c, c - 96);
//         } else if (c >= 'A') {
//             printf("'%c': Letter %d\n", c, c - 64);
//         } else if (c == '\n') {
//             printf("'\\n'\n");
//         } else if (c >= '0') {
//             printf("'%c': Digit %d\n", c, c - 48);
//         } else {
//             printf("'%c': Non-alphanumeric\n", c);
//         }
//     } while (c != EOF);
// }

size_t readString(char* string, size_t maxStringLength)
{
    size_t len = 0;
    int c;
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n' || len >= maxStringLength) {
            for (int i = len; i < maxStringLength; i++) {
                string[i] = 0;
            }
            return len;
        }
        string[len] = c;
        len++;
    }
}

size_t readStringFile(FILE* file, char* string, size_t maxStringLength)
{
    size_t len = 0;
    int c;
    while (1) {
        c = getc(file);
        if (c == EOF || len >= maxStringLength) {
            for (int i = len; i < maxStringLength; i++) {
                string[i] = 0;
            }
            return len;
        }
        string[len] = c;
        len++;
    }
}

FILE* openInputFile(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Input file can't be opened\n");
    }
    return file;
}

FILE* openOutputFile(char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Output file can't be opened\n");
    }
    return file;
}


// int main(void)
// {
//     char inputName[80];
//     char outputName[80];

//     readString(inputName, 80);
//     readString(outputName, 80);

//     FILE* inputFile = openInputFile(inputName);
//     FILE* outputFile = openOutputFile(outputName);
//     if (inputFile == NULL || outputFile == NULL) {
//         if (inputFile != NULL) {
//             fclose(inputFile);
//         } else if (outputFile != NULL) {
//             fclose(outputFile);
//         }
//         return 1;
//     }

//     char c = getc(inputFile);
//     bool toUp = true;
//     do {
//         if (c == ' ' || c == '\n') {
//             toUp = true;
//         } else if (toUp) {
//             c = toupper(c);
//             toUp = false;
//         } else {
//             c = tolower(c);
//         }
//         putc(c, outputFile);
//         c = getc(inputFile);
//     } while (c != EOF);
//     fclose(inputFile);
//     fclose(outputFile);
// }

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++) {
        printf("[%d] %s", i, argv[i]);
    }
}