#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define MAX 100

typedef struct Brutarie {
    char* nume;
    int id; 
    int nrAngajati;
} Brutarie;

typedef struct Stack{
    int top;
    Brutarie vector[MAX];

} Stack;

void initializareStack(Stack* s){
    s->top = -1;
}

void isEmpty(Stack* s){
    return s->top == -1;
}

void isFull(Stack* s){
    return s->top == MAX - 1;
}

void push(Stack* s, Brutarie b){
    s->vector[++(s->top)] = b;

}

Brutarie initializareBrutarie(const char* nume, int id, int nrAngajati) {
	Brutarie b;
	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.id = id;
	b.nrAngajati = nrAngajati;

	return b;
}


Brutarie pop(Stack* s){
    Brutarie b = initializareBrutarie(NULL, 0, 0);

    b = s->vector[(s->top)--];
    return b;
}

typedef struct Queue{
    Brutarie vector[MAX];
    int front, rear, size;
}Queue;

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
    q->rear = (q->rear+1) % MAX;
    q->vector[q->rear] = b;
    q->size++;
}

Brutarie dequeue(Queue* q){
    Brutarie val = q->vector[q->front];
    q->front = (q->front+1) %MAX;
    q->size--;
    return val;

}