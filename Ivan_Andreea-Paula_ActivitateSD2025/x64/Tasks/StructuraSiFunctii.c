#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

//Paula Ivan -> P si I

struct StucturaParticipant {
    int id;
    char* rol;
    int nrCursuri;
    float* preturiCursuri;
};
typedef struct StucturaParticipant Participant;

Participant citireParticipantDeLaTastatura() {

    Participant p;

    printf("Introduceti ID-ul participantului: ");
    scanf_s("%d", &p.id);

    char buffer[100];
    printf("Introduceti rolul participantului: ");
    scanf_s(" %[^\n]", buffer, (unsigned)_countof(buffer));
    p.rol = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    if (p.rol != NULL) {
        strcpy_s(p.rol, (strlen(buffer) + 1), buffer);
       ;
    }
    printf("Introduceti numarul de cursuri: ");
    scanf_s("%d", &p.nrCursuri);

    p.preturiCursuri = (float*)malloc(p.nrCursuri * sizeof(float));
    if (p.preturiCursuri == NULL) {
        printf("Eroare la alocarea memoriei pentru preturi!\n");
        exit(1);
       

    }
    printf("Introduceti preturile cursurilor:\n");
    for (int i = 0; i < p.nrCursuri; i++) {
        printf("Curs %d: ", i + 1);
        scanf_s("%f", &p.preturiCursuri[i]);
    }

    return p;
};

float calculareMediePreturiCursuri(Participant p) {
    if (p.nrCursuri == 0) {
        printf("Participantul nu are cursuri.\n");
        return;
    }

    float suma = 0;
    for (int i = 0; i < p.nrCursuri; i++) {
        suma += p.preturiCursuri[i];
    }

    return suma / p.nrCursuri;
};

void schimbareRol(Participant* p) {
    if (p == NULL) {
        printf("Eroare: Pointerul la participant este NULL!\n");
        return;
    }

    free(p->rol);

    char buffer[50];
    printf("Introduceti noul rol pentru participantul %d: ", p->id);
    scanf_s(" %[^\n]", buffer, (unsigned)_countof(buffer));

    p->rol = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    if (p->rol == NULL) {
        printf("Eroare la alocarea memoriei pentru noul rol!\n");
        exit(1);
    }
    strcpy_s(p->rol, strlen(buffer) + 1, buffer);
};

void afisareParticipant(Participant p) {

    printf("\nParticipant ID: %d\n", p.id);
    printf("Rol: %s\n", p.rol);
    printf("Numar cursuri: %d\n", p.nrCursuri);
    printf("Preturi cursuri:\n");
    for (int i = 0; i < p.nrCursuri; i++) {
        printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
    }
};


int main()
{
    Participant p = citireParticipantDeLaTastatura();
    afisareParticipant(p);
    printf("Medie preturi pentru primul participant: %.2f\n", calculareMediePreturiCursuri(p));
    schimbareRol(&p);
    afisareParticipant(p);
    
    return 0;

}