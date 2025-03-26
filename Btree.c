#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 3
#define MAX_RECORDS 100

typedef struct Record {
    int id;
    char data[256];
} Record;

typedef struct BTreeNode {
    int keys[ORDER - 1];
    Record* records[ORDER - 1];
    struct BTreeNode* children[ORDER];
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
        printf("ID: %d, Data: %s\n", root->records[i]->id, root->records[i]->data);
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

void insertNonFull(BTreeNode* node, Record* record) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > record->id) {
            node->keys[i + 1] = node->keys[i];
            node->records[i + 1] = node->records[i];
            i--;
        }
        node->keys[i + 1] = record->id;
        node->records[i + 1] = record;
        node->numKeys++;
    }
}

BTreeNode* insert(BTreeNode* root, int id, const char* data) {
    Record* newRecord = (Record*)malloc(sizeof(Record));
    newRecord->id = id;
    strncpy(newRecord->data, data, 255);
    newRecord->data[255] = '\0';

    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = id;
        root->records[0] = newRecord;
        root->numKeys = 1;
        return root;
    }
    insertNonFull(root, newRecord);
    return root;
}

int main() {
    BTreeNode* root = NULL;
    root = insert(root, 10, "User A");
    root = insert(root, 20, "User B");
    root = insert(root, 5, "User C");
    root = insert(root, 6, "User D");
    root = insert(root, 12, "User E");
    root = insert(root, 30, "User F");
    root = insert(root, 7, "User G");
    root = insert(root, 17, "User H");

    printf("Database Records:\n");
    traverse(root);
    printf("\n");

    int key = 6;
    BTreeNode* result = search(root, key);
    if (result)
        printf("Record with ID %d found: %s\n", key, result->records[0]->data);
    else
        printf("Record with ID %d not found.\n", key);

    return 0;
}
