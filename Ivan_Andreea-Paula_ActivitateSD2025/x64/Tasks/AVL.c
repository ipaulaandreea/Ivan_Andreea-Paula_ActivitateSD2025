#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include "participant.h"

struct Nod {
	Participant info;
	struct Nod* st;
	struct Nod* dr;
}; 
typedef struct Nod Nod;

typedef struct {
    Participant* vector;
    int capacitate;
    int index;
} VectorParticipanti;

typedef struct ListaSimpla {
    Participant info;
    struct ListaSimpla* next;
} ListaSimpla;

typedef struct ListaDubla {
    Participant info;
    struct ListaDubla* prev;
    struct ListaDubla* next;
} ListaDubla;

Nod* rotireDreapta(Nod* radacina) {
	Nod* nod;
	nod = radacina->st;
	radacina->st = nod->dr;
	nod->dr = radacina;

	return nod;
}

Nod* rotireStanga(Nod* radacina) {
	Nod* nod;
	nod = radacina->dr;
	radacina->dr = nod->st;
	nod->st = radacina;
	return nod;
}

int gradEchilibru(Nod* radacina)
{
	int inaltimeSt = inaltime(radacina->st);
	int inaltimeDr = inaltime(radacina->dr);
	return inaltimeSt - inaltimeDr;
}

void inserareArbore(Nod** radacina, Participant p) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > p.id) {
			inserareArbore(&((*radacina)->st), p);
		}
		else {
			inserareArbore(&((*radacina)->dr), p);
		}
		int grad = gradEchilibru((*radacina));
		if (grad == 2) {
			if (gradEchilibru((*radacina)->st) == 1) {
				(*radacina) = rotireDreapta((*radacina));
			}
			else {
				(*radacina)->st = rotireStanga((*radacina)->st);
				(*radacina) = rotireDreapta((*radacina));
			}
		}
		else if (grad == -2) {
			if (gradEchilibru((*radacina)->dr) == 1) {
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
			}

			(*radacina) = rotireStanga((*radacina));
	}
}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = p;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}

int inaltime(Nod* radacina)
{
	if (radacina == NULL)
		return 0;
	else
	{
		int inaltimeSt = inaltime(radacina->st);
		int inaltimeDr = inaltime(radacina->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
}


Participant citireParticipantDinFisier(FILE* file) {
	char buffer[256];
	Participant p1;

	if (fgets(buffer, sizeof(buffer), file)) {
		char* aux = strtok(buffer, ",\n");
		p1.id = atoi(aux);

		aux = strtok(NULL, ",\n");
		p1.rol = malloc(strlen(aux) + 1);
		strcpy(p1.rol, aux);

		aux = strtok(NULL, ",\n");
		p1.nrCursuri = atoi(aux);

		p1.preturiCursuri = malloc(p1.nrCursuri * sizeof(float));
		for (int i = 0; i < p1.nrCursuri; i++) {
			aux = strtok(NULL, ",\n");
			p1.preturiCursuri[i] = atof(aux);
		}
	}
	return p1;
}

void afisareParticipant(Participant p) {

	printf("\n ID Participant: %d\n", p.id);
	printf("Rol: %s\n", p.rol);
	printf("Numar cursuri: %d\n", p.nrCursuri);
	printf("Preturi cursuri:\n");
	for (int i = 0; i < p.nrCursuri; i++) {
		printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
	}
}

Nod* citireArboreParticipantDinFisier(char* numeFisier) {
	Nod* arbore = NULL;

	if (!numeFisier) {
		return NULL;
	}
	else {
		FILE* f = fopen(numeFisier, "r");

while (!feof(f)) {
    Participant p = citireParticipantDinFisier(f);

    if (p.rol != NULL && p.nrCursuri > 0 && p.preturiCursuri != NULL)
        inserareArbore(&arbore, p);
}
		fclose(f);

	}
	return arbore;
}

void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->st);
		afisareParticipant(arbore->info);
		afisareInOrder(arbore->dr);
	}
}

void afisarePreordine(Nod* radacina) {
	if (radacina) {
		afisareParticipant(radacina->info);
		afisarePreordine(radacina->st);
		afisarePreordine(radacina->dr);
	}
}
void stergereArbore(Nod** radacina) {
	if (*radacina) {
		stergereArbore(&((*radacina)->st));
		stergereArbore(&((*radacina)->dr));
		free((*radacina)->info.preturiCursuri);
		free((*radacina)->info.rol);
		free(*radacina);
		*radacina = NULL;
	}
}

Nod* cautaNod(Nod* radacina, int id) {
    if (radacina == NULL)
        return NULL;
    if (radacina->info.id == id)
        return radacina;
    else if (id < radacina->info.id)
        return cautaNod(radacina->st, id);
    else
        return cautaNod(radacina->dr, id);
}

void salvarePreordineInVector(Nod* radacina, VectorParticipanti* vp) {
    if (radacina) {
        if (vp->index < vp->capacitate)
            vp->vector[vp->index++] = radacina->info;
        salvarePreordineInVector(radacina->st, vp);
        salvarePreordineInVector(radacina->dr, vp);
    }
}

void inserareSfarsitListaSimpla(ListaSimpla** cap, Participant p) {
    ListaSimpla* nou = (ListaSimpla*)malloc(sizeof(ListaSimpla));
    nou->info = p;
    nou->next = NULL;
    if (*cap == NULL)
        *cap = nou;
    else {
        ListaSimpla* temp = *cap;
        while (temp->next)
            temp = temp->next;
        temp->next = nou;
    }
}

void salvarePreordineListaSimpla(Nod* radacina, ListaSimpla** cap) {
    if (radacina) {
        inserareSfarsitListaSimpla(cap, radacina->info);
        salvarePreordineListaSimpla(radacina->st, cap);
        salvarePreordineListaSimpla(radacina->dr, cap);
    }
}

void salvareInordineListaSimpla(Nod* radacina, ListaSimpla** cap) {
    if (radacina) {
        salvareInordineListaSimpla(radacina->st, cap);
        inserareSfarsitListaSimpla(cap, radacina->info);
        salvareInordineListaSimpla(radacina->dr, cap);
    }
}

void inserareSfarsitListaDubla(ListaDubla** cap, Participant p) {
    ListaDubla* nou = (ListaDubla*)malloc(sizeof(ListaDubla));
    nou->info = p;
    nou->next = NULL;
    nou->prev = NULL;

    if (*cap == NULL)
        *cap = nou;
    else {
        ListaDubla* temp = *cap;
        while (temp->next)
            temp = temp->next;
        temp->next = nou;
        nou->prev = temp;
    }
}

void salvareInordineListaDubla(Nod* radacina, ListaDubla** cap) {
    if (radacina) {
        salvareInordineListaDubla(radacina->st, cap);
        inserareSfarsitListaDubla(cap, radacina->info);
        salvareInordineListaDubla(radacina->dr, cap);
    }
}

void afisareListaSimpla(ListaSimpla* cap) {
    while (cap) {
        afisareParticipant(cap->info);
        cap = cap->next;
    }
}

void afisareListaDubla(ListaDubla* cap) {
    while (cap) {
        afisareParticipant(cap->info);
        cap = cap->next;
    }
}

void main()
{
	Nod* arbore = citireArboreParticipantDinFisier("participanti.txt");
	afisarePreordine(arbore);

	// Cautare dupa ID
    int idCautat = 4;
    Nod* nodGasit = cautaNod(arbore, idCautat);
    if (nodGasit)
        afisareParticipant(nodGasit->info);
    else
        printf("Participantul cu ID %d nu a fost gasit.\n", idCautat);

    // Salvare in vector (Preordine)
    VectorParticipanti vp;
    vp.capacitate = 20;
    vp.index = 0;
    vp.vector = (Participant*)malloc(vp.capacitate * sizeof(Participant));
    salvarePreordineInVector(arbore, &vp);

    for (int i = 0; i < vp.index; i++)
        afisareParticipant(vp.vector[i]);

    free(vp.vector);

    // Salvare in lista simplu inlantuita (Inordine)
    ListaSimpla* listaS = NULL;
    salvareInordineListaSimpla(arbore, &listaS);
    afisareListaSimpla(listaS);

    // Salvare in lista dublu inlantuita (Postordine)
    ListaDubla* listaD = NULL;
    salvareInordineListaDubla(arbore, &listaD);
    afisareListaDubla(listaD);

	stergereArbore(&arbore);
	afisarePreordine(arbore);


}