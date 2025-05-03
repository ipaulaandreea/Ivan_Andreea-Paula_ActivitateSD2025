#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

typedef struct Cladire {
	int id;
	char adresa[100];
	int an;
	struct Cladire* next;
} Cladire;

//1. Crearea unei tabele de dispersie pentru stocarea clădirilor din București(clustere pe baza anului construirii)
Cladire* hashTable[HASH_SIZE];

int hash(int an) {
	return an % HASH_SIZE;
}

void adaugaCladire(int id, const char* adresa, int an) {
	int index = hash(an);
	Cladire* cladire = (Cladire*)malloc(sizeof(Cladire));
	cladire->id = id;
	strcpy(cladire->adresa, adresa);
	cladire->an = an;
	cladire->next = hashTable[index];
	hashTable[index] = cladire;
}

//2. Funcție pentru afișarea clădirilor dintr - un anumit an
void afiseazaCladiriDinAn(int an) {
	int index = hash(an);
	Cladire* curent = hashTable[index];
	while (curent) {
		if (curent->an == an) {
			printf("ID: %d, Adresa: %s, An: %d\n", curent->id, curent->adresa, curent->an);
			curent = curent->next;
		}
	}
}

//3. Funcție pentru ștergerea unei clădiri pe baza ID - ului și anului construirii
void stergereCladireIdAn(int id, int an) {
	int index = hash(an);
	Cladire* curent = hashTable[index];
	Cladire* prev = NULL;

	while (curent) {
		if (curent->id == id && curent->an == an) {
			if (prev) {
				prev->next = curent->next;
			}
			else {
				hashTable[index] = curent->next;
			}
				free(curent);
				return;
			}
			prev = curent;
			curent = curent->next;
		}
	}


//4. Funcție pentru ștergerea unei clădiri doar pe baza ID - ului
void stergereCladireId(int id) {
	for (int i = 0; i < HASH_SIZE; i++) {
		Cladire* curent = hashTable[i];
		Cladire* prev = NULL;

		while (curent) {
			if (curent->id == id) {
				if (prev) {
					prev->next = curent->next;
				}
				else {
					hashTable[i] = curent->next;
				}
					free(curent);
					return;
				}
				prev = curent;
				curent = curent->next;
			}
		}
	}

//5. Observarea diferenței dintre cele două funcții de ștergere
// ~ functia 3 este mai rapida decat functia 4 deoarece, avand la dispozitie anul, 
// adica parametrul dupa care se face hashingul si implicit stabilirea indexul fiecarui bucket,
// cautarea se face tintit la nivelul bucketului corespunzator, nu la nivelul intregii tabele de dispersie ~

//6. Funcție pentru salvarea într-un vector a clădirilor dintr-un anumit an (deep copy).
Cladire** copiereCladiriDinAn(int an, int* dimVector) {
	int index = hash(an);
	Cladire* curent = hashTable[index];
	Cladire** vector = malloc(100 * sizeof(Cladire*));
	*dimVector = 0;

	while (curent) {
		if (curent->an == an) {
			Cladire* copie = (Cladire*)malloc(sizeof(Cladire));
			copie->id = curent->id;
			strcpy(copie->adresa, curent->adresa);
			copie->an = curent->an;
			copie->next = NULL;
			vector[(*dimVector)++] = copie;
		}
		curent = curent->next;
	}
	return vector;
}
//7. Funcție pentru modificarea anului de construire a unei clădiri(cu actualizarea clusterizării).
void modificareAnCladire(int id, int anNou) {
	for (int i = 0; i < HASH_SIZE; i++) {
		Cladire* curent = hashTable[i];
		Cladire* prev = NULL;

		while (curent) {
			if (curent->id == id) {
				if (prev) {
					prev->next = curent->next;
				}
				else {
					hashTable[i] = curent->next;
				}
				curent->an = anNou;
				int indexNou = hash(anNou);
				curent->next = hashTable[indexNou];
				hashTable[indexNou] = curent;
				return;
			}
			prev = curent;
			curent = curent->next;
		}
	}
} 

void main() {

	adaugaCladire(1, "Bd. Unirii 1", 1985);
	adaugaCladire(2, "Str. Victoriei 2", 1985);
	adaugaCladire(3, "Calea Dorobanti 3", 1990);

	printf("\nCladiri din 1985:\n");
	afiseazaCladiriDinAn(1985);

	stergereCladireIdAn(1, 1985);
	printf("\nCladiri din 1985 dupa stergere:\n");
	afiseazaCladiriDinAn(1985);
	stergereCladireId(3);
	printf("\nCladiri din 1990 dupa stergere:\n");
	afiseazaCladiriDinAn(1990);

	
	adaugaCladire(4, "Bd. Splaiului Unirii 32", 1985);
	adaugaCladire(5, "Str. Victoriei 21", 1975);
	adaugaCladire(6, "Calea Dorobanti 31", 1990);

	int dimVector = 0;
	Cladire** vector = copiereCladiriDinAn(1985, &dimVector);
	printf("\nCladiri copiate din 1985:\n");
	for(int i = 0; i< dimVector; i++){
		printf("ID: %d, Adresa: %s, An: %d\n", vector[i]->id, vector[i]->adresa, vector[i]->an);
		free(vector[i]);	
	}
	free(vector);

	modificareAnCladire(6, 1985);
	printf("\nCladiri din 1985 dupa modificare:\n");
	afiseazaCladiriDinAn(1985);
}