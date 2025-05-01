#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"


struct StructNod {
	Participant info;
	struct StructNod* next;
	struct StructNod* prev;
};
typedef struct StructNod Nod;

typedef struct NodSimplu {
	Participant info;
	struct NodSimplu* next;
} NodSimplu;

//1. Functie pentru stergerea unui nod de pe o pozitie data.
void stergerePozitie(Nod** cap, int pozitie) {
	if (*cap == NULL) {
		return;
	}

	Nod* temp = *cap;
	int index = 0;

	while (temp && index < pozitie) {
		temp = temp->next;
		index += 1;
	}

	if (!temp) return;

	if (temp->prev) {
		temp->prev->next = temp->next;
	}
	else {
		*cap = temp->next;
	}
	free(temp->info.rol);
	free(temp->info.preturiCursuri);
	free(temp);
}
//2. Functie pentru inserarea elementelor in ordine crescatoare dupa un atribut.
void inserareInOrdine(Nod** cap, Participant p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = nou->prev = NULL;

	if (*cap == NULL) {
		*cap = nou;
		return;
	}

	Nod* temp = *cap;
	while (temp && temp->info.id < p.id) {
		temp = temp->next;
	}

	if (!temp) {
		Nod* ultim = *cap;
		while (ultim->next) {
			ultim = ultim->next;
		}
		ultim->next = nou;
		nou->prev = ultim;
	}
	else if (temp == *cap) {
		nou->next = *cap;
		(*cap)->prev = nou;
		*cap = nou;
	} else {
		nou->prev = temp->prev;
		nou->next = temp;
		temp->prev->next = nou;
		temp->prev = nou;
	}
}
//3. Functii pentru parcurgerea listei in ordine crescatoare si descrescatoare.
void parcurgereCrescatoare(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		printf("ID: %d, Rol: %s\n", temp->info.id, temp->info.rol);
		temp = temp->next;
	}
}

void parcurgereDescrescatoare(Nod* cap) {
	Nod* temp = cap;
	while (temp && temp->next) temp = temp->next; 

	while (temp) {
		printf("ID: %d, Rol: %s\n", temp->info.id, temp->info.rol);
		temp = temp->prev;
	}
}

Participant creareParticipant(int id, const char* rol, int nrCursuri, float* preturi) {
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

//4. Functie pentru salvarea elementelor intr - o lista simplu inlantuita(deep copy).
NodSimplu* copiereLista(Nod* cap) {
	NodSimplu* capSimplu = NULL;
	NodSimplu* ultim = NULL;

	while (cap) {
		NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
		nou->info = creareParticipant(cap->info.id, cap->info.rol, cap->info.nrCursuri, cap->info.preturiCursuri);
		nou->next = NULL;

		if (!capSimplu) capSimplu = nou;
		else ultim->next = nou;

		ultim = nou;
		cap = cap->next;
	}

	return capSimplu;
}
//5. Functie pentru interschimbarea a doua elemente din lista pe baza pozitiilor.
void interschimbarePozitii(Nod* cap, int poz1, int poz2) {
	if (poz1 == poz2) return;

	Nod* n1 = NULL, * n2 = NULL, * temp = cap;
	int i = 0;
	while (temp) {
		if (i == poz1) n1 = temp;
		if (i == poz2) n2 = temp;
		temp = temp->next;
		i++;
	}

	if (n1 && n2) {
		Participant aux = n1->info;
		n1->info = n2->info;
		n2->info = aux;
	}
}
void main() {
	Nod* lista = NULL;

	float preturi1[] = { 100.0, 200.0 };
	float preturi2[] = { 150.0 };
	float preturi3[] = { 300.0, 400.0, 500.0 };

	Participant p1 = creareParticipant(3, "Student", 2, preturi1);
	Participant p2 = creareParticipant(1, "Profesor", 1, preturi2);
	Participant p3 = creareParticipant(2, "Coordonator", 3, preturi3);

	inserareInOrdine(&lista, p1);
	inserareInOrdine(&lista, p2);
	inserareInOrdine(&lista, p3);

	printf("Lista in ordine crescatoare:\n");
	parcurgereCrescatoare(lista);

	printf("\n Lista in ordine descrescatoare:\n");
	parcurgereDescrescatoare(lista);

	printf("\n Stergere de pe pozitia 1: \n");
	stergerePozitie(&lista, 1);
	parcurgereCrescatoare(lista);

	printf("\n Copiere intr-o lista simplu inlantuita: \n");
	NodSimplu* listaSimpla = copiereLista(lista);
	NodSimplu* tempSimplu = listaSimpla;
	while (tempSimplu) {
		printf("Copiat ID: %d, Rol: %s\n", tempSimplu->info.id, tempSimplu->info.rol);
		tempSimplu = tempSimplu->next;
	}

	printf("\n Interschimbare pozitii 0 si 1: \n");
	interschimbarePozitii(lista, 0, 1);
	parcurgereCrescatoare(lista);

}
