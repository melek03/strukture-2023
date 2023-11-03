#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LENGTH 30
#define MEMORY_ALLOCATION_FAILURE -1
#define FAILED_TO_ADD -2
#define FILE_OPEN_ERROR -3

struct _Person;
typedef struct _Person* Person;
typedef struct _Person {
	char name[MAX_LENGTH];
	char lastname[MAX_LENGTH];
	int birthyear;
	Person Next;
} person;

Person createPerson(char* name, char* lastname, int year);
int addToBeginning(Person P, char* name, char* lastname, int year);
int printList(Person P);
int addToEnd(Person P, char* name, char* lastname, int year);
Person findLast(Person P);
Person findPerson(Person P, char* lastname);
int eraseElement(Person P, char* lastname);
Person findPrevious(Person P, char* lastname);
int addPersonAfter(Person P, char* name, char* lastname, int year, char* lastname_to_add_after);
int addPersonBefore(Person P, char* name, char* lastname, int year, char* lastname_to_add_before);
int saveToFile(Person P, char* filename);
int readFromFile(Person P, char* filename);


int main() {

	person Head = { .Next = NULL, .name = {0}, .birthyear = 0 };
	Person P = &Head;

	int choice = 33; //random value 
	char name[MAX_LENGTH] = { 0 };
	char lastname[MAX_LENGTH] = { 0 };
	int year = 0;
	char search_by_last[MAX_LENGTH] = { 0 };
	char element_to_erase[MAX_LENGTH] = { 0 };
	char element_to_add_after[MAX_LENGTH] = { 0 };
	char element_to_add_before[MAX_LENGTH] = { 0 };
	char filename[MAX_LENGTH] = { 0 };

	while (choice != 0) {
		printf("What do you want to do?\n");
		printf("1.Add to start\n2.Print list\n3.Add to end\n4.Find by last name\n5.Erase an element\n6.Add behind element\n7.Add in front of element\n8.Write list into a file\n9.Read list from a file\n0.Exit\n");
		printf("\n");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			printf("\nInput first name, last name and year of birth:\n");
			scanf("%s %s %d", &name, &lastname, &year);
			printf("\n");
			addToBeginning(P, name, lastname, year);
			printf("\n");
			break;

		case 2:
			printList(P);
			break;

		case 3:
			printf("\nInput first name, last name and year of birth:\n");
			scanf("%s %s %d", &name, &lastname, &year);
			addToEnd(P, name, lastname, year);
			break;

		case 4:
			printf("Enter last name to search by: ");
			printf("\n");
			scanf("%s", &search_by_last);
			Person temp = findPerson(P, search_by_last);
			printf("%s %s %d\n", temp->name, temp->lastname, temp->birthyear);
			printf("\n");
			break;

		case 5:
			printf("Enter last name of the person you want to erase: ");
			scanf("%s", &element_to_erase);
			eraseElement(P, element_to_erase);
			printf("Person Deleted!\n");
			printf("\n");
			break;

		case 6:
			printf("\nInput first name, last name and year of birth:\n");
			scanf("%s %s %d", &name, &lastname, &year);
			printf("\nInput last name of the person after who you want to add the new person: ");
			scanf("%s", &element_to_add_after);
			addPersonAfter(P, name, lastname, year, element_to_add_after);
			printf("\n");
			break;

		case 7:
			printf("\nInput first name, last name and year of birth:\n");
			scanf("%s %s %d", &name, &lastname, &year);
			printf("\nInput last name of the person before who you want to add the new person: ");
			scanf("%s", &element_to_add_before);
			addPersonBefore(P, name, lastname, year, element_to_add_before);
			printf("\n");
			break;

		case 8:
			saveToFile(P, "list.txt");
			break;

		case 9:
			readFromFile(P, "list.txt");
			break;

		case 0:
			printf("End!");
			break;

		default:
			printf("Invalid input!");
		}
	}

	return EXIT_SUCCESS;
}

Person createPerson(char* name, char* lastname, int year) {

	Person newPerson = NULL;
	newPerson = (Person)malloc(sizeof(person));

	if (!newPerson) {
		printf("Memory allocation failed!\n");
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastname, lastname);
	newPerson->birthyear = year;
	newPerson->Next = NULL;

	return newPerson;

}

int printList(Person P) {

	Person temp = P->Next;

	printf("List:\n");
	printf("Name:\tlastname:\tbirthyear:\n");
	while (temp) {
		printf("%s\t%s\t%d\n", temp->name, temp->lastname, temp->birthyear);
		temp = temp->Next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int addToBeginning(Person P, char* name, char* lastname, int year) {

	Person newPerson = NULL;
	newPerson = createPerson(name, lastname, year);

	newPerson->Next = P->Next;
	P->Next = newPerson;

	return EXIT_SUCCESS;
}

int addToEnd(Person P, char* name, char* lastname, int year) {

	Person newPerson = NULL;
	Person last = NULL;

	newPerson = createPerson(name, lastname, year);

	if (!newPerson) {
		return FAILED_TO_ADD;
	}

	last = findLast(P);

	newPerson->Next = last->Next;
	last->Next = newPerson;

	return EXIT_SUCCESS;
}

Person findLast(Person P) {

	Person current = P;

	while (current->Next != NULL) {
		current = current->Next;
	}

	return current;
}

Person findPerson(Person P, char* lastname) {
	Person temp = P;

	while (temp) {
		if (strcmp(temp->lastname, lastname) == 0) {
			return temp;
		}

		temp = temp->Next;
	}

	return temp;
}

int eraseElement(Person P, char* lastname) {

	Person toDelete = NULL;
	P = findPrevious(P, lastname);

	if (P != NULL) {
		toDelete = P->Next;
		P->Next = toDelete->Next;

		free(toDelete);
	}

	return EXIT_SUCCESS;
}

Person findPrevious(Person P, char* lastname) {

	while (P != NULL && strcmp(P->Next->lastname, lastname)) {
		P = P->Next;
	}

	if (P == NULL) {
		printf("Person is not a part of the list!\n");
		return NULL;
	}

	return P;
}

/*
3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.

*/

int addPersonAfter(Person P, char* name, char* lastname, int year, char* lastname_to_add_after) {

	Person toAddAfter = findPerson(P, lastname_to_add_after);

	addToBeginning(toAddAfter, name, lastname, year);

	return EXIT_SUCCESS;
}

int addPersonBefore(Person P, char* name, char* lastname, int year, char* lastname_to_add_before) {

	Person toAddBefore = findPrevious(P, lastname_to_add_before);

	addToBeginning(toAddBefore, name, lastname, year);

	return EXIT_SUCCESS;
}

int saveToFile(Person P, char* filename) {

	FILE* file_pointer = NULL;
	file_pointer = fopen(filename, "w");

	if (file_pointer == NULL) {
		printf("Failed to open file!");
		return FILE_OPEN_ERROR;
	}

	while (P != NULL) {
		fprintf(file_pointer, "%s\t%s\t%d\n", P->name, P->lastname, P->birthyear);
		P = P->Next;
	}

	printf("List saved to file!\n");
	fclose(file_pointer);

	return EXIT_SUCCESS;
}

int readFromFile(Person P, char* filename) {

	char array[MAX_LENGTH];

	FILE* file_pointer = NULL;

	file_pointer = fopen(filename, "r");
	Person temp = NULL;

	if (file_pointer == NULL) {
		printf("Failed to open file!\n");
		return FILE_OPEN_ERROR;
	}

	while (fgets(array, MAX_LENGTH, file_pointer) != NULL) {
		printf(" %s", array);
	}

	fclose(file_pointer);

	return EXIT_SUCCESS;

}