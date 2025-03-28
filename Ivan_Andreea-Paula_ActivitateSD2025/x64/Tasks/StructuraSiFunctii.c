#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include "participant.h"

//1.2 Funcție pentru citirea unui articol de la tastatură.
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

//1.3. Funcție care calculează o valoare (ex: medie, sumă, maxim, minim).
float calculareMediePreturiCursuri(Participant p) {
    if (p.nrCursuri == 0) {
        printf("Participantul nu are cursuri.\n");
        return 0;
    }

    float suma = 0;
    for (int i = 0; i < p.nrCursuri; i++) {
        suma += p.preturiCursuri[i];
    }

    return suma / p.nrCursuri;
};

//1.4. Funcție care modifică un atribut al articolului.
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

//1.5. Funcție pentru afișarea unui articol
void afisareParticipant(Participant p) {

    printf("\n ID Participant: %d\n", p.id);
    printf("Rol: %s\n", p.rol);
    printf("Numar cursuri: %d\n", p.nrCursuri);
    printf("Preturi cursuri:\n");
    for (int i = 0; i < p.nrCursuri; i++) {
        printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
    }
};

int main() {
    Participant p = citireParticipantDeLaTastatura();
    afisareParticipant(p);
    printf("Medie preturi pentru primul participant: %.2f\n", calculareMediePreturiCursuri(p));
    schimbareRol(&p);
    afisareParticipant(p);

    return 0;

}