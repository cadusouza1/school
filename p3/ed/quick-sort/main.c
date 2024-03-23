#define BUFF_SIZE 4096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_raw_data_from_stdin() {
    char *buff = calloc(BUFF_SIZE, sizeof(char));

    if (buff == NULL) {
        fprintf(stderr, "Could not allocate memory for stdin buffer\n");
        return NULL;
    }

    int i = 0, max_size = BUFF_SIZE;

    while (!feof(stdin)) {
        if (i == max_size) {
            max_size *= 2;
            char *new = realloc(buff, sizeof(char) * max_size);

            if (buff == NULL) {
                fprintf(stderr,
                        "Could not reallocate memory for stdin buffer\n");
                return NULL;
            }

            if (buff != new) {
                buff = new;
            }
        }

        buff[i++] = fgetc(stdin);
    }

    buff[i] = '\0';

    return buff;
}

int *parse_raw_stdin_data_from_buff(char *buff, int *return_size) {
    int *parsed_buff = calloc(BUFF_SIZE, sizeof(int));

    if (parsed_buff == NULL) {
        fprintf(stderr, "Could not allocate memory for the integer buffer\n");
        return NULL;
    }

    char *c;
    int i = 0, max_size = BUFF_SIZE;

    while ((c = strsep(&buff, "\n"))) {
        if (c[0] == -1) {
            continue;
        }

        if (i == max_size) {
            max_size *= 2;
            int *new = realloc(parsed_buff, sizeof(char) * max_size);

            if (parsed_buff == NULL) {
                fprintf(stderr,
                        "Could not reallocate memory for the integer buffer\n");
                return NULL;
            }

            if (parsed_buff != new) {
                parsed_buff = new;
            }
        }

        parsed_buff[i++] = atoi(c);
    }

    *return_size = i;

    return parsed_buff;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int l, int h) {
    int pivot = arr[h];

    int j, i = l - 1;

    for (j = l; j <= h - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[h]);
    return i + 1;
}

void _quick_sort(int *arr, int l, int h) {
    if (l < h) {
        int p = partition(arr, l, h);
        _quick_sort(arr, l, p - 1);
        _quick_sort(arr, p + 1, h);
    }
}

void quick_sort(int *arr, int len) { _quick_sort(arr, 0, len - 1); }

int main(int argc, char *argv[]) {
    int len, i;

    int *nums =
        parse_raw_stdin_data_from_buff(read_raw_data_from_stdin(), &len);

    quick_sort(nums, len);

    for (i = 0; i < len; i++) {
        printf("%d\n", nums[i]);
    }

    return 0;
}
