#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 4096

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int find(Subset *subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void union_sets(Subset *subsets, int x, int y) {
    int root_x = find(subsets, x);
    int root_y = find(subsets, y);

    if (subsets[root_x].rank < subsets[root_y].rank)
        subsets[root_x].parent = root_y;
    else if (subsets[root_x].rank > subsets[root_y].rank)
        subsets[root_y].parent = root_x;
    else {
        subsets[root_y].parent = root_x;
        subsets[root_x].rank++;
    }
}

int sort_fn(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

int kruskal(Edge *edges, int num_vertices, int num_edges) {
    int i, e;
    qsort(edges, num_edges, sizeof(Edge), sort_fn);

    Subset *subsets = malloc(num_edges * sizeof(Subset));

    if (subsets == NULL) {
        fprintf(stderr, "Error allocating memory for subsets\n");
        return -1;
    }

    for (i = 0; i < num_edges; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int total_weight = 0;

    for (i = 0, e = 0; e < num_vertices - 1; i++) {
        int root_src = find(subsets, edges[i].src);
        int root_dest = find(subsets, edges[i].dest);

        if (root_src != root_dest) {
            total_weight += edges[i].weight;
            union_sets(subsets, root_src, root_dest);
            e++;
        }
    }

    free(subsets);
    return total_weight;
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

typedef struct {
    int num_vertices;
    int num_edges;
    Edge *edges;
} UserInput;

UserInput *parse_user_input(char *raw_data) {
    UserInput *parsed_buff = malloc(sizeof(UserInput));

    if (parsed_buff == NULL) {
        fprintf(stderr, "Could not allocate memory for parsing user input\n");
        return NULL;
    }

    int max_num_edges = 32;
    parsed_buff->num_edges = 0;
    parsed_buff->edges = malloc(sizeof(Edge) * max_num_edges);

    if (parsed_buff->edges == NULL) {
        fprintf(stderr, "Could not allocate memory for edges\n");
        return NULL;
    }

    parsed_buff->num_vertices = atoi(strsep(&raw_data, "\n"));

    char *c;
    while ((c = strsep(&raw_data, "\n"))) {
        if (c[0] == -1) {
            break;
        }

        if (parsed_buff->num_edges == max_num_edges) {
            max_num_edges *= 2;
            Edge *new =
                realloc(parsed_buff->edges, sizeof(Edge) * max_num_edges);

            if (parsed_buff->edges == NULL) {
                fprintf(stderr, "Could not reallocate memory for edges\n");
                return NULL;
            }

            if (parsed_buff->edges != new) {
                parsed_buff->edges = new;
            }
        }

        parsed_buff->edges[parsed_buff->num_edges].src = atoi(strsep(&c, " "));
        parsed_buff->edges[parsed_buff->num_edges].dest = atoi(strsep(&c, " "));
        parsed_buff->edges[parsed_buff->num_edges].weight =
            atoi(strsep(&c, " "));

        parsed_buff->num_edges++;
    }

    return parsed_buff;
}

int main() {
    UserInput *parsed_buff = parse_user_input(read_raw_data_from_stdin());

    int result = kruskal(parsed_buff->edges, parsed_buff->num_vertices,
                         parsed_buff->num_edges);

    printf("%d", result);

    free(parsed_buff);
    return 0;
}
