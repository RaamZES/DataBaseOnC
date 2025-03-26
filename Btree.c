#include <stdio.h>
#include <stdlib.h>

#define ORDER 3 

typedef struct BTreeNode {
    int keys[ORDER - 1];
    struct BTreeNode *children[ORDER];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode* createNode(int isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < ORDER; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void traverse(BTreeNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->numKeys; i++) {
        if (!root->isLeaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->isLeaf) traverse(root->children[root->numKeys]);
}

BTreeNode* search(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && root->keys[i] == key) {
        return root;
    }
    if (root->isLeaf) {
        return NULL;
    }
    return search(root->children[i], key);
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    }
}

BTreeNode* insert(BTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    }
    insertNonFull(root, key);
    return root;
}

int main() {
    BTreeNode* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 30);
    root = insert(root, 7);
    root = insert(root, 17);

    printf("Traversal of B-tree: ");
    traverse(root);
    printf("\n");

    int key = 6;
    if (search(root, key))
        printf("Key %d found in B-tree.\n", key);
    else
        printf("Key %d not found.\n", key);

    return 0;
}
