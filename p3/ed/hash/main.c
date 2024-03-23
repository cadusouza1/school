#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 8
#define BUFF_SIZE 32

typedef struct _Node {
    int freq;
    char *word;
    struct _Node *next;
} Node;

Node *init_node(char *word, int freq) {
    Node *n = malloc(sizeof(Node));
    n->freq = freq;
    n->word = word;
    n->next = NULL;

    return n;
}

void add_node(Node *before, Node *node) {
    Node *temp = before->next;
    before->next = node;
    node->next = temp;
}

Node *get_node(Node *head, char *word) {
    if (head == NULL) {
        return NULL;
    }

    if (strcmp(head->word, word) == 0) {
        return head;
    }

    return get_node(head->next, word);
}

void print_linked_list(Node *head) {
    if (head == NULL) {
        return;
    }

    /* printf("(\"%s\", %d)", head->word, head->freq); */
    /* if (head->next != NULL) { */
    /*     printf(" -> "); */
    /*     print_linked_list(head->next); */
    /* } else { */
    /*     printf("\n"); */
    /* } */

    for (Node *n = head; n != NULL; n = n->next) {
        printf("(\"%s\", %d)", n->word, n->freq);

        if (n->next != NULL) {
            printf(" -> ");
        }
    }

    printf("\n");
}

typedef struct Hash Hash;
struct Hash {
    Node *vec[HASH_SIZE];
};

Hash *hash_init() {
    Hash *h = malloc(sizeof(Hash));

    for (int i = 0; i < HASH_SIZE; i++) {
        h->vec[i] = NULL;
    }

    return h;
}

int _hash(char *word) {
    int sum = 0;

    for (char *c = &word[0]; *c != '\0'; c++) {
        sum += (int)*c;
    }

    return sum % HASH_SIZE;
}

void print_hash(Hash *hash) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash->vec[i] == NULL) {
            printf("(NULL, 0)\n");
        } else {
            print_linked_list(hash->vec[i]);
        }
    }
}

void hash_insert(Hash *hash, char *word) {
    int hash_val = _hash(word);

    if (hash->vec[hash_val] == NULL) {
        hash->vec[hash_val] = init_node(word, 1);
        return;
    }

    if (strcmp(hash->vec[hash_val]->word, word) == 0) {
        hash->vec[hash_val]->freq++;
        return;
    }

    add_node(hash->vec[hash_val], init_node(word, 1));
}

char *hash_get(Hash *hash, char *word) {
    Node *n = get_node(hash->vec[_hash(word)], word);

    if (n == NULL) {
        return NULL;
    }

    return n->word;
}

Node *hash_max(Hash *hash) {
    Node *max = init_node(NULL, 0);

    for (int i = 0; i < HASH_SIZE; i++) {
        for (Node *n = hash->vec[i]; n != NULL; n = n->next) {
            if (n->freq > max->freq) {
                max = n;
            }
        }
    }

    return max;
}

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

// Removes punctuation and makes all chars lower case
char *purify(char *p) {
    char *pure = calloc(strlen(p), sizeof(char));
    int i = 0;
    char *c;

    for (c = &p[0]; *c != '\0'; c++) {
        if (ispunct(*c)) {
            continue;
        }

        pure[i++] = tolower(*c);
    }

    pure[i] = '\0';
    return pure;
}

typedef struct Words Words;
struct Words {
    int size;
    char **words;
};

Words *parse_words_from_buff(char *buff) {
    int max_size = BUFF_SIZE, size = 0;
    Words *words = calloc(1, sizeof(Words));
    words->words = calloc(max_size, sizeof(char *));
    char *word;

    while ((word = strsep(&buff, " "))) {
        if (size == max_size) {
            max_size *= 2;
            char **new = realloc(words->words, sizeof(char *) * max_size);

            if (words->words == NULL) {
                fprintf(stderr,
                        "Could not reallocate memory for the words buffer\n");
                return NULL;
            }

            if (words->words != new) {
                words->words = new;
            }
        }

        words->words[size] = purify(word);

        size++;
    }

    words->size = size;
    return words;
}

int main(int argc, char *argv[]) {
    Hash *hash = hash_init();
    int i;

    Words *parsed = parse_words_from_buff(read_raw_data_from_stdin());

    for (i = 0; i < parsed->size; i++) {
        hash_insert(hash, parsed->words[i]);
    }

    print_hash(hash);

    Node *max = hash_max(hash);
    printf("(%d, %s)\n", max->freq, max->word);

    return 0;
}
