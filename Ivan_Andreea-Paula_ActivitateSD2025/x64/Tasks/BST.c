#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participant.h"

////creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
	Participant info;
};

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

void adaugaParticipantInArbore(Nod** radacina, Participant participant) {
    if ((*radacina) != NULL) {
        if (participant.id < (*radacina)->info.id) {
            adaugaParticipantInArbore(&((*radacina)->st), participant);
        }
        else if (participant.id > (*radacina)->info.id) {
            adaugaParticipantInArbore(&((*radacina)->dr), participant);
        }
        else {
            if ((*radacina)->info.rol != NULL) {
                free((*radacina)->info.rol);
            }
            if ((*radacina)->info.preturiCursuri != NULL) {
                free((*radacina)->info.preturiCursuri);
            }
            (*radacina)->info.nrCursuri = participant.nrCursuri;
            (*radacina)->info.preturiCursuri = (float*)malloc(sizeof(float) * participant.nrCursuri);
            for (int i = 0; i < participant.nrCursuri; i++) {
                (*radacina)->info.preturiCursuri[i] = participant.preturiCursuri[i];
            }
            (*radacina)->info.rol = (char*)malloc(strlen(participant.rol) + 1);
            strcpy_s((*radacina)->info.rol, strlen(participant.rol) + 1, participant.rol);
        }
    }

    else {
        (*radacina) = malloc(sizeof(Nod));
        (*radacina)->info = participant;
        (*radacina)->info.preturiCursuri = (float*)malloc(sizeof(float) * participant.nrCursuri);
        for (int i = 0; i < participant.nrCursuri; i++) {
            (*radacina)->info.preturiCursuri[i] = participant.preturiCursuri[i];
        }
        (*radacina)->info.rol = (char*)malloc(strlen(participant.rol) + 1);
        strcpy_s((*radacina)->info.rol, strlen(participant.rol) + 1, participant.rol);
        (*radacina)->st = NULL;
        (*radacina)->dr = NULL;
    }
}

Nod* citireArboreDeParticipantiDinFisier(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    Nod* radacina = NULL;
    while (!feof(file)) {
        Participant p = citireParticipantDinFisier(file);
        adaugaParticipantInArbore(&radacina, p);
        free(p.preturiCursuri);
        free(p.rol);
    }
    fclose(file);
    return radacina;
}

void afisareParticipantiInOrdine(Nod* radacina) {
    if (radacina != NULL) {
        afisareParticipantiInOrdine(radacina->st);
        afisareParticipant(radacina->info);
        afisareParticipantiInOrdine(radacina->dr);
    }
}

void afisareParticipantiPreordine(Nod* radacina) {
    if (radacina != NULL) {
        afisareParticipant(radacina->info);
        afisareParticipantiPreordine(radacina->st);
        afisareParticipantiPreordine(radacina->dr);
    }
}

void dezalocareArboreParticipanti(Nod** radacina) {
    if ((*radacina) != NULL) {
        dezalocareArboreParticipanti(&((*radacina)->st));
        dezalocareArboreParticipanti(&((*radacina)->dr));
        free((*radacina)->info.preturiCursuri);
        free((*radacina)->info.rol);
        free(*radacina);
        *radacina = NULL;
    }
}

Participant getParticipantByID(Nod* radacina, int id) {
    Participant p;
    p.id = -1;
    if (id > radacina->info.id) {
        return getParticipantByID(radacina->dr, id);
    }
    else {
        p = radacina->info;
        p.rol = (char*)malloc(strlen(radacina->info.rol) + 1);
        strcpy_s(p.rol, strlen(radacina->info.rol) + 1, radacina->info.rol);
        p.preturiCursuri = (float*)malloc(sizeof(float) * radacina->info.nrCursuri);
        for (int i = 0; i < radacina->info.nrCursuri; i++) {
            p.preturiCursuri[i] = radacina->info.preturiCursuri[i];
        }
        return p;
    }
    return p;
}

int determinareNumarNoduri(Nod* radacina) {
    if (radacina != NULL) {
        return 1 + determinareNumarNoduri(radacina->st) + determinareNumarNoduri(radacina->dr);

    }
    else {
        return 0;
    }
}
// 1. Functie pentru stergerea unui nod pe baza unui ID, mentinand proprietatile arborelui BST
Nod* stergeNodDupaID(Nod* radacina, int id) {
    if (radacina == NULL) return NULL;

    if (id < radacina->info.id) {
        radacina->st = stergeNodDupaID(radacina->st, id);
    }
    else if (id > radacina->info.id) {
        radacina->dr = stergeNodDupaID(radacina->dr, id);
    }
    else {
        if (radacina->st == NULL) {
            Nod* temp = radacina->dr;
            free(radacina->info.rol);
            free(radacina->info.preturiCursuri);
            free(radacina);
            return temp;
        }
        else if (radacina->dr == NULL) {
            Nod* temp = radacina->st;
            free(radacina->info.rol);
            free(radacina->info.preturiCursuri);
            free(radacina);
            return temp;
        }

        Nod* succesor = radacina->dr;
        while (succesor->st != NULL)
            succesor = succesor->st;

        free(radacina->info.rol);
        free(radacina->info.preturiCursuri);
        radacina->info.id = succesor->info.id;
        radacina->info.rol = strdup(succesor->info.rol);
        radacina->info.nrCursuri = succesor->info.nrCursuri;
        radacina->info.preturiCursuri = (float*)malloc(sizeof(float) * succesor->info.nrCursuri);
        for (int i = 0; i < succesor->info.nrCursuri; i++)
            radacina->info.preturiCursuri[i] = succesor->info.preturiCursuri[i];

        radacina->dr = stergeNodDupaID(radacina->dr, succesor->info.id);
    }

    return radacina;
}

int inaltime(Nod* radacina) {
    if (radacina == NULL)
        return 0;
    int h_st = inaltime(radacina->st);
    int h_dr = inaltime(radacina->dr);
    return 1 + (h_st > h_dr ? h_st : h_dr);
}

// 2. Functie pentru returnarea subarborelui cu inaltimea mai mare
Nod* subarboreCuInaltimeMaiMare(Nod* radacina) {
    if (radacina == NULL) return NULL;

    int h_st = inaltime(radacina->st);
    int h_dr = inaltime(radacina->dr);

    return (h_st > h_dr) ? radacina->st : radacina->dr;
}

//3. Functie pentru numararea nodurilor subordonate unui nod
int numarNoduriSubordine(Nod* radacina) {
    if (radacina == NULL) return 0;
    return determinareNumarNoduri(radacina) - 1;
}

//4. Functie pentru returnarea subarborelui cu mai multe noduri in subordine
Nod* subarboreCuMaiMultiDescendenti(Nod* radacina) {
    if (radacina == NULL) return NULL;

    int noduriSt = determinareNumarNoduri(radacina->st);
    int noduriDr = determinareNumarNoduri(radacina->dr);

    return (noduriSt > noduriDr) ? radacina->st : radacina->dr;
}

int main() {
    Nod* arbore = citireArboreDeParticipantiDinFisier("participanti.txt");
	afisareParticipantiPreordine(arbore);
    afisareParticipantiInOrdine(arbore);

	Participant p = getParticipantByID(arbore, 2);
	printf("\n\n---------------");
	afisareParticipant(p);

	int i = determinareNumarNoduri(arbore);
	printf("\nnumar noduri: %d", i);

    //Stergere nod dupa ID
    int idDeSters = 2;
    arbore = stergeNodDupaID(arbore, idDeSters);
    printf("\nDupa stergerea nodului cu ID = %d:\n", idDeSters);
    afisareParticipantiInOrdine(arbore);

    // Subarborele cu inaltime mai mare
    Nod* subarboreInalt = subarboreCuInaltimeMaiMare(arbore);
    afisareParticipantiInOrdine(subarboreInalt);
    

    // Numar noduri in subordine
    printf("\nNumar de noduri in subordine pentru radacina: %d\n",
        numarNoduriSubordine(arbore));

    // Subarbore cu mai multi descendenti
    Nod* subarboreCuMaiMulti = subarboreCuMaiMultiDescendenti(arbore);
    afisareParticipantiInOrdine(subarboreCuMaiMulti);


    dezalocareArboreParticipanti(&arbore);

    return 0;
}



