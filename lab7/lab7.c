#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define ERROR_ALLOCATION (-1)

struct Directory;
typedef struct Directory* root;
typedef struct Directory {
	char name[MAX_SIZE];
	root parent;
	root subDir;
} directory;

struct Stack;
typedef struct Stack* positionStack;
typedef struct Stack {
	root dirLevel;
	positionStack next;
} stack;

//Function prototypes
 root makeDirectory(char name[MAX_SIZE]);
 root makeSubDirectory(char name[MAX_SIZE], root currentDir);
 root changeDirectory(char name[MAX_SIZE], root currentDir);
 int listDirectory(root currentDir);

 root pop(positionStack headStack);
 void push(positionStack headStack, root dirLevel);
 root createNew(root dirLevel);



int main() {

	directory headDir = { .name = {0}, .parent = NULL, .subDir = NULL };
	stack headStack = { .dirLevel = NULL, .next = NULL };

	root startDir = rootDir("C:");
	headDir.subDir = rootDir;

	root currentDir = rootDir;

	push(&headStack, currentDir);

	char name[MAX_SIZE];
	int choice;

	while (choice != 0) {
		printf("Menu:\n");
		printf("1) md\n2) cd dir\n3) cd...\n4) dir\n0) Exit");
		printf("\n");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			printf("\nName of new directory: ");
			scanf("%s", &name);
			printf("\n");
			makeSubDirectory(name, currentDir);
			break;

		case 2:
			printf("\nName of directory: ");
			scanf("%s", &name);
			root newDir = changeDirectory(name, currentDir);
			if (newDir != currentDir) {
				push(&headStack, currentDir);
				currentDir = newDir;
			}
			break;

		case 3:
			if (currentDir != rootDir) {
				currentDir = pop(&headStack);
				printf("\nCurrently in %s ", currentDir->name);
				printf("\n");
			}
			else printf("\nAlready in root directory!");
			break;

		case 4:
			listDirectory(currentDir);
			break;

		case 0:
			printf("\nEnd!");
			break;

		default:
			printf("Invalid input!");
		}
		
	}

	free(rootDir);

	return 0;

}

root makeDirectory(char name[MAX_SIZE]) {
	root newDir = (root)malloc(sizeof(directory));
	if (newDir == NULL) {
		printf("Failed to allocate memory!");
		return ERROR_ALLOCATION;
	}

	strcpy(newDir->name, name);
	newDir->parent = NULL;
	newDir->subDir = NULL;
	return newDir;
}

root makeSubDirectory(char name[MAX_SIZE], root currentDir) {

	root newDir = makeDirectory(name);
	newDir->parent = currentDir->subDir;
	currentDir->subDir = newDir;
	return newDir;
}

root changeDirectory(char name[MAX_SIZE], root currentDir) {

	root subDir = currentDir->subDir;
	while (subDir != NULL) {
		if (strcmp(subDir->name, name) == 0) {
			return subDir;
		}
		subDir = subDir->subDir;
	}

	printf("Directory %s not found!", name);
	return currentDir;
}

int listDirectory(root currentDir) {

	printf("Directory %s contents:", currentDir->name);
	root subDir = currentDir->subDir;
	while (subDir != NULL) {
		printf("\n -%s\n", subDir->name);
		subDir = subDir->subDir;
	}

	if (currentDir->subDir == NULL) {
		printf("\n(empty)");
	}

	return EXIT_SUCCESS;
}

root pop(positionStack headStack) {
	positionStack toDelete = headStack->next;

	if (!toDelete) {
		printf("Stack is empty!");
		return headStack->dirLevel;
	}

	headStack->next = toDelete->next;
	root dirLevel = toDelete->dirLevel;
	free(toDelete);

	return dirLevel;
}

void push(positionStack headStack, root dirLevel) {

	positionStack newElement = (positionStack)malloc(sizeof(stack));
	if (newElement == NULL) {
		printf("Failed to allocate memory!");
		exit(ERROR_ALLOCATION);
	}

	newElement->dirLevel = dirLevel;
	newElement->next = NULL;

	return newElement;
}