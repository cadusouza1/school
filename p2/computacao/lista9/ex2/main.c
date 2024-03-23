#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 51
#define CAP 32

int main(int argc, char *argv[]) {
    int i, j, size = 0;
    char buffer[CAP][MAX_LINHA];

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    for (size = 0; size < CAP && !feof(in); size++) {
        fgets(buffer[size], MAX_LINHA, in);
        printf("buffer[%d] = %s", size, buffer[size]);
    }

    for (i = size - 1; i >= 0; i--) {
        for (j = strlen(buffer[i]) - 1; j >= 0; j--) {
            fputc(buffer[i][j], out);
        }
    }

    return 0;
}
