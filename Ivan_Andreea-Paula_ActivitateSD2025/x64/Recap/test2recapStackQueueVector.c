#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define MAX 100



struct Brutarie {
    char* nume;
    int id; 
    int nrAngajati;
};

typedef struct Brutarie Brutarie;

struct Nod {
    Brutarie info;
    Nod* fiuStg;
    Nod* fiuDr;
};

typedef struct Nod Nod;

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

typedef struct Stack {
    Brutarie data[MAX];
    int top;
} Stack;

void init(Stack *s){
    s->top = -1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

int isFull(Stack *s){
    return s->top == MAX - 1;
}

void push(Stack *s, Brutarie b){
    if(isFull(s)){
        printf("Stack plin");
        return;
    }
    s->data[++(s->top)] = b;
}

Brutarie pop(Stack* s){
    Brutarie b = initializareBrutarie(NULL, 0, 0);
    if(isEmpty(s)){
        printf("Stack gol");
        return b;
    }
    return s->data[(s->top)--];
}

typedef struct Queue{
    Brutarie data[MAX];
    int front, rear, size;
} Queue;

void init(Queue* q){
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue* q){
    return q->size == 0;
}

int isFull(Queue* q){
    return q->size == MAX;
}

void enqueue(Queue* q, Brutarie b){
    if(isFull(q)){
        printf("Coada plina!");
        return;
    }
    q->rear = (q->rear +1 ) % MAX;
    q->data[q->rear] = b;
    q->size++;
}

Brutarie dequeue(Queue* q){
    Brutarie invalid = initializareBrutarie(NULL, 0, 0);
    if(isEmpty(q)){
        printf("Coada goala!");
        return invalid;
    }
    Brutarie val = q->data[q->front];
    q->front = (q->front+1) % MAX;
    q->size--;
    return val;
}