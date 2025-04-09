#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"
#define CLUSTERS 5


typedef struct {
    Participant* elemente;
    int count;
} LinieMatrice;

// 4.0.Citirea obiectelor dintr - un fișier și salvarea într - un vector.
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

// 4.0.Citirea obiectelor dintr - un fișier și salvarea într - un vector.
void citesteParticipantiDinFisier(Participant** vector, const char* numeFisier, int dimensiune) {
    *vector = malloc(sizeof(Participant) * dimensiune);
    FILE* fisier = fopen(numeFisier, "r");
    int contor = 0;
    while (contor < dimensiune && !feof(fisier)) {
        Participant p = citireParticipantDinFisier(fisier);
        inserareParticipantInVector(p, vector, contor);
        contor++;
    }
    fclose(fisier);
}

// 4.1. Functie care face deep copy din vector intr-o matrice pe linii, dupa nrCursuri % CLUSTERS
LinieMatrice* vectorInMatrice(Participant* vector, int n) {
    LinieMatrice* matrice = malloc(CLUSTERS * sizeof(LinieMatrice));
    for (int i = 0; i < CLUSTERS; ++i) {
        matrice[i].elemente = NULL;
        matrice[i].count = 0;
    }

    for (int i = 0; i < n; ++i) {
        int linie = vector[i].nrCursuri % CLUSTERS;
        int poz = matrice[linie].count;

        matrice[linie].count++;
        matrice[linie].elemente = realloc(matrice[linie].elemente, matrice[linie].count * sizeof(Participant));

        // Deep copy
        matrice[linie].elemente[poz].id = vector[i].id;

        // Copiem stringul
        matrice[linie].elemente[poz].rol = malloc(strlen(vector[i].rol) + 1);
        strcpy(matrice[linie].elemente[poz].rol, vector[i].rol);

        matrice[linie].elemente[poz].nrCursuri = vector[i].nrCursuri;

        // Copiem vectorul de preturi
        matrice[linie].elemente[poz].preturiCursuri = malloc(vector[i].nrCursuri * sizeof(float));
        for (int j = 0; j < vector[i].nrCursuri; ++j) {
            matrice[linie].elemente[poz].preturiCursuri[j] = vector[i].preturiCursuri[j];
        }
    }

    return matrice;
}

void main() {

    Participant* vector = NULL;
    int dimensiune = 10;

    citesteParticipantiDinFisier(&vector, "participanti.txt", dimensiune);

    LinieMatrice* matrice = vectorInMatrice(vector, 5);
}