#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct StructMasina{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructMasina Masina;

void afisareMasina(Masina masina) {
	printf("ID:%d\n", masina.id);
	printf("Numar usi:%d\n", masina.nrUsi);
	printf("Pret:%.2f\n", masina.pret);
	printf("Model:%s\n", masina.model);
	printf("Nume sofer:%s\n", masina.numeSofer);
	printf("Serie:%c\n\n", masina.serie);
}

Masina citireMasinaFisier(FILE* file) {
	Masina m;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);
	m.id=atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m.model, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m.numeSofer, aux);
	m.serie = strtok(NULL, sep)[0];
	return m;
}

//VECTORI//
void afisareVectorMasini(Masina* vector, int dimVector){
    for(int i = 0; i < dimVector; i++){
        afisareMasina(vector[i]);
    }
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = (*masini)[i];
	}
	aux[(*nrMasini)] = masinaNoua;//shallow copy
	free(*masini);
	(*masini) = aux;
	(*nrMasini)++;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file = fopen(numeFisier, "r");
	Masina* masini = NULL;
	(*nrMasiniCitite) = 0;
	while (!feof(file)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini){
	for(int i = 0; i < *nrMasini; i++){
		if(*vector[i]->model){
			free(*vector[i]->model);
		}
		if(*vector[i]->numeSofer){
			free(*vector[i]->numeSofer);
		}
	}
	free(*vector);
	*vector = NULL;
	(*nrMasini) = 0; 
}

//LISTE SIMPLU INLANTUITE//
struct NodSimplu {
	Masina info;
	NodSimplu* next;
}; 

typedef struct NodSimplu NodSimplu;

void afisareListaMasini(NodSimplu* cap){
	while(cap){
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(NodSimplu** cap, Masina m){
	NodSimplu* nodNou = (NodSimplu*)malloc(sizeof(NodSimplu));
	nodNou->info = m;
	nodNou->next = NULL;

	if(*cap){
		NodSimplu* temp = *cap;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = nodNou;
	} else {
		*cap = nodNou;
	}
}

void adaugaMasinaLaInceputLista(NodSimplu** cap, Masina m){
	NodSimplu* nodNou = (NodSimplu*)malloc(sizeof(NodSimplu));
	nodNou->info = m;
	nodNou->next = *cap;
	*cap = nodNou;
}

NodSimplu* citireListaDinFisier(const char* numeFisier){
	FILE* file = fopen(numeFisier, "r");
	NodSimplu* cap = NULL;
	while(!feof){
		adaugaMasinaInLista(&cap, citireMasinaFisier(numeFisier));
	}
	fclose(file);
	return cap;
}

void dezalocareLista(NodSimplu** cap){
	while(*cap){
		NodSimplu* temp = *cap;
		(*cap) = temp->next;
		if(temp->info.model){
			free(temp->info.model);
		}
		if(temp->info.numeSofer){
			free(temp->info.numeSofer);
		}
		free(temp);
	}
}

float calculeazaPretulMasinilorUnuiSofer(NodSimplu* cap, const char* numeSofer){
	float suma = 0;
	while(cap){
		if(strcmp(cap->info.numeSofer, numeSofer) == 0){
			suma+=cap->info.pret;
		}
		cap = cap->next;
	}
	return suma;
}

void stergeMasiniDinSeria(NodSimplu** cap, const char* serie){
	while(*cap && (*cap)->info.serie == serie){
		NodSimplu* aux = *cap;
		*cap = aux->next;
		        if (aux->info.numeSofer) {
            free(aux->info.numeSofer);
        }
        if (aux->info.model) {
            free(aux->info.model);
        }
        free(aux);
	}
	if(*cap){
		NodSimplu* aux = *cap;
		while(aux){
			if(aux->next && aux->info.serie != serie){
				aux = aux->next;
			}
			if(aux->next){
				NodSimplu* deSters = aux->next;
				aux->next = deSters->next;
                if (deSters->info.numeSofer) {
                    free(deSters->info.numeSofer);
                }
                if (deSters->info.model) {
                    free(deSters->info.model);
                }
                free(deSters);
            }
			else {
				aux = NULL;
			}
		}
	}
}

//LISTE DUBLU INLANTUITE//

struct NodDublu{
	Masina info;
	struct NodDublu* next;
	struct NodDublu* prev;
};
typedef struct NodDublu NodDublu;

struct ListaDubla{
	NodDublu* first;
	NodDublu* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

void afisareListaMasiniDeLaInceput(ListaDubla lista){
	NodDublu* p = lista.first;
	while(p){
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniDeLaSfarsit(ListaDubla lista){
	NodDublu* p = lista.last;
	while(p){
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(ListaDubla* lista, Masina m){
	NodDublu* nodNou = (NodDublu*)malloc(sizeof(NodDublu));
	nodNou->info = m;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if(lista->last != NULL){
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}

void adaugaMasinaInListaLaInceput(ListaDubla* lista, Masina m){
	NodDublu* nodNou = (NodDublu*)malloc(sizeof(NodDublu));
	nodNou->info = m;
	nodNou->next = lista->first;
	nodNou->prev = NULL;
	if(lista->first){
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

ListaDubla citireLDDinFisier(const char* numeFisier){
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL; 
	lista.nrNoduri = 0;
	FILE* file = fopen(numeFisier, "r");
	while(!feof){
		adaugaMasinaInLista(&lista, citireMasinaFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista){
	NodDublu* p = lista->first;
	while(p){
		NodDublu* aux = p;
		p = p->next;
		if (aux->info.model) {
			free(aux->info.model);
		}
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}

float calcularePretMediu(ListaDubla lista){
	if (lista.nrNoduri > 0){
		float suma = 0;
		NodDublu* aux = lista.first;
		while(aux){
			suma+=aux->info.pret;
			aux = aux->next;
		} 
		return suma/lista.nrNoduri;
	}
	return 0;
}

void stergeMasinaDupaID(ListaDubla* lista, int id){
	NodDublu* p = lista->first;
	while(p != NULL && p->info.id != id){
		p = p->next;
	}
	if(p == NULL) return;

	if(p->prev == NULL){
		lista->first = p->next;
		if(lista->first){
			lista->first->prev = NULL;
		}
	} else {
		p->prev->next = p->next;
	}
	if(p->next != NULL){
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
		if (p->info.model) {
		free(p->info.model);
	}
	if (p->info.numeSofer) {
		free(p->info.numeSofer);
	}
	free(p);
	lista->nrNoduri--;
}

char* getNumeSoferMasinaScumpa(ListaDubla* lista){
	if(lista->first){
	NodSimplu* max = lista->first;
	NodSimplu* p = lista->first->next;
	while(p){
		if(p->info.pret > max->info.pret){
			max = p;
		}
		p = p->next;
	}
	char* nume = (char*)malloc(strlen(max->info.numeSofer)+1);
	strcpy_s(nume, strlen(max->info.numeSofer)+1, max->info.numeSofer);
	return nume;
	} else {
	return NULL;
	}
}

//HASH TABLE//

struct HashTable {
	NodSimplu** tabel;
	int dim;
};
typedef struct HashTable HashTable;

HashTable initializareHashTable(int dimensiune){
	HashTable ht; 
	ht.dim = dimensiune;
	for(int i = 0 ; i < dimensiune; i++){
	ht.tabel[i] = NULL;
	}
	return ht;
}

int calculeazaHash(const char* nume, int dimensiune){
	int suma = 0; 
	for (int i = 0; i < strlen(nume); i++){
		suma+= nume[i];
	}
	return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable ht, Masina masina){
	int pozitie = calculeazaHash(masina.numeSofer, ht.dim);
	if(ht.tabel[pozitie] == NULL){
		ht.tabel[pozitie] = (NodSimplu*)malloc(sizeof(NodSimplu));
		ht.tabel[pozitie]->info = masina;
		ht.tabel[pozitie]->next = NULL;
	} else {
		adaugaMasinaInLista(ht.tabel[pozitie], masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune){
	FILE* file = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(dimensiune);
	while(!feof(file)){
		Masina masina = citireMasinaFisier(file);
		inserareMasinaInTabela(ht, masina);
	}
	fclose(file);
	return ht;
}

void afisareTabelaMasini(HashTable ht){
	for(int i = 0; i < ht.dim; i++){
		if(ht.tabel[i] != NULL){
		afisareListaMasini(ht.tabel[i]);
	} else {
		printf("\nPe pozitia %d nu avem masini\n");
	}
}
}

void dezalocareTabelaMasini(HashTable* ht){
	for(int i = 0; i<ht->dim; i++){
		dezalocareLista(&ht->tabel[i]);
	}
	free(ht->tabel);
	ht->tabel = NULL;
	ht->dim = 0;
}

float calculeazaMedieLista(NodSimplu* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->info.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere){
	float* preturi = NULL;
	*nrClustere = 0;
	for(int i = 0; i < ht.dim; i++){
		if(ht.tabel[i] != NULL){
			(*nrClustere)++;
		}
	}
	preturi = (float*)malloc(sizeof(float)*(*nrClustere));
	int contor = 0;
	for(int i = 0; i < ht.dim; i++){
		if(ht.tabel[i] != NULL){
			preturi[contor] = calcluleazaMedieLista(ht.tabel[i]);
			contor++;
		}
	}
	return preturi;

}

Masina getMasinaDinLista(NodSimplu* cap, const char* nume) {
	Masina m;
	m.id = -1;
	while (cap && strcmp(cap->info.numeSofer, nume) != 0) {
		cap = cap->next;
	}
	if (cap) {
		m = cap->info;
		m.model = (char*)malloc(strlen(cap->info.model) + 1);
		strcpy_s(m.model, strlen(cap->info.model) + 1, cap->info.model);		
		m.numeSofer = (char*)malloc(strlen(cap->info.numeSofer) + 1);
		strcpy_s(m.numeSofer, strlen(cap->info.numeSofer) + 1, cap->info.numeSofer);
	}
	return m;
}

Masina getMasinaDupNumeSofer(HashTable ht, const char* nume){
	Masina m;
	m.id = -1;
	int poz = calculeazaHash(nume, ht.dim);
	if(poz >= 0 && ht.dim){
		return getMasinaDinLista(ht.tabel[poz], nume);
	}
	return m;
}

int main(){
    int dim = 0;
    Masina* vector = citireVectorMasiniFisier("masini.txt", &dim);
    afisareVectorMasini(vector, dim);
}