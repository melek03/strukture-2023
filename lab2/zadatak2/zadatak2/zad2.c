/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
	A. dinamički dodaje novi element na početak liste,
	B. ispisuje listu,
	C. dinamički dodaje novi element na kraj liste,
	D. pronalazi element u listi (po prezimenu),
	E. briše određeni element iz liste,
	U zadatku se ne smiju koristiti globalne varijable.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define max_length 30
#define FILE_OPEN_ERROR (-1)
#define FAILED_TO_ALLOCATE (-2)
#define FAILED_TO_ADD (-3)

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
	char name[max_length];
	char lastname[max_length];
	int birthyear;
	Position Next;
} person;

int addToBeginning(Position P, char* name, char* lastname, int yob);
int printList(Position P);
int addToEnd(Position P, char* name, char* lastname, int yob);
Position findPerson(Position P, char* lastname);
int eraseElement(char* surname, Position Head);
int insertAfter(Position P, Position newPerson);
Position findLast(Position Head);

Position createPerson(char* name, char* lastname, int yob) {		//yob - year of birth

	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(person));		//memory allocation for the person we want to add to list
	if (!newPerson) {
		printf("Error while allocating memory!");
		return FAILED_TO_ALLOCATE;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastname, lastname);
	newPerson->birthyear = yob;
	
	newPerson->Next = NULL;

	return newPerson;

}


int main() {

	person Head = { .Next = NULL, .name = {0}, .lastname = {0}, .birthyear = {0} }; //automatically sets every element of a structure to 0
	Position P = &Head;

	int choice = 11;
	int exit = 0;

	char name[max_length] = { 0 };
	char lastname[max_length] = { 0 };
	char search_by_last[max_length] = { 0 };
	char element_to_erase[max_length] = { 0 };
	int year = 0;
	

	while (choice != 0) {
		printf("What do you want to do?\n");
		printf("1.Add to start\n2.Print list\n3.Add to end\n4.Find by last name\n5.Erase an element\n");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Input first name, last name and year of birth:\n");
				scanf("%s %s %d", &name, &lastname, &year);
				addToBeginning(P, name, lastname, year);
				break;
			
			case 2: 
				printList(P);
				break;

			case 3:
				printf("Input first name, last name and year of birth:\n");
				scanf("%s %s %d", &name, &lastname, &year);
				addToEnd(P, name, lastname, year);
				break;

			case 4:
				printf("Enter last name to search by: ");
				scanf("%s", &search_by_last);
				Position temp = findPerson(P, search_by_last);
				printf("%s %s %d", temp->name, temp->lastname, temp->birthyear);
				break;

			case 5:
				printf("Enter last name of the person you want to erase: ");
				scanf("%s", &element_to_erase);
				eraseElement(P, element_to_erase);
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

int addToBeginning(Position Head, char* name, char* lastname, int yob) {		//yob - year of birth
	
	Position newPerson = NULL;

	newPerson = createPerson(name, lastname, yob);

	addToEnd(Head, newPerson->name, newPerson->lastname, newPerson->birthyear);

	return EXIT_SUCCESS;
}

int printList(Position first) {
	
	Position temp = first->Next;

	printf("\nList:\n");

	while (temp) {
		printf("First name\tLast name\tYear of Birth");
		printf("%s\t%s\t%d\n", temp->name, temp->lastname, temp->birthyear);

		temp = temp->Next;
	}

	return EXIT_SUCCESS;
}

int addToEnd(Position Head, char* name, char* lastname, int yob) {

	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson(name, lastname, yob);

	if (!newPerson) {
		return FAILED_TO_ADD;
	}

	last = findLast(Head);
	insertAfter(last, newPerson);

	return EXIT_SUCCESS;

}

Position findPerson(Position first, char* lastname)
{
	Position temp = first;

	while (temp){
		if (strcmp(temp->lastname, lastname) == 0){		//strcmp can (also) compare >, <, alphabetically
			return temp;
		}
		
		temp = temp->Next;
	}

	return temp;
}

Position findLast(Position Head) {

	Position current = Head;

	while (current->Next != NULL) {
		current = current->Next;
	}

	return current;
}

int insertAfter(Position P, Position newPerson) {

	newPerson->Next = P->Next;
	P->Next = newPerson;

	return EXIT_SUCCESS;
}

int eraseElement(char* lastname, Position Head) {

	Position before = Head;
	Position toErase = before->Next;

	int tracker = 0;

	while (toErase != NULL) {
		if (strcmp(toErase, lastname) == 0) {
			toErase = before->Next;
			before->Next = toErase->Next;

			free(toErase);
			tracker  = 1;

			break;
		}
	}

	if (tracker == 0) {
		printf("Person doesn't exist!");
	}

	return EXIT_SUCCESS;
}