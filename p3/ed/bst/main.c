#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _BSTNode {
    int data;
    struct _BSTNode *left;
    struct _BSTNode *right;
} BSTNode;

BSTNode *bst_init(int data) {
    BSTNode *bst = malloc(sizeof(BSTNode));

    bst->data = data;
    bst->left = NULL;
    bst->right = NULL;

    return bst;
}

typedef struct _QueueNode {
    BSTNode *data;
    struct _QueueNode *next;
} QueueNode;

typedef struct _Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *q_create_queue() {
    Queue *q = malloc(sizeof(Queue));

    if (q == NULL) {
        fprintf(stderr, "Could not alocate the queue\n");
        return NULL;
    }

    q->front = q->rear = NULL;

    return q;
}

QueueNode *q_create_node(BSTNode *data) {
    QueueNode *n = malloc(sizeof(QueueNode));

    if (n == NULL) {
        fprintf(stderr, "Couldn't allocate queue node'\n");
        return NULL;
    }

    n->data = data;
    n->next = NULL;

    return n;
}

void enqueue(Queue *q, BSTNode *data) {
    QueueNode *n = q_create_node(data);

    if (n == NULL) {
        return;
    }

    if (q->rear == NULL || q->front == NULL) {
        q->front = q->rear = n;
        return;
    }

    q->rear->next = n;
    q->rear = n;
}

BSTNode *dequeue(Queue *q) {
    if (q->front == NULL && q->rear == NULL) {
        return NULL;
    }

    QueueNode *temp = q->front;
    BSTNode *n = temp->data;
    q->front = q->front->next;

    free(temp);
    return n;
}

void bst_insert(BSTNode **head, BSTNode *n) {
    if (*head == NULL) {
        *head = n;
    } else if (n->data <= (*head)->data) {
        bst_insert(&(*head)->left, n);
    } else {
        bst_insert(&(*head)->right, n);
    }
}

void bst_print(BSTNode *head) {
    Queue *q = q_create_queue();

    if (q == NULL) {
        return;
    }

    enqueue(q, head);

    while (q->front != NULL) {
        BSTNode *node = dequeue(q);
        printf("%d ", node->data);

        if (node->left) {
            enqueue(q, node->left);
        }

        if (node->right) {
            enqueue(q, node->right);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    char *operation;
    int number;
    BSTNode *head = NULL;

    do {
        char *line = NULL;
        size_t n = 0;

        getline(&line, &n, stdin);
        operation = strsep(&line, " ");

        switch (operation[0]) {
        case 'i':
            bst_insert(&head, bst_init(atoi(strsep(&line, "\n"))));
            break;
        case 'p':
            bst_print(head);
            break;
        default:
            break;
        }
    } while (!feof(stdin));

    return 0;
}
