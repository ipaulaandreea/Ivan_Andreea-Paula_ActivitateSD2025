#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"

void afisareParticipant(Participant p) {

    printf("\n ID Participant: %d\n", p.id);
    printf("Rol: %s\n", p.rol);
    printf("Numar cursuri: %d\n", p.nrCursuri);
    printf("Preturi cursuri:\n");
    for (int i = 0; i < p.nrCursuri; i++) {
        printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
    }
}

void afisareVector(Participant* vector, int nrElemente){
    for(int i = 0; i < nrElemente; i++){
        afisareParticipant(vector[i]);
        printf("\n");
    }
}

void inserareParticipantInVector(Participant p, Participant** vector, int index) {
    (*vector)[index].id = p.id;
    (*vector)[index].nrCursuri = p.nrCursuri;

    (*vector)[index].rol = malloc(strlen(p.rol) + 1);
    strcpy((*vector)[index].rol, p.rol);

    (*vector)[index].preturiCursuri = malloc(p.nrCursuri * sizeof(float));
    for (int i = 0; i < p.nrCursuri; i++) {
        (*vector)[index].preturiCursuri[i] = p.preturiCursuri[i];
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

//3.1. Funcție pentru citirea obiectelor din fișier și salvarea într-un vector
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

//3.2. Funcție pentru salvarea unui obiect într-un fișier text
void salveazaParticipantInFisier(Participant p, char* numeFisier){
    FILE* f = fopen(numeFisier, "w");
    fprintf(f, "%d %s %d", p.id, p.rol, p.nrCursuri);
    for (int i = 0; i < p.nrCursuri; i++) {
        fprintf(f, " %.2f", p.preturiCursuri[i]);
    }
    fprintf(f, "\n");
}

//3.3. Funcție pentru salvarea unui vector de obiecte într-un fișier text
void salveazaVectorParticipantiInFisier(Participant* vector,int dim, char* numeFisier){
    FILE* f = fopen(numeFisier, "w");

    for (int i = 0; i < dim; i++) {
        fprintf(f, "%d %s %d", vector[i].id, vector[i].rol, vector[i].nrCursuri);
        for (int j = 0; j < vector[i].nrCursuri; j++) {
            fprintf(f, " %.2f", vector[i].preturiCursuri[j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);

}

int main() {
    Participant* vector = NULL;
    int dimensiune = 10;

    citesteParticipantiDinFisier(&vector, "participanti.txt", dimensiune);
//    afisareVector(vector, dimensiune);

    salveazaParticipantInFisier(vector[0], "output-participant.txt");
    salveazaVectorParticipantiInFisier(vector, dimensiune, "output-vectorParticipanti.txt");

    return 0;


}