#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>


struct StructuraMasina{
    int id; 
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

typedef struct StructuraMasina Masina;



Masina citireMasinaDinFisier(FILE* file){
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = (char*)malloc(strlen(aux)+1);
    strcpy_s(m1.model, strlen(aux)+1, aux);
    aux = strtok(NULL, sep);
    m1.numeSofer = (char*)malloc(strlne(aux)+1);
    strcpy_s(m1.numeSofer, strlen(aux)+1, aux);
    m1.serie = *strtok(NULL, sep);
    return m1; 
}

void afisareMasina(Masina masina){
    printf("ID: %d\n",masina.id);
    printf("Nr. usi:%d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

typedef struct Heap{
    Masina* vector;
    int nrMasini;
    int lungime;
} Heap;

Heap initializareHeap(int lungime){
    Heap heap;
    heap.lungime = lungime;
    heap.nrMasini = 0;
    heap.vector = (Masina*)malloc(sizeof(Masina));
    return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod){
    int pozFiuSt = 2*pozitieNod +1;
    int pozFiuDr = 2* pozitieNod +2;
    int pozMax = pozitieNod;

    if(pozFiuSt < heap.nrMasini && heap.vector[pozMax].pret < heap.vector[pozFiuSt].pret){
        pozMax = pozFiuSt;
    }
        if(pozFiuDr < heap.nrMasini && heap.vector[pozMax].pret < heap.vector[pozFiuDr].pret){
        pozMax = pozFiuDr;
    }
    if(pozMax != pozitieNod){
        Masina aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[pozitieNod];
        heap.vector[pozitieNod] = aux;
    }
    if(pozMax <= (heap.nrMasini-2)/2){
        filtreazaHeap(heap, pozMax);
    }
}

void citireHeapDinFisier(const char* numeFisier){
    FILE* file = fopen(numeFisier, "r");
    Heap heap = initializareHeap(10);
    while(!feof(file)){
        heap.vector[heap.nrMasini++] = citireMasinaDinFisier(file);
    }
    fclose(file);
    for(int i = (heap.nrMasini-2)/2; i >= 0; i--){
        filtreazaHeap(heap, i);
    }
    return heap;
}

void afisareHeap(Heap heap){
    for(int i = 0; i < heap.nrMasini; i++){
        afisareMasina(heap.vector[i]);
    }
}

void afisareHeapAscuns(Heap heap){
    for(int i = heap.nrMasini; i < heap.lungime; i++){
        afisareMasina(heap.vector[i]);
    }
}

Masina extrageObiectDinHeap(Heap* heap){
    if(heap->nrMasini > 0){
        Masina aux = heap->vector[0];
        heap->vector[0] = heap->vector[heap->nrMasini-1];
        heap->vector[heap->nrMasini - 1] = aux;
        heap->nrMasini--;
        for(int i = (heap->nrMasini -2)/2; i>=0; i--){
            filtreazaHeap(*heap, i);
        }
            return aux;
    }
}

void dezalocareHeap(Heap* heap){
    for(int i = 0; i < heap->lungime; i++){
        free(heap->vector[i].model);
        free(heap->vector[i].numeSofer);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->lungime = 0;
    heap->nrMasini = 0;
}