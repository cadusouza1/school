#define MAX_QUEUE_SIZE 1024

typedef struct _Queue {
    int items[MAX_QUEUE_SIZE];
    int size;
} Queue;

Queue queue_init() {
    Queue q;
    q.size = 0;

    return q;
}

void enqueue(Queue *queue) {}

void dequeue(Queue *queue);

int main(int argc, char *argv[]) { return 0; }
