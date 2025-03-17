#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct StructNod {
	Masina info;
	struct StructNod* prev;
	struct StructNod* next;
};
typedef struct StructNod Nod;

//creare structura pentru Lista Dubla 
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

typedef struct ListaDubla LD;


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	Masina m1 = { 0, 0, 0.0, NULL, NULL, 0 }; // Initialize structure to avoid garbage values

	// Read a line from the file
	if (!fgets(buffer, sizeof(buffer), file)) {
		return m1; // Return empty structure if reading fails
	}

	char* aux = strtok(buffer, sep);
	if (!aux) return m1;
	m1.id = atoi(aux);

	aux = strtok(NULL, sep);
	if (!aux) return m1;
	m1.nrUsi = atoi(aux);

	aux = strtok(NULL, sep);
	if (!aux) return m1;
	m1.pret = atof(aux);

	aux = strtok(NULL, sep);
	if (!aux) return m1;
	m1.model = (char*)malloc(strlen(aux) + 1);
	if (m1.model) strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	if (!aux) return m1;
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	if (m1.numeSofer) strcpy(m1.numeSofer, aux);

	aux = strtok(NULL, sep);
	if (aux) {
		m1.serie = *aux;
	}

	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(LD lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}

};
void afisareListaMasiniDeLaSfarsit(LD lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.ultim;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
};

void adaugaMasinaInLista(LD* lista, Masina masinaNoua)	{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //shallow copy
	nou->prev = NULL;
	nou->next = NULL;
	if (lista->prim != NULL) {
		nou->prev = lista->ultim;
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;

	//adauga la final in lista primita o noua masina pe care o primim ca parametru
}

void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
}

LD citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, m);
	}
	fclose(f);
	return lista;
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareLDMasini(LD* lista) {
	while (lista->prim->next) {
		lista->prim = lista->prim->next;
		free(lista->prim->prev->info.numeSofer);
		free(lista->prim->prev->info.model);
		free(lista->prim->prev);
	}
	free(lista->ultim->info.numeSofer);
	free(lista->ultim->info.model);
	free(lista->ultim);
	lista->ultim = NULL;
	lista->prim = NULL;
}

float calculeazaPretMediu(LD lista) {
	float suma = 0;
	int contor = 0;
	Nod* p = lista.prim;
	while (p) {
		suma += p->info.pret;
		contor++;
		p = p->next;
	}
	if (contor > 0) {
		return suma / contor;
	}
	//calculeaza pretul mediu al masinilor din lista.
	return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
	LD lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lista);
	printf("Invers:\n");
	afisareListaMasiniDeLaSfarsit(lista);
	printf("%.2f\n", calculeazaPretMediu(lista));

	dezalocareLDMasini(&lista);
	return 0;
}