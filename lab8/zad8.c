#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

#define ERROR_ALLOCATION (-1)
#define ELEMENT_NOT_FOUND (-2)


struct TreeNode;
typedef struct TreeNode* root;
typedef struct TreeNode {
	int element;
	root left;
	root right;
} treeNode;

//function prototypes

root createNode(int element);
root insertToNode(root R, int element);
int inOrderPrint(root R);
int postOrderPrint(root R);
int preOrderPrint(root R);
root deleteElement(root R, int element);
int findElement(root R, int element);

int main() {

	root R = NULL;
	int choice, element;

	while (1) {
		printf("Menu:\n");
		printf("1. Insert Element\n");
		printf("2. Inorder Traversal\n");
		printf("3. Preorder Traversal\n");
		printf("4. Postorder Traversal\n");
		printf("5. Delete Element\n");
		printf("6. Find Element\n");
		printf("0. Exit\n");
		printf("Enter: ");
		scanf("%d", &choice);
		printf("---------------------\n");

		switch (choice) {
			case 1:
				printf("\nInput a number: ");
				scanf("%d", &element);
				R = insertToNode(R, element);
				printf("\n");
				break;

			case 2:
				inOrderPrint(R);
				printf("\n");
				break;

			case 3:
				preOrderPrint(R);
				printf("\n");
				break;

			case 4:
				postOrderPrint(R);
				printf("\n");
				break;

			case 5:
				printf("\nEnter element to delete: ");
				scanf("%d", &element);
				R = deleteElement(R, element);
				break;

			case 6:
				printf("Enter element to find: ");
				scanf("%d", &element);
				if (findElement(R, element)) {
					printf("\n%d is in the tree!", element);
				}
				else printf("%d isn't found in the tree!", element);
				break;

			case 0:
				return 0;

			default:
				printf("Invalid choice!");
		}

	}

	return 0;
}

root createNode(int element) {

	root newNode = (root)malloc(sizeof(treeNode));

	//check if memory allocation succeded 
	if (newNode == NULL) {
		printf("Failed to allocate memory!");
		exit(ERROR_ALLOCATION);
	}

	newNode->element = element;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

root insertToNode(root R, int element) {

	if (R == NULL) {
		return createNode(element);
	}

	if (element < R->element) {
		R->left = insertToNode(R->left, element);
	}
	else if (element >= R->element) {
		R->right = insertToNode(R->right, element);
	}

	return R;
}

int inOrderPrint(root R) {

	if (R != NULL) {
		inOrderPrint(R->left);
		printf("%d ", R->element);
		inOrderPrint(R->right);
	}

	return EXIT_SUCCESS;
}


int preOrderPrint(root R) {

	if (R != NULL) {
		printf("%d ", R->element);
		preOrderPrint(R->left);
		preOrderPrint(R->right);
	}

	return EXIT_SUCCESS;
}

int postOrderPrint(root R) {

	if (R != NULL) {
		postOrderPrint(R->left);
		postOrderPrint(R->right);
		printf("%d ", R->element);
	}

	return EXIT_SUCCESS;
}

root deleteElement(root R, int element) {

	if (R == NULL) {
		return R;
	}

	if (element < R->element) {
		R->left = deleteElement(R->left, element);
	}
	else if (element > R->element) {
		R->right = deleteElement(R->right, element);
	}
	else {
		if (R->left == NULL) {
			root temp = R->right;
			free(R);

			return temp;
		}
		else if (R->right == NULL) {
			root temp = R->left;
			free(R);

			return temp;
		}

		root temp = R->right;
		while (temp->left != NULL) {
			temp = temp->left;
		}

		R->element = temp->element;
		R->right = deleteElement(R->right, temp->element);
	}

	return R;
}

int findElement(root R, int element) {

	if (R == NULL) {
		return 0;
	}

	if (element == R->element) {
		return 1;
	}
	else if (element < R->element) {
		return findElement(R->left, element);
	}
	else {
		return findElement(R->right, element);
	}
}


