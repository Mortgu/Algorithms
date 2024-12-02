#include <stdlib.h>
#include <stdio.h>

#include "avl.h"

int main(int argc, char **argv) {
    Node *root = (Node*) malloc(sizeof(Node));

    if (root == NULL) {
        fprintf(stderr, "Failed to allocate memory for root node!");
        return 1;
    }

    root->key = 100;
    root->height = 0;
    root->left = NULL;
    root->right = NULL;

    insert(&root, 120);
    insert(&root, 90);
    insert(&root, 80);
    insert(&root, 70);
    //insert(root, 60);

    printNodes(root, 0);

    return 0;
}

void insert(Node **root, int key) {
    if (*root == NULL) {
        *root = createNode(key, 0, NULL, NULL);
        return;
    }

    if (key <= (*root)->key) {
        insert(&((*root)->left), key);
        checkRotationRight(root);
    } else {
        insert(&((*root)->right), key);
        checkRotationRight(root);
    }

    updateHeight(*root);
}

int max(int a, int b) {
    if (a < b) return b;
    else return a;
}

int getHeight(Node *root) {
    return root ? root->height : -1;
}

void updateHeight(Node *root) {
    if (root) {
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    }
}

// Funktion zur Initialisierung eines neuen Knotens
Node* createNode(int key, int height, Node *left, Node *right) {
    Node *node = (Node*) malloc(sizeof(Node));

    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for new Node!\n");
        return NULL;
    }

    node->key = key;
    node->height = height;
    node->left = left;
    node->right = right;

    return node;
}

// Left Rotation
// Laufzeit: O(1) - Die Rotation und Höhenaktualisierung sind konstante Zeitoperationen.
void rotateLeft(Node** root) {
    Node* b = (*root)->right;

    (*root)->right = b->left;
    b->left = *root;
    *root = b;

    updateHeight((*root)->left); // O(1) - Höhe eines Knotens zu aktualisieren ist eine konstante Zeitoperation.
    updateHeight(*root);         // O(1) - Höhe eines Knotens zu aktualisieren ist eine konstante Zeitoperation.
}

// Right Rotation
// Laufzeit: O(1) - Die Rotation und Höhenaktualisierung sind konstante Zeitoperationen.
void rotateRight(Node** root) {
    Node* b = (*root)->left;

    (*root)->left = b->right;
    b->right = *root;
    *root = b;

    updateHeight((*root)->right); // O(1) - Höhe eines Knotens zu aktualisieren ist eine konstante Zeitoperation.
    updateHeight(*root);          // O(1) - Höhe eines Knotens zu aktualisieren ist eine konstante Zeitoperation.
}

// Double Rotation Left
// Laufzeit: O(1) - Besteht aus zwei Rotationen, jede Rotation ist eine konstante Zeitoperation.
void doubleRotationLeft(Node *root) {
    rotateRight(&(root->right)); // O(1) - Eine einzelne Rechtsrotation.
    rotateLeft(&root);           // O(1) - Eine einzelne Linksrotation.
}

void doubleRotationRight(Node *root) {
    rotateLeft(&(root->left));
    rotateRight(&root);
}

void checkRotationLeft(Node **root) {
    if (*root != NULL) {
        if ((*root)->right != NULL) {
            if (getHeight((*root)->right) - getHeight((*root)->left) == 2) {
                if (getHeight((*root)->right->left) > getHeight((*root)->right->right)) {
                    rotateRight(&((*root)->right));
                    rotateLeft(root);
                } else {
                    rotateLeft(root);
                } 
            }  else {
                updateHeight(*root);
            }
        } else {
            updateHeight(*root);
        }   
    }
}

void checkRotationRight(Node **root) {
    if (*root != NULL) {
        if ((*root)->left != NULL) {
            if (getHeight((*root)->left) - getHeight((*root)->right) == 2) {
                if (getHeight((*root)->left->right) > getHeight((*root)->left->left)) {
                   rotateLeft(&((*root)->left));
                   rotateRight(root);
                } else {
                    rotateRight(root);
                } 
            }  else {
                updateHeight(*root);
            }
        } else {
            updateHeight(*root);
        }   
    }
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

void delete(Node **root, int key) {
    if (*root == NULL)
        return;

    if (key < (*root)->key) {
        delete(&((*root)->left), key);
    } else if (key > (*root)->key) {
        delete(&((*root)->right), key);
    } else {
        if ((*root)->left == NULL || (*root)->right == NULL) {
            Node *temp = (*root)->left ? (*root)->left : (*root)->right;

            if (temp == NULL) {
                temp = *root;
                *root = NULL;
            } else {
                **root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode((*root)->right);
            (*root)->key = temp->key;
            delete(&((*root)->right), temp->key);
        }
    }

    if (*root == NULL)
        return;

    updateHeight(*root);

    int balance = getBalance(*root);

    if (balance > 1 && getBalance((*root)->left) >= 0)
        *root = rightRotate(*root);

    if (balance > 1 && getBalance((*root)->left) < 0) {
        (*root)->left = leftRotate((*root)->left);
        *root = rightRotate(*root);
    }

    if (balance < -1 && getBalance((*root)->right) <= 0)
        *root = leftRotate(*root);

    if (balance < -1 && getBalance((*root)->right) > 0) {
        (*root)->right = rightRotate((*root)->right);
        *root = leftRotate(*root);
    }
}

void deleteIterative(Node **root, int key) {
    Node *parent = NULL;
    Node *current = *root;

    // Step 1: Find the node to be deleted
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) return;

    if (current->left == NULL || current->right == NULL) {
        Node *newCurr = (current->left == NULL) ? current->right : current->left;

        if (parent == NULL) {
            *root = newCurr;
        } else if (current == parent->left) {
            parent->left = newCurr;
        } else {
            parent->right = newCurr;
        }
        free(current);
    } else {
        Node *p = NULL;
        Node *temp = current->right;

        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }

        if (p != NULL) {
            p->left = temp->right;
        } else {
            current->right = temp->right;
        }

        current->key = temp->key;
        free(temp);
    }

    Node *node = parent;
    while (node != NULL) {
        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            rotateRight(&node);
        } else if (balance > 1 && getBalance(node->left) < 0) {
            rotateLeft(&(node->left));
            rotateRight(&node);
        } else if (balance < -1 && getBalance(node->right) <= 0) {
            rotateLeft(&node);
        } else if (balance < -1 && getBalance(node->right) > 0) {
            rotateRight(&(node->right));
            rotateLeft(&node);
        }

        node = (parent == NULL) ? NULL : ((key < parent->key) ? parent->left : parent->right);
    }
}

void printNodes(Node *root, int space) {
    if (root == NULL)
        return;

    int indent = 5;
    space += indent;

    printNodes(root->right, space);

    printf("\n");
    for (int i = indent; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    printNodes(root->left, space);
}
