#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE (30)
#define MAX_INPUT (1024)
#define FILE_ERROR_OPEN (-1)
#define MAX_STUDENTS (10)
#define MEMORY_ALLOCATION_ERROR (-2)

typedef struct _Student {
	char name[MAX_SIZE];
	char lastname[MAX_SIZE];
	float points;
} student;

int noRows(char* file);
student* readStudentData(int noStudents, char* file);
float maxPoints(int noStudents, student* students);
int printStudentData(int noStudents, student* students, float max);

int main() {

	int noStudents = 0;
	float maximumPoints = 0.0;

	int* absolutePoints = 0;
	int relativePoints = 0;

	noStudents = noRows("students.txt");
	printf("Number of students in the file: %d", noStudents);

	student* students = NULL;

	students = readStudentData(noStudents, "students.txt");

	maximumPoints = maxPoints(noStudents, students);

	printStudentData(noStudents, students, maximumPoints);

	free(students);

	return EXIT_SUCCESS;
}

int noRows(char* file) {
	int counter = 0;

	FILE* filepointer = NULL;
	char buffer[MAX_INPUT] = { 0 };

	filepointer = fopen(file, "r");

	if (!filepointer) {
		printf("Error while opening the file!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filepointer)) {
		fgets(buffer, max_input, fp);
		counter++;
	}

	fclose(filepointer);

	return counter;
}

student* readStudentData(int noStudents, char* file) {
	
	int i = 0;
	FILE* filepointer = NULL;

	student* students = NULL;

	students = (student*)malloc(noStudents * sizeof(student));

	filepointer = fopen(file, "r");

	if (!students) {
		printf("Memory allocation failed!\n");
		free(students);
		return MEMORY_ALLOCATION_ERROR;
	}

	while (!feof(filepointer)) {
		fscanf(filepointer, "%s %s %f", students[i].name, students[i].lastname, &students[i].points);
		i++;
	}

	fclose(filepointer);

	return students;
}

float maxPoints(int noStudents, student* students) {

	float max = 0;
	int i = 0;

	for (i = 0; i < noStudents; i++) {
		if (students[i].points > max) {
			max = students[i].points;
		}
	}

	return max;
}

int printStudentData(int noStudents, student* students, float max) {

	int i = 0;

	printf("\nFirst name\t Last name\t Absolute\t Relative\n");

	for (i = 0; i < noStudents; i++) {

		float relativePoints = 0;
		relativePoints = students[i].points / (float)max * 100;

		printf("%s\t %s\t %f\t %f\t", students[i].name, students[i].lastname, students[i].points, relativePoints);
		printf("\n");
	}

	return EXIT_SUCCESS;
}
