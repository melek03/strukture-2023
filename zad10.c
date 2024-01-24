#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGHT (1024)
#define FILE_ERROR (-1)

typedef struct City* CityPosition;
typedef struct City {
	char name[MAX_LENGHT];
	int population;
	CityPosition left;
	CityPosition right;
	CityPosition next;
}City;

typedef struct Country* CountryPosition;
typedef struct Country {
	char name[MAX_LENGHT];
	CityPosition CountrysCities;
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
}Country;

CountryPosition CountryInitialization(CountryPosition);
CountryPosition CreatingListOfCountrys(CountryPosition, char*, char*);
int find(CountryPosition);
int	PrintTree(CityPosition, int);

CityPosition CreatingCityTree(CityPosition, char*, int);
CityPosition CityInitialization(CityPosition);
int CountryPrintList(CountryPosition);
int CityTreePrint(CityPosition);

CountryPosition CreatingCountryTree(CountryPosition, char*, char*);
CityPosition CreatingCityList(CityPosition, char*, int);
int CountryTreePrint(CountryPosition);
int CityListPrint(CityPosition);

int main()
{
	CountryPosition head = NULL;
	head = CountryInitialization(head);
	FILE* filePointer = NULL;
	filePointer = fopen("drzave.txt", "r");
	if (filePointer == NULL) {
		printf("ERROR. Unable to open file.\n");
		return FILE_ERROR;
	}

	char CountrysName[MAX_LENGHT] = { 0 };
	char CountryFile[MAX_LENGHT] = { 0 };

	while (!feof(filePointer))
	{
		fscanf(filePointer, "%s %s", CountrysName, CountryFile);
		head = CreatingListOfCountrys(head, CountrysName, CountryFile);
		head->left = CreatingCountryTree(head->left, CountrysName, CountryFile);
	}
	printf("a)\n");
	CountryPrintList(head->next);
	printf("\n______________\nb)\n");
	CountryTreePrint(head->left);

	find(head);


	fclose(filePointer);

	return EXIT_SUCCESS;
}

CountryPosition CountryInitialization(CountryPosition newElement)
{
	newElement = (CountryPosition)malloc(sizeof(Country));
	if (newElement == NULL) {
		printf("ERROR. Unable to allocate memory.\n");
		return NULL;
	}
	newElement->CountrysCities = NULL;
	strcpy(newElement->name, "0");
	newElement->next = NULL;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}
CountryPosition CreatingListOfCountrys(CountryPosition head, char* CountryName, char* CityFileName)
{
	FILE* filePointer = NULL;
	CountryPosition CurrentCountry = NULL, NewCountry = NULL;
	char CityName[MAX_LENGHT] = { 0 };
	int CityPopulation = 0;
	CurrentCountry = head;
	filePointer = fopen(CityFileName, "r");
	if (filePointer == NULL) {
		printf("ERROR. Unable to open file.\n");
		return NULL;
	}
	while (CurrentCountry->next != NULL && strcmp(CurrentCountry->next->name, CountryName) < 0)
		CurrentCountry = CurrentCountry->next;
	NewCountry = CountryInitialization(NewCountry);
	strcpy(NewCountry->name, CountryName);
	while (!feof(filePointer))
	{
		fscanf(filePointer, " %s %d", CityName, &CityPopulation);
		CityName[strlen(CityName) - 1] = '\0';
		NewCountry->CountrysCities = CreatingCityTree(NewCountry->CountrysCities, CityName, CityPopulation);
	}
	NewCountry->next = CurrentCountry->next;
	CurrentCountry->next = NewCountry;
	fclose(filePointer);
	return head;
}
CityPosition CreatingCityTree(CityPosition node, char* CityName, int CityPopulation)
{
	if (node == NULL) {
		node = CityInitializtion(node);
		strcpy(node->name, CityName);
		node->population = CityPopulation;
		return node;
	}
	else if (CityPopulation >= node->population)
		node->right = CreatingCityTree(node->right, CityName, CityPopulation);
	else if (CityPopulation < node->population)
		node->left = creatingTheTreeOfCities(node->left, CityName, CityPopulation);
	return node;
}
CityPosition CityInitialization(CityPosition NewCity)
{
	NewCity = (CityPosition)malloc(sizeof(City));
	if (NewCity == NULL) {
		printf("ERROR. Unable to allocate memory.\n");
		return NULL;
	}
	NewCity->left = NULL;
	NewCity->right = NULL;
	NewCity->next = NULL;
	strcpy(NewCity->name, "0");
	NewCity->population = 0;
	return NewCity;
}
int CountryPrintList(CountryPosition head)
{
	while (head != NULL)
	{
		printf("\n%s", head->name);
		CityTreePrint(head->CountrysCities);
		printf("\n");
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int CityTreePrint(CityPosition root)
{
	if (root != NULL)
	{
		CityTreePrint(root->left);
		printf("\n%s - %d", root->name, root->population);
		printfCityTree(root->right);
	}
	return EXIT_SUCCESS;
}
CountryPosition CreatingCountryTree(CountryPosition node, char* CountryName, char* CountryFile)
{
	FILE* filePointer = NULL;
	if (node == NULL) {
		char CityName[MAX_LENGHT] = { 0 };
		int CityPopulation = 0;
		node = CountryInitialization(node);
		strcpy(node->name, CountryName);
		filePointer = fopen(CountryFile, "r");
		if (filePointer == NULL) {
			printf("ERROR. Unable to open file.\n");
			return NULL;
		}
		while (!feof(filePointer))
		{
			fscanf(filePointer, " %s %d", CityName, &CityPopulation);
			CityName[strlen(CityName) - 1] = '\0';
			node->CountrysCities = CityListPrint(node->CountrysCities, CityName, CityPopulation);
		}
		fclose(filePointer);
		return node;
	}
	else if (strcmp(node->name, CountryName) < 0)
		node->right = CreatingCityTree(node->right, CountryName, CountryFile);
	else if (strcmp(node->name, CountryName) >= 0)
		node->left = creatingTheTreeOfCountries(node->left, CountryName, CountryFile);
	return node;
}
CityPosition CreatingCityList(CityPosition head, char* CityName, int CityPopulation)
{
	CityPosition currentCity = NULL, newCity = NULL;
	currentCity = head;
	if (currentCity == NULL)
	{
		currentCity = CityInitialization(currentCity);
		strcpy(currentCity->name, CityName);
		currentCity->population = CityPopulation;
		return currentCity;
	}
	else if (currentCity->population > CityPopulation)
	{
		newCity = initializationOfCity(newCity);
		strcpy(newCity->name, CityName);
		newCity->population = CityPopulation;
		newCity->next = currentCity;
		return newCity;
	}
	else
		while (currentCity->next != NULL && (currentCity->next->population < CityPopulation))
			currentCity = currentCity->next;
	newCity = CityInitialization(newCity);
	strcpy(newCity->name, CityName);
	newCity->population = CityPopulation;
	newCity->next = currentCity->next;
	currentCity->next = newCity;
	return head;
}
int CountryTreePrint(CountryPosition root)
{
	if (root != NULL)
	{
		printCountryTree(root->left);
		printf("\n%s\n", root->name);
		printCityList(root->CountrysCities);
		printCountryTree(root->right);
	}
	return EXIT_SUCCESS;
}
int CityListPrint(CityPosition head)
{
	while (head != NULL)
	{
		printf("%s - %d\n", head->name, head->population);
		head = head->next;
	}
	return EXIT_SUCCESS;
}
int find(CountryPosition head)
{
	char countryName[MAX_LENGHT] = { 0 };
	int findPopulation = 0;
	printf("\nUnesi koju drzavu zelite pretraziti: ");
	scanf(" %s", countryName);
	printf("Unesite broj populacije: ");
	scanf("%d", &findPopulation);

	//PRETRAGA PREKO LISTE DRZAVA
	CountryPosition current = NULL;
	current = head->next;
	while (current != NULL && strcmp(current->name, countryName))
		current = current->next;
	if (current != NULL) {
		CityPosition rootCity = NULL;
		rootCity = current->CountrysCities;
		printf("\nPopis gradova s vecom populacijom od %d:", findPopulation);
		treePrint(rootCity, findPopulation);
	}
	else
		printf("\nPogresan unos, molimo pripazite na veliko i malo slovo!\n");
	return EXIT_SUCCESS;
}
int PrintTree(CityPosition nodeCity, int findPopulation)
{
	if (nodeCity != NULL) {
		treePrint(nodeCity->left, findPopulation);
		if (nodeCity->population > findPopulation)
			printf("\n%s - %d", nodeCity->name, nodeCity->population);
		treePrint(nodeCity->right, findPopulation);
	}
	return EXIT_SUCCESS;
}