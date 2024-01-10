#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ERROR_ALLOCATION (-1)

struct TreeNode;
typedef struct TreeNode* Root;
typedef struct TreeNode {
    int element;
    Root left;
    Root right;
} treenode;

Root insertToNode(Root R, int el);
Root createNode(int el);
int replace(Root R);
int inOrderPrint(Root R);
int random();


int main() {

    Root root = NULL;
    root = insertToNode(root, 2);

    insertToNode(root, 5);
    insertToNode(root, 7);
    insertToNode(root, 8);
    insertToNode(root, 11);
    insertToNode(root, 1);
    insertToNode(root, 4);
    insertToNode(root, 2);
    insertToNode(root, 3);
    insertToNode(root, 7);

    inOrderPrint(root);
    printf("\n");

    replace(root);
    inOrderPrint(root);
    printf("\n");

    Root rootRandom = NULL;
    srand(time(NULL));
    rootRandom = insertToNode(rootRandom, random());
    for (int i = 0; i < 10; i++) {
        insertToNode(rootRandom, random());
    }
    inOrderPrint(rootRandom);
    printf("\n");

    return 0;
}

Root createNode(int el) {
    Root newNode = NULL;
    newNode = (Root)malloc(sizeof(treenode));
    
    if (newNode == NULL) {
        printf("Failed to allocate memory!");
        exit(ERROR_ALLOCATION);
    }
    newNode->element = el;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Root insertToNode(Root R, int el) {
    if (R == NULL) {
        return createNode(el);
    }

    if (el < R->element) {
        R->left = insertToNode(R->left, el);
    }
    else if (el >= R->element) {
        R->right = insertToNode(R->right, el);
    }
    return R;
}

int replace(Root R) {
    if (R == NULL) {
        return 0;
    }
    int left = 0, right = 0;
    left = replace(R->left);
    right = replace(R->right);

    int temp = R->element;
    R->element = left + right;

    return R->element + temp;
}

int inOrderPrint(Root R) {
    if (R != NULL) {
        inOrderPrint(R->left);
        printf("%d ", R->element);
        inOrderPrint(R->right);
    }
    return EXIT_SUCCESS;
}

int random() {
    int min = 10;
    int max = 90;

    return min + rand() % (max - min + 1);
}