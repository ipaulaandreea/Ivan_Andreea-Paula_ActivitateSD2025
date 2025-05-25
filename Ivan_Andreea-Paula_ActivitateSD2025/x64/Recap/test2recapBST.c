#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<malloc.h>

struct Brutarie {
    char* nume;
    int id; 
    int nrAngajati;
};

typedef struct Brutarie Brutarie;

Brutarie initializareBrutarie(const char* nume, int id, int nrAngajati) {
	Brutarie b;
	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.id = id;
	b.nrAngajati = nrAngajati;

	return b;
}

void afisareBrutarie(Brutarie b) {
	printf("%d %s %d\n", b.id, b.nume, b.nrAngajati);
}

Brutarie citireBrutarieDinFisier(FILE* file){
    Brutarie b;
    char buffer[100];
    char sep[3] = ",/n";
    char* aux;
    fgets(buffer, 100, file);
    aux = strtok(buffer, sep);
    b.id = atoi(aux);
    b.nrAngajati = atoi(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    b.nume = (char*)malloc(strlen(aux)+1);
    strcpy_s(b.nume, strlen(aux)+1, aux);
    return b;
}

typedef struct Nod Nod;
struct Nod {
    Brutarie info;
    Nod* st;
    Nod* dr;
};

void inserareNod(Brutarie b, Nod** radacina){
    if(*radacina){
        if((*radacina)->info.id > b.id){
            inserareNod(b, &(*radacina)->st);
        }
        else {
            inserareNod(b, &(*radacina)->dr);
        }
    }
    else {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = b;
        nou->st = NULL;
        nou->dr = NULL;
        *radacina = nou;
    }
}

void afisarePreordine(Nod* radacina){
    if(radacina){
        afisareBrutarie(radacina->info);
        afisarePreordine(radacina->st);
        afisarePreordine(radacina->dr);
    }
}

void afisareInordine(Nod* radacina){
    if(radacina){
        afisareInordine(radacina->st);
        afisareBrutarie(radacina->info);
        afisareInordine(radacina->dr);
    }
}

Brutarie cautaBrutarie(Nod* rad, int id){
    if(rad){
        if(id < rad->info.id){
            return cautaBrutarie(rad->st, id);
        }
        else{
            if(id > rad->info.id){
                return cautaBrutarie(rad->dr, id);
            }
            else {
                return initializareBrutarie(rad->info.nume, rad->info.id, rad->info.nrAngajati);
            }
        }
    }
    else {
        return initializareBrutarie("", 0, 0);
    }
}

int calcNrTotalAngajati(Nod* radacina){
    if(radacina){
        return radacina->info.nrAngajati
        + calcNrTotalAngajati(radacina->st) 
        + calcNrTotalAngajati(radacina->dr);
    } else {
        return 0;
    }
}

int determinareInaltime(Nod* radacina){
    if(radacina){
        int stH = determinareInaltime(radacina->st);
        int drH = determinareInaltime(radacina->dr);
        return 1 + (stH > drH ? stH : drH);
    }
    else {
        return 0;
    }
}

void stergereArbore(Nod** radacina){
    if(*radacina){
        stergereArbore(&(*radacina)->st);
        stergereArbore(&(*radacina)->dr);
        free((*radacina)->info.nume);
        free(*radacina);
        *radacina = NULL;
    }
}

Nod* citireArboreDinFisier(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    Nod* radacina = NULL;
    while (!feof(file)) {
        Brutarie b = citireBrutarieDinFisier(file);
        inserareNod(b, &radacina);
        free(b.nume);
    }
    fclose(file);
    return radacina;
}
