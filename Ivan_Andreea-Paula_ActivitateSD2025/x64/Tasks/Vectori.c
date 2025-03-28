#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"

Participant initializare(int id, const char* rol, int nrCursuri, float* preturiCursuri) {
    Participant p;
    p.id = id;
    p.nrCursuri = nrCursuri;
    p.rol = (char*)malloc((strlen(rol) + 1)*sizeof(char));
    strcpy_s(p.rol, strlen(rol) + 1, rol);
    p.preturiCursuri = (float*)malloc(sizeof(preturiCursuri)*sizeof(float));
    for(int i = 0; i < nrCursuri; i++){
        p.preturiCursuri[i] = preturiCursuri[i];
    }
    return p;
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

//2.2. Funcție pentru copierea obiectelor care îndeplinesc o condiție într-un nou vector.
void copiazaParticipantiCuMulteCursuri(Participant* vector, char nrElemente, int pragNrCursuri,
                                       Participant** vectorNou, int* dimensiune){
    *dimensiune = 0;
    for(int i = 0; i < nrElemente; i++){
        if(vector[i].nrCursuri >= pragNrCursuri){
            (*dimensiune)++;
        }
    }
    *vectorNou = (Participant*)malloc(sizeof(Participant)*(*dimensiune));
    int k = 0;
    for(int i = 0; i < nrElemente; i++){
        if(vector[i].nrCursuri >= pragNrCursuri){
            (*vectorNou)[k] = vector[i];

            (*vectorNou)[k].rol = (char*) malloc(strlen(vector[i].rol)+1);
            strcpy_s((*vectorNou)[k].rol, strlen(vector[i].rol)+1, vector[i].rol);

            (*vectorNou)[k].preturiCursuri = (float*)malloc((*vectorNou)[k].nrCursuri * sizeof(float));
            for(int j = 0; j < vector[i].nrCursuri;j++){
                (*vectorNou)[k].preturiCursuri[j] =  vector[i].preturiCursuri[j];
            }

            k++;
        }
    }
}

//2.3. Funcție pentru mutarea obiectelor care îndeplinesc o altă condiție într-un nou vector
void mutaStudenti(Participant** vector, int* nrElemente, const char* rol,
                  Participant** vectorStudenti, int* dimensiune){

    *dimensiune = 0;
    for(int i = 0; i < *nrElemente; i++){
        if(strcmp((*vector)[i].rol, rol) == 0){
            (*dimensiune)++;
        }
    }
    *vectorStudenti = (Participant*)malloc(sizeof (Participant) * (*dimensiune));
    int k = 0;
    for (int i = 0; i < *nrElemente;){
        if(strcmp((*vector)[i].rol, rol) == 0){
            (*vectorStudenti)[k] = (*vector)[i];

            (*vectorStudenti)[k].rol = (char*) malloc(strlen((*vector)[i].rol)+1);
            strcpy_s((*vectorStudenti)[k].rol, strlen((*vector)[i].rol)+1, (*vector)[i].rol);

            (*vectorStudenti)[k].preturiCursuri = (float*) malloc((*vector)[i].nrCursuri*sizeof(float));
            for(int j = 0; j < (*vector)[i].nrCursuri; j++){
                (*vectorStudenti)[k].preturiCursuri[j] = (*vector)[i].preturiCursuri[j];
            }
            free((*vector)[i].rol);
            free((*vector)[i].preturiCursuri);

            for (int j = i; j < *nrElemente - 1; j++) {
                (*vector)[j] = (*vector)[j + 1];
            }

            (*nrElemente)--;
            k++;
        } else {
            i++;
        }
    }

}

//2.4. Funcție pentru concatenarea a doi vectori
void concatenareVectori(Participant** vectorRezultat, int* dimensiune,
                        Participant* vector1, const int* dimensiuneV1,
                        Participant* vector2, const int* dimensiuneV2){
    *dimensiune = (*dimensiuneV1) + (*dimensiuneV2);
    *vectorRezultat = (Participant*) malloc(sizeof(Participant) * (*dimensiune));

    for(int i = 0; i < *dimensiuneV1; i++){
        (*vectorRezultat)[i] = vector1[i];
        (*vectorRezultat)[i].rol = (char*) malloc(strlen(vector1[i].rol)+1);
        strcpy_s((*vectorRezultat)[i].rol, strlen(vector1[i].rol)+1, vector1[i].rol);

        (*vectorRezultat)[i].preturiCursuri = (float*)malloc((*vectorRezultat)[i].nrCursuri * sizeof(float));
        for (int k = 0; k < vector1[i].nrCursuri; k++) {
            (*vectorRezultat)[i].preturiCursuri[k] = vector1[i].preturiCursuri[k];
        }    }

    for(int j = 0; j < *dimensiuneV2; j++) {
        (*vectorRezultat)[j + (*dimensiuneV1)] = vector2[j];
        (*vectorRezultat)[j + (*dimensiuneV1)].rol = (char *) malloc(strlen(vector2[j].rol) + 1);
        strcpy_s((*vectorRezultat)[j + (*dimensiuneV1)].rol, strlen(vector2[j].rol) + 1, vector2[j].rol);

        (*vectorRezultat)[j + (*dimensiuneV1)].preturiCursuri = (float *) malloc(
                (*vectorRezultat)[j + (*dimensiuneV1)].nrCursuri * sizeof(float));
        for (int l = 0; l < vector2[j].nrCursuri; l++) {
            (*vectorRezultat)[j + (*dimensiuneV1)].preturiCursuri[l] = vector2[j].preturiCursuri[l];
        }
    }
}

//2.5. Funcție pentru afișarea unui vector de obiecte.
void afisareVector(Participant* vector, int nrElemente){
    for(int i = 0; i < nrElemente; i++){
        afisareParticipant(vector[i]);
        printf("\n");
    }
}

int main()
{
    //2.1. Crearea unui vector alocat dinamic cu cel puțin 5 obiecte de tipul structurii definite.
    int nrParticipanti = 5;
    Participant* participanti;
    participanti = (Participant*)malloc(nrParticipanti * sizeof(Participant));

    float cursuri1[] = {100.0, 150.0};
    float cursuri2[] = {200.0};
    float cursuri3[] = {80.0, 90.0, 120.0};
    float cursuri4[] = {130.0, 160.0};
    float cursuri5[] = {95.0};

    participanti[0] = initializare(1, "student", 2, cursuri1);
    participanti[1] = initializare(2, "profesor", 1, cursuri2);
    participanti[2] = initializare(3, "invitat", 3, cursuri3);
    participanti[3] = initializare(4, "student", 2, cursuri4);
    participanti[4] = initializare(5, "asistent", 1, cursuri5);

    for (int i = 0; i < nrParticipanti; i++) {
        afisareParticipant(participanti[i]);
    }

    Participant* participantiCuMulteCursuri = NULL;
    int nrParticipantiCuMulteCursuri = 0;
    copiazaParticipantiCuMulteCursuri(participanti, nrParticipanti, 3,
                                      &participantiCuMulteCursuri, &nrParticipantiCuMulteCursuri);
    printf("\nParticipanti cu numar mare de cursuri:\n");
    afisareVector(participantiCuMulteCursuri, nrParticipantiCuMulteCursuri);

    Participant* participantiStudenti = NULL;
    int nrParticipantiStudenti = 0;
    mutaStudenti(&participanti, &nrParticipanti, "student",
                 &participantiStudenti, &nrParticipantiStudenti);
    printf("\nParticipanti cu rolul de studenti:\n");
    afisareVector(participantiStudenti, nrParticipantiStudenti);

    printf("\nLista de participanti dupa mutarea studentilor:\n");
    afisareVector(participanti, nrParticipanti);

    Participant* vectorConcatenat = NULL;
    int dimVectorConcatenat = 0;
    concatenareVectori(&vectorConcatenat, &dimVectorConcatenat,
                       participantiStudenti, &nrParticipantiStudenti,
                       participanti, &nrParticipanti);
    printf("\nLista concatenata:\n");
    afisareVector(vectorConcatenat, dimVectorConcatenat);

    return 0;

}