#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int val;
    struct _Node *prev, *next;
} Node;

typedef struct _LinkedList {
    Node *head;
} LinkedList;

LinkedList *init_linkedlist() {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;

    return list;
}

void add_node(Node *node_prev, int node_data) {}
void remove_node(Node *node);
void print_linkedlist(LinkedList *list);

int main(int argc, char *argv[]) { return 0; }
