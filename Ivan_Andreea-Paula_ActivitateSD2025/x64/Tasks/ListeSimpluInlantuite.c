#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"


struct StructNod {
	Participant info;
	struct StructNod* next;
};
typedef struct StructNod Nod;

struct ListaSimpla {
	Nod* head; 
};
typedef struct ListaSimpla LS;


// Functie pentru crearea unui participant
Participant creeazaParticipant(int id, const char* rol, int nrCursuri, float* preturi) {
	Participant p;
	p.id = id;
	p.rol = strdup(rol);
	p.nrCursuri = nrCursuri;
	p.preturiCursuri = (float*)malloc(nrCursuri * sizeof(float));
	for (int i = 0; i < nrCursuri; i++) {
		p.preturiCursuri[i] = preturi[i];
	}
	return p;
}

// Functie pentru afisarea unui participant
void afisareParticipant(Participant p) {

	printf("\n ID Participant: %d\n", p.id);
	printf("Rol: %s\n", p.rol);
	printf("Numar cursuri: %d\n", p.nrCursuri);
	printf("Preturi cursuri:\n");
	for (int i = 0; i < p.nrCursuri; i++) {
		printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
	}
};

//Functie pentru adaugarea unui nou nod la inceputul listei
void adaugaLaInceput(LS* lista, Participant participant) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	if (nou == NULL) {
		exit(1);
	}
	nou->info = participant;
	nou->next = lista->head;
	lista->head = nou;
}

//Functie pentru afisarea listei
void afiseazaLista(LS lista) {
	Nod* temp = lista.head;
	while (temp != NULL) {
		afisareParticipant(temp->info);
		temp = temp->next;
	}
	printf("NULL\n");
}

//1. Functie pentru stergerea unui nod de pe o pozitie data.
int stergereNod(int pozitie, LS* lista) {
	if (lista == NULL || lista->head == NULL || pozitie < 0) {
		return -1;
	}
	Nod* temp = lista->head;
	if (pozitie == 0) {
		lista->head = temp->next;
		free(temp);
		return 0;
	}

	for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
		temp = temp->next;
	}

	if (temp == NULL || temp->next == NULL) {
		return 0;
	}

	Nod* nodDeSters = temp->next;
	temp->next = nodDeSters->next;
	free(nodDeSters);

	return 0;
}

//2. Funcție pentru inserarea elementelor în ordine crescătoare după un atribut.
void inserareDupaNumarulCursurilor(LS* lista, Nod* nod) {
	if (lista == NULL || nod == NULL) {
		return;
	}
	if (lista == NULL || nod->info.nrCursuri < lista->head->info.nrCursuri) {
		nod->next = lista->head;
		lista->head = nod;
		return;
	}

	Nod* temp = lista->head;
	while(temp->next != NULL && temp->next->info.nrCursuri <= nod->info.nrCursuri) {
		temp = temp->next;
	}

	nod->next = temp;
	temp->next = nod;
}

//3. Funcție pentru salvarea într-un vector a elementelor care îndeplinesc o condiție(deep copy).
void salvareInVector(LS lista, int nrMinimCursuri, Participant** vectorParticipanti, int* dimensiune) {
	if (vectorParticipanti == NULL || dimensiune == NULL) {
		return;
	}

	Nod* temp = lista.head;
	int dimVector = 0;

	while (temp != NULL) {
		if (temp->info.nrCursuri >= nrMinimCursuri) {
			dimVector += 1;
		}
		temp = temp->next;
	}

	*vectorParticipanti = (Participant*)malloc(dimVector * sizeof(Participant));
	if (*vectorParticipanti == NULL) {
		printf("Eroare la alocarea vectorului!\n");
		exit(1);
	}
	temp = lista.head;
	int index = 0;
	while (temp != NULL) {
	if (temp->info.nrCursuri >= nrMinimCursuri) {
		(*vectorParticipanti)[index].id = temp->info.id;
		(*vectorParticipanti)[index].rol = strdup(temp->info.rol);
		(*vectorParticipanti)[index].nrCursuri = temp->info.nrCursuri;
		(*vectorParticipanti)[index].preturiCursuri = (float*)malloc((*vectorParticipanti)[index].nrCursuri * sizeof(float));
		for (int i = 0; i < (*vectorParticipanti)[index].nrCursuri; i++) {
			(*vectorParticipanti)[index].preturiCursuri[i] = temp->info.preturiCursuri[i];
		}
		index++;
	}
	temp = temp->next;
	}
*dimensiune = dimVector;
}

//4. Functie pentru interschimbarea a doua elemente in lista pe baza pozițiilor
void interschimbareNoduri(LS* lista, int poz1, int poz2){
	if(lista == NULL || lista->head == NULL || poz1 < 0 || poz2 < 0){
		return;
	}

	Nod* prev1 = NULL;
	Nod* prev2 = NULL;
	Nod* curr1 = lista->head;
	Nod* curr2 = lista->head;
	int index = 0;
	while(curr1 != NULL && index < poz1){
		prev1 = curr1;
		curr1 = curr1->next;
		index++;
	}

	index = 0;

	while(curr2 != NULL && index < poz2){
		prev2 = curr2;
		curr2 = curr2->next;
		index++;
	}

	if(curr1 == NULL || curr2 == NULL){
		return;
	}
	if(prev1 != NULL){
		prev1->next = curr2;
	}
	else{
		lista->head = curr2;
	}
	if(prev2 != NULL){
		prev2->next = curr1;
	}
	else{
		lista->head = curr1;
	}

Nod* temp = curr1->next;
curr1->next = curr2->next;
curr2->next = temp;
}

void main() {
	LS lista;
	lista.head = NULL;

	float preturi1[] = { 100.0, 150.0 };
	float preturi2[] = { 200.0 };
	float preturi3[] = { 80.0, 90.0, 120.0 };

	Participant p1 = creeazaParticipant(1, "student", 2, preturi1);
	Participant p2 = creeazaParticipant(2, "profesor", 1, preturi2);
	Participant p3 = creeazaParticipant(3, "invitat", 3, preturi3);

	adaugaLaInceput(&lista, p1);
	adaugaLaInceput(&lista, p2);
	adaugaLaInceput(&lista, p3);

	printf("Lista initiala: ");
	afiseazaLista(lista);

	if (stergereNod(1, &lista) == 0) {
		printf("Nodul a fost sters cu succes.\n");
	}
	else {
		printf("Eroare la stergere: pozitie invalida.\n");
	}

	printf("Lista dupa stergere: ");
	afiseazaLista(lista);

	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = p2;
	nodNou->next = NULL;
	inserareDupaNumarulCursurilor(&lista, nodNou);
	printf("Lista dupa adaugare in ordinea numarului de cursuri:");
	afiseazaLista(lista);

	Participant* vectorParticipanti = NULL;
	int nrParticipanti = 0;

	salvareInVector(lista, 2, &vectorParticipanti, &nrParticipanti);
	printf("Participanti salvati cu cel putin 2 cursuri:\n");
	for (int i = 0; i < nrParticipanti; i++) {
		afisareParticipant(vectorParticipanti[i]);
	}

	for (int i = 0; i < nrParticipanti; i++) {
		free(vectorParticipanti[i].rol);
		free(vectorParticipanti[i].preturiCursuri);
	}
	free(vectorParticipanti);

	printf("Lista inainte de interschimbare: ");
	afiseazaLista(lista);
	interschimbareNoduri(&lista, 1, 2);
	printf("Lista dupa interschimbare: ");
	afiseazaLista(lista);
}
