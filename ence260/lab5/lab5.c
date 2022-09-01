#include <stdio.h>
#include <stdint.h>
#include <string.h>


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

size_t readString(char* string, size_t maxStringLength) {
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

FILE* openInputFile(char* filename)
{
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Input file can't be opened");
    }
    return f;
}

int main(void) {
    char filename[80];
    readString(filename, 80);
    FILE* f = openInputFile(filename);
    if (f == NULL) {
        return 0;
    }
    char c = getchar();
    char* data;
    int total = 0;
    int err = fscanf(f, data);
    fclose(f);
    printf("%d", err);
    printf("data?");
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == c) {
            total++;
        }
    }
    printf("sddfs%d", total);
}