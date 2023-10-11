#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max_size (50)
#define max_line (1024)
#define FILE_ERROR_OPEN (-1) //ako ga koristimo vise puta + ako radimo s nekin pa da se oni ne misle sta nan znaci random ass -1

typedef struct _student {
	char name[max_size];
	char surname[max_size];
	double points;
} student;

int readNOrowsInFile() {

	int counter = 0;

	FILE *fp=NULL;
	fp = fopen("students.txt", "r");

	fclose(fp);
	while (!feof(fp)) {   //feof prolazi kroz cijeli file i vraća nam neki pozitivni broj dok ne dođe do nekog exit znaka

		fgets(buffer, max_line, fp); //buffer zapisuje sve što pročita,
		counter++;

	}
	

}

int main() {

	/*int norows = 0; //uvik inicijalizirat varijablu na neki value da ne bude trash value
	printf("%d",norows);*/

	int norows = 0;

	norows = ime funkcije koja je gori;
	FILE *fp = NULL; //bitno inicijalizirati na nulu da znamo da je prazan
	char buffer[max_line] = {0};

	fp = fopen("students.txt", "r"); //stavi taj dokument u isti folder inace triba napisat cilu putanju; postoji w-write, r-read, a-"append" (a dodaje nakon zadnjeg elementa, w bi prebrisa sve sta vec pise u fileu) 
	if (!fp) {
		printf("file is not open\n");
		/*return -1; //moze se stavit bilo sta, al vako znamo da ako se nesto lose zavrsi da ce nan pokazat -1 */
		return FILE_ERROR_OPEN;
	}
	
	while (!feof(fp)) {   //feof prolazi kroz cijeli file i vraća nam neki pozitivni broj dok ne dođe do nekog exit znaka

		fgets(buffer, max_line, fp); //buffer zapisuje sve što pročita,
		norows++;

	}

	printf("%d",norows);

	fclose(fp); //odma zatvara file i govori da smo gotovi sa njim (da nebi osta otvoren)
	return EXIT_SUCCESS;

	return 0;
}