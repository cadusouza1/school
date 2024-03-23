typedef enum {
    Black,
    Red,
} NodeColor;

typedef struct _Node {
    int data;
    NodeColor color;
    struct _Node *left, *right, *parent;
} Node;

void insert(Node **root, int data);
void remove(Node **root, int data);
int height(Node **root);
Node *search(Node **root, int data);

int main(int argc, char *argv[]) { return 0; }
