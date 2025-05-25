#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include <string.h>
#define MAX 100
#include "participant.h"

//Boilerplate code pentru stive//

Participant creareParticipant(int id, const char* rol, int nrCursuri, float* preturi) {
	Participant p;
	p.id = id;
	p.rol = strdup(rol);
	p.nrCursuri = nrCursuri;
	p.preturiCursuri = (float*)malloc(nrCursuri * sizeof(float));
	for (int i = 0; i < nrCursuri; i++) {
		p.preturiCursuri[i] = preturi[i];
	}
	return p;
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

void afisareParticipant(Participant p) {

	printf("\n ID Participant: %d\n", p.id);
	printf("Rol: %s\n", p.rol);
	printf("Numar cursuri: %d\n", p.nrCursuri);
	printf("Preturi cursuri:\n");
	for (int i = 0; i < p.nrCursuri; i++) {
		printf("  Curs %d: %.2f RON\n", i + 1, p.preturiCursuri[i]);
	}
}

void dezalocaParticipant(Participant* p) {
    if (p->rol != NULL) {
        free(p->rol);
        p->rol = NULL;
    }
    if (p->preturiCursuri != NULL) {
        free(p->preturiCursuri);
        p->preturiCursuri = NULL;
    }
}

typedef struct {
    Participant info;
    struct NodSimplu* next;
} NodSimplu;

void adaugaParticipantInListaSLL(NodSimplu** cap, Participant p){
    NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
    nou->info = p;
    nou->next = *cap;
    *cap = nou;
}
Participant stergeParticipantDinListaDeLaInceputSLL(NodSimplu** cap){
        if(*cap == NULL){
        printf("lista goala");
        return creareParticipant(0,NULL,0,NULL);
    } 

    NodSimplu* nodDeSters = *cap;
    Participant p = nodDeSters->info;
    
    *cap = nodDeSters->next;
    free(nodDeSters);
    return p;
};

typedef struct {
    Participant info;
    struct NodDublu* next;
    struct NodDublu* prev;
} NodDublu;

void adaugaParticipantInListaLaInceputDLL(NodDublu** cap, Participant p){
	NodDublu* nodNou = (NodDublu*)malloc(sizeof(NodDublu));
	nodNou->info = p;
    nodNou->prev = NULL;
    nodNou->next = *cap;
    if(*cap != NULL){
        (*cap)->prev = nodNou;
    }
    *cap = nodNou;
}

Participant stergeParticipantDinListaDeLaInceputDLL(NodDublu** cap){
    if(*cap == NULL){
        printf("lista goala");
        return creareParticipant(0,NULL,0,NULL);
    } 

    NodDublu* nodDeSters = *cap;
    Participant p = nodDeSters->info;
    *cap = nodDeSters->next;
    if(*cap != NULL){
        (*cap)->prev = NULL;
    }

    free(nodDeSters);
    return p;
}

/// Stiva implementata pe vector///

typedef struct {
    Participant vector[MAX];
    int top;
} StivaVector;

void init(StivaVector *s){
    s->top = -1;
}

int isEmpty(StivaVector *s){
    return s->top == -1;
}

int isFull(StivaVector *s){
    return s->top == MAX - 1;
}

void pushV(StivaVector *s, Participant p){
    if(isFull(s)){
        printf("Stiva plina");
        return;
    }
    s->vector[++(s->top)] = p;
}

Participant popV(StivaVector* s){
    if(isEmpty(s)){
        printf("Stiva goala");
        return creareParticipant(0,NULL,0,NULL);
    }
    return s->vector[(s->top)--];
}

void citireStivaDinFisierV(const char* numeFisier, StivaVector* s){
    FILE* file = fopen(numeFisier, "r");
    while(!feof(file)){
        Participant p = citireParticipantDinFisier(file);
        pushV(s, p);
    }
};
void afisareStivaV(StivaVector s){
    for(int i = s.top; i>=0; i--){
        afisareParticipant(s.vector[i]);
    }
};

void dezalocareStivaV(StivaVector* s){
    while(!isEmpty(s)){
        Participant p = popV(s);
        dezalocaParticipant(&p);
    };
    s->top = -1;
};

/// Stiva implementata pe lista simplu inlantuita ///

typedef struct {
    NodSimplu* top;
} StivaSinglyLinkedList;


void pushSLL(StivaSinglyLinkedList* s, Participant p){
    adaugaParticipantInListaSLL(&(s->top), p);
}

Participant popSLL(StivaSinglyLinkedList* s) {
    return stergeParticipantDinListaDeLaInceputSLL(&(s->top));
}

void citireStivaDinFisierSLL(const char* numeFisier, StivaSinglyLinkedList* s){
FILE* file = fopen(numeFisier, "r");
while(!feof(file)){
    Participant p = citireParticipantDinFisier(file);
    pushSLL(s, p);
}
fclose(file);
}

void afisareStivaSLL(StivaSinglyLinkedList s){
    NodSimplu* temp = s.top;
    while(temp!= NULL){
        afisareParticipant(temp->info);
        temp = temp->next;
    }
}
void dezalocaStivaSLL(StivaSinglyLinkedList* s) {
    while (s->top != NULL) {
        NodSimplu* nodCurent = s->top;
        s->top = s->top->next;

        dezalocaParticipant(&(nodCurent->info));
        free(nodCurent);
    }
}

///Stiva implementata pe lista dublu inlantuita///

typedef struct {
    NodDublu* top;
} StivaDoublyLinkedList;

void pushDLL(StivaDoublyLinkedList* s, Participant p){
    adaugaParticipantInListaLaInceputDLL(&(s->top), p);
}

Participant popDLL(StivaDoublyLinkedList* s) {
    return stergeParticipantDinListaDeLaInceputDLL(&(s->top));
}

void citireStivaDinFisierDLL(const char* numeFisier, StivaDoublyLinkedList* s){
FILE* file = fopen(numeFisier, "r");
while(!feof(file)){
    Participant p = citireParticipantDinFisier(file);
    pushDLL(s, p);
}
fclose(file);
}

void afisareStivaDLL(StivaDoublyLinkedList s){
    NodDublu* temp = s.top;
    while(temp!= NULL){
        afisareParticipant(temp->info);
        temp = temp->next;
    }
}
void dezalocaStivaDLL(StivaDoublyLinkedList* s) {
    while (s->top != NULL) {
        NodDublu* nodCurent = s->top;
        s->top = s->top->next;

        dezalocaParticipant(&(nodCurent->info));
        free(nodCurent);
    }
}


int main(){

        //PARTICIPANTI DE TEST//
    float preturi1[] = {100.0, 150.5};
    float preturi2[] = {80.0};
    float preturi3[] = {120.0, 200.0, 300.0};

    Participant p1 = creareParticipant(1, "Trainer", 2, preturi1);
    Participant p2 = creareParticipant(2, "Student", 1, preturi2);
    Participant p3 = creareParticipant(3, "Mentor", 3, preturi3);

    //STIVA PE VECTOR//
    StivaVector stivaVector;
    init(&stivaVector);
    citireStivaDinFisierV("participanti.txt", &stivaVector);

    pushV(&stivaVector, p1);
    pushV(&stivaVector, p2);
    pushV(&stivaVector, p3);

    printf("\n Stiva pe vector \n");
    afisareStivaV(stivaVector);
    dezalocareStivaV(&stivaVector);

    //STIVA PE LISTA SIMPLU INLANTUITA//
    StivaSinglyLinkedList stivaSimpla;
    stivaSimpla.top = NULL;
    citireStivaDinFisierSLL("participanti.txt", &stivaSimpla);

    pushSLL(&stivaSimpla, creareParticipant(1, "Trainer", 2, preturi1));
    pushSLL(&stivaSimpla, creareParticipant(2, "Student", 1, preturi2));
    pushSLL(&stivaSimpla, creareParticipant(3, "Mentor", 3, preturi3));

    printf("\n Stiva pe lista simplu inlantuita \n");
    afisareStivaSLL(stivaSimpla);
    while (stivaSimpla.top != NULL) {
        Participant p = popSLL(&stivaSimpla);
        dezalocaParticipant(&p);
    }

    //STIVA PE LISTA DUBLU INLANTUITA//
    StivaDoublyLinkedList stivaDubla;
    stivaDubla.top = NULL;
    citireStivaDinFisierDLL("participanti.txt", &stivaDubla);

    pushDLL(&stivaDubla, creareParticipant(1, "Trainer", 2, preturi1));
    pushDLL(&stivaDubla, creareParticipant(2, "Student", 1, preturi2));
    pushDLL(&stivaDubla, creareParticipant(3, "Mentor", 3, preturi3));

    printf("\n Stiva pe lista dublu inlantuita \n");
    afisareStivaDLL(stivaDubla);
    dezalocaStivaDLL(&stivaDubla);


    return 0;
}