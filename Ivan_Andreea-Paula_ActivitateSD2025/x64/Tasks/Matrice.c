#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"
#define CLUSTERS 3


typedef struct {
    Participant* elemente;
    int count;
} LinieMatrice;

// 4.0.Citirea obiectelor dintr-un fișier și salvarea într-un vector.
Participant citireParticipantDinFisier(FILE* file) {
    Participant p;
    char buffer[256];

    if (!fgets(buffer, sizeof(buffer), file)) {
        p.id = -1;
        p.rol = malloc(1);
        p.rol[0] = '\0';
        p.nrCursuri = 0;
        p.preturiCursuri = NULL;
        return p;
    }

    char* aux = strtok(buffer, ",\r\n");
    if (!aux) { p.id = -1; return p; }
    p.id = atoi(aux);

    aux = strtok(NULL, ",\r\n");
    if (!aux) { p.id = -1; return p; }
    p.rol = malloc(strlen(aux) + 1);
    strcpy(p.rol, aux);

    aux = strtok(NULL, ",\r\n");
    if (!aux) { p.id = -1; return p; }
    p.nrCursuri = atoi(aux);

    p.preturiCursuri = malloc(p.nrCursuri * sizeof(float));
    for (int i = 0; i < p.nrCursuri; i++) {
        aux = strtok(NULL, ",\r\n");
        if (aux) {
            p.preturiCursuri[i] = atof(aux);
        } else {
            p.preturiCursuri[i] = 0.0f;
        }
    }

    return p;
}

void inserareParticipantInVector(Participant p, Participant** vector, int index) {
    Participant nou;

    nou.id = p.id;
    nou.nrCursuri = p.nrCursuri;

    nou.rol = malloc(strlen(p.rol) + 1);
    strcpy(nou.rol, p.rol);

    nou.preturiCursuri = malloc(p.nrCursuri * sizeof(float));
    for (int i = 0; i < p.nrCursuri; i++) {
        nou.preturiCursuri[i] = p.preturiCursuri[i];
    }

    (*vector)[index] = nou;
}

// 4.0.Citirea obiectelor dintr-un fișier și salvarea într-un vector.
void citesteParticipantiDinFisier(Participant** vector, const char* numeFisier, int dimensiune) {
    *vector = malloc(sizeof(Participant) * dimensiune);
    FILE* fisier = fopen(numeFisier, "r");
    
    if (!fisier) {
        perror("Eroare la deschiderea fisierului");
        exit(1);
    }

    int contor = 0;
    while (contor < dimensiune) {
        Participant p = citireParticipantDinFisier(fisier);

        if (p.id == -1) break;

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
        matrice[linie].elemente[poz].id = vector[i].id;
        matrice[linie].elemente[poz].rol = malloc(strlen(vector[i].rol) + 1);
        strcpy(matrice[linie].elemente[poz].rol, vector[i].rol);

        matrice[linie].elemente[poz].nrCursuri = vector[i].nrCursuri;

        matrice[linie].elemente[poz].preturiCursuri = malloc(vector[i].nrCursuri * sizeof(float));
        for (int j = 0; j < vector[i].nrCursuri; ++j) {
            matrice[linie].elemente[poz].preturiCursuri[j] = vector[i].preturiCursuri[j];
        }
    }

    return matrice;
}

//4.2. Sortarea liniilor matricei după numărul de elemente
void sorteazaLiniiMatrice(LinieMatrice* matrice) {
    for (int i = 0; i < CLUSTERS - 1; i++) {
        for (int j = i + 1; j < CLUSTERS; j++) {
            if (matrice[i].count > matrice[j].count) {
                LinieMatrice temp = matrice[i];
                matrice[i] = matrice[j];
                matrice[j] = temp;
            }
        }
    }
}

//4.3. Afișarea conținutului matricei
void afiseazaMatrice(LinieMatrice* matrice) {
    for (int i = 0; i < CLUSTERS; i++) {
        printf("Linia %d (%d elemente):\n", i, matrice[i].count);
        for (int j = 0; j < matrice[i].count; j++) {
            Participant p = matrice[i].elemente[j];
            printf("  ID: %d, Rol: %s, Nr cursuri: %d, Preturi: ",
                p.id, p.rol, p.nrCursuri);
            for (int k = 0; k < p.nrCursuri; k++) {
                printf("%.2f ", p.preturiCursuri[k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {

    Participant* vector = NULL;
    int dimensiune = 10;

    citesteParticipantiDinFisier(&vector, "participanti.txt", dimensiune);

    printf("=== Matricea înainte de sortare ===\n");
    LinieMatrice* matrice = vectorInMatrice(vector, dimensiune);
    afiseazaMatrice(matrice);

    printf("=== Matricea după sortare ===\n");
    sorteazaLiniiMatrice(matrice);
    afiseazaMatrice(matrice);

    for (int i = 0; i < CLUSTERS; i++) {
        for (int j = 0; j < matrice[i].count; j++) {
            free(matrice[i].elemente[j].rol);
            free(matrice[i].elemente[j].preturiCursuri);
        }
        free(matrice[i].elemente);
    }
    free(matrice);

    for (int i = 0; i < dimensiune; i++) {
        free(vector[i].rol);
        free(vector[i].preturiCursuri);
    }
    free(vector);

    return 0;
}