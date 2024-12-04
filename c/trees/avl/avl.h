typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

void insert(Node **root, int key);
void delete(Node **root, int key);
Node* createNode(int key, int height, Node *left, Node *right);
int max(int a, int b);

int getHeight(Node *root);
void updateHeight(Node *root);

void rotateLeft(Node **root);
void rotateRight(Node **root);

void doubleRotationLeft(Node *root);
void doubleRotationRight(Node *root);

void checkRotationLeft(Node **root);
void checkRotationRight(Node **root);

void printNodes(Node *root, int space);