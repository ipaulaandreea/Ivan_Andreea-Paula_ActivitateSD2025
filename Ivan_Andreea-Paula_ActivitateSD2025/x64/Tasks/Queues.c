#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include <string.h>
#define MAX 100
#include "participant.h"

//Boilerplate code pentru cozi//

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

typedef struct {
    Participant info;
    struct NodDublu* next;
    struct NodDublu* prev;
} NodDublu;

/// Coada implementata pe vector///

typedef struct CoadaV{
    Participant vector[MAX];
    int front, rear, size;
} CoadaV;

void init(CoadaV* q){
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(CoadaV* q){
    return q->size == 0;
}

int isFull(CoadaV* q){
    return q->size == MAX;
}

void enqueueV(CoadaV* q, Participant p){
    if(isFull(q)){
        printf("Coada plina!");
        return;
    }
    q->rear = (q->rear +1 ) % MAX;
    q->vector[q->rear] = p;
    q->size++;
}

Participant dequeueV(CoadaV* q){
    if(isEmpty(q)){
        printf("Coada goala!");
        return creareParticipant(0, NULL, 0, NULL);
    }
    Participant val = q->vector[q->front];
    q->front = (q->front+1) % MAX;
    q->size--;
    return val;
}
void citireCoadaDinFisierV(const char* numeFisier, CoadaV* q){
    FILE* file = fopen(numeFisier, "r");
    while(!feof(file)){
        enqueueV(q, citireParticipantDinFisier(file));
    }
    fclose(file);
};

void afisareCoadaV(CoadaV q){
        int index = q.front;

    for (int i = 0; i < q.size; i++) {
        afisareParticipant(q.vector[index]);
        index = (index + 1) % MAX;
    }
}

void dezalocareCoadaV(CoadaV* q){
        int index = q->front;

    for (int i = 0; i < q->size; i++) {
        dezalocaParticipant(&(q->vector[index]));
        index = (index + 1) % MAX;
    }

    q->front = -1;
    q->rear = -1;
    q->size = 0;
};

/// Coada implementata pe lista simpla inlantuita///

typedef struct {
    NodSimplu* front;  
    NodSimplu* rear; 
} CoadaSLL;

void initCoadaSLL(CoadaSLL* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueueSLL(CoadaSLL* q, Participant p) {
    NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
    nou->info = p;
    nou->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = nou;
    } else {
        q->rear->next = nou;
        q->rear = nou;
    }
}

Participant dequeueSLL(CoadaSLL* q) {
    if (q->front == NULL) {
        printf("Coada este goala!\n");
        return creareParticipant(0, NULL, 0, NULL);
    }

    NodSimplu* temp = q->front;
    Participant p = temp->info;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return p;
}

void citireCoadaDinFisierSLL(const char* numeFisier, CoadaSLL* q) {
    FILE* file = fopen(numeFisier, "r");

    while (!feof(file)) {
        Participant p = citireParticipantDinFisier(file);
            enqueueSLL(q, p);
    }
    fclose(file);
}

void afisareCoadaSLL(CoadaSLL q) {
    NodSimplu* temp = q.front;
    while (temp != NULL) {
        afisareParticipant(temp->info);
        temp = temp->next;
    }
}

void dezalocareCoadaSLL(CoadaSLL* q) {
    while (q->front != NULL) {
        NodSimplu* temp = q->front;
        q->front = q->front->next;
        dezalocaParticipant(&(temp->info));
        free(temp);
    }
    q->rear = NULL;
}

/// Coada implementata pe lista dublu inlantuita ///

typedef struct {
    NodDublu* front; 
    NodDublu* rear;   
} CoadaDLL;

void initCoadaDLL(CoadaDLL* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueueDLL(CoadaDLL* q, Participant p) {
    NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
    nou->info = p;
    nou->next = NULL;
    nou->prev = q->rear;

    if (q->rear == NULL) {
        q->front = q->rear = nou;
    } else {
        q->rear->next = nou;
        q->rear = nou;
    }
}

Participant dequeueDLL(CoadaDLL* q) {
    if (q->front == NULL) {
        printf("Coada este goala!\n");
        return creareParticipant(0, NULL, 0, NULL);
    }

    NodDublu* temp = q->front;
    Participant p = temp->info;
    q->front = q->front->next;

    if (q->front != NULL)
        q->front->prev = NULL;
    else
        q->rear = NULL;

    free(temp);
    return p;
}

void citireCoadaDinFisierDLL(const char* numeFisier, CoadaDLL* q) {
    FILE* file = fopen(numeFisier, "r");

    while (!feof(file)) {
        Participant p = citireParticipantDinFisier(file);
            enqueueSLL(q, p);
    }
    fclose(file);
}

void afisareCoadaDLL(CoadaDLL q) {
    NodDublu* temp = q.front;
    while (temp != NULL) {
        afisareParticipant(temp->info);
        temp = temp->next;
    }
}

void dezalocareCoadaDLL(CoadaDLL* q) {
    while (q->front != NULL) {
        NodDublu* temp = q->front;
        q->front = q->front->next;
        dezalocaParticipant(&(temp->info));
        free(temp);
    }
    q->rear = NULL;
}

int main() {
        // COADĂ PE VECTOR //
    CoadaV coadaV;
    init(&coadaV);
    citireCoadaDinFisierV("participanti.txt", &coadaV);

    printf("Coada pe vector \n");
    afisareCoadaV(coadaV);
    dezalocareCoadaV(&coadaV);


    // COADĂ PE LISTĂ SIMPLU INLĂNȚUITĂ //
    CoadaSLL coadaSLL;
    initCoadaSLL(&coadaSLL);
    citireCoadaDinFisierSLL("participanti.txt", &coadaSLL);

    printf("\nCoada pe lista simplu inlantuita \n");
    afisareCoadaSLL(coadaSLL);
    dezalocareCoadaSLL(&coadaSLL);


    // COADĂ PE LISTĂ DUBLU INLĂNȚUITĂ //
    CoadaDLL coadaDLL;
    initCoadaDLL(&coadaDLL);
    citireCoadaDinFisierDLL("participanti.txt", &coadaDLL);

    printf("\n Coada pe lista dublu inlantuita \n");
    afisareCoadaDLL(coadaDLL);
    dezalocareCoadaDLL(&coadaDLL);


    return 0;

}