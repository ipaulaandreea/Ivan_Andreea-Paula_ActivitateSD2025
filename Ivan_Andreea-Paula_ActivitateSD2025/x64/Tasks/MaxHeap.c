#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Pacient {
	int id;
	char* nume;
	int varsta;
	char* simptome;
	int gradUrgenta;
};
typedef struct Pacient Pacient;

 struct MaxHeap {
	 int lungime;
	 Pacient* vector;
	 int nrPacienti;
};

 typedef struct MaxHeap MaxHeap;

 Pacient initializarePacient(int id, char* nume, int varsta, char* simptome, int gradUrgenta){
	Pacient p;
    p.id = id;
    p.varsta = varsta;
    p.gradUrgenta = gradUrgenta;
    p.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(p.nume, nume);
    p.simptome = (char*)malloc(strlen(simptome) + 1);
    strcpy(p.simptome, simptome);
    return p;
 }

 Pacient citirePacientDinFisier(FILE* file) {
	 char buffer[100];
	 char sep[3] = ",\n";
	 fgets(buffer, 100, file);
	 char* aux;
	 Pacient p1;
	 aux = strtok(buffer, sep);
	 p1.id = atoi(aux);
	 aux = strtok(NULL, sep);
	 p1.nume = malloc(strlen(aux) + 1);
	 strcpy_s(p1.nume, strlen(aux) + 1, aux);
	 p1.varsta = atoi(strtok(NULL, sep));
	 p1.gradUrgenta = atoi(strtok(NULL, sep));
	 aux = strtok(NULL, sep);
	 p1.simptome = malloc(strlen(aux) + 1);
	 strcpy_s(p1.simptome, strlen(aux) + 1, aux);

	 return p1;
 }

 void afisarePacient(Pacient p) {
	 printf("Nume: %s , Varsta: %d,  Simptome: %s, Grad urgenta: %d\n",
		 p.nume, p.varsta, p.simptome, p.gradUrgenta);
 }

 MaxHeap initializareHeap(int lungime) {
	 MaxHeap maxHeap;
	 maxHeap.lungime = lungime;
	 maxHeap.nrPacienti = 0;
	 maxHeap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);
	 return maxHeap;
 }

 void filtreazaHeap(MaxHeap heap, int pozitieNod) {
	 int pozFiuSt = 2 * pozitieNod + 1;
	 int pozFiuDr = 2 * pozitieNod + 2;
	 int pozMax = pozitieNod;

	 if (pozFiuSt < heap.nrPacienti && heap.vector[pozMax].gradUrgenta < heap.vector[pozFiuSt].gradUrgenta) {
		 pozMax = pozFiuSt;
	 }

	 if (pozFiuDr < heap.nrPacienti && heap.vector[pozMax].gradUrgenta < heap.vector[pozFiuDr].gradUrgenta) {
		 pozMax = pozFiuDr;
	 }

	 if (pozMax != pozitieNod) {
		 Pacient aux = heap.vector[pozMax];
		 heap.vector[pozMax] = heap.vector[pozitieNod];
		 heap.vector[pozitieNod] = aux;
		 if (pozMax <= (heap.nrPacienti - 2) / 2) {
			 filtreazaHeap(heap, pozMax);
		 }
	 }
 }

 MaxHeap citireHeapDinFisier(const char* numeFisier) {
	 FILE* file = fopen(numeFisier, "r");
	 MaxHeap heap = initializareHeap(10);
	 while (!feof(file)) {
		 heap.vector[heap.nrPacienti++] = citirePacientDinFisier(file);
	 }
	 fclose(file);
	 for (int i = (heap.nrPacienti - 2) / 2; i >= 0; i--) {
		 filtreazaHeap(heap, i);
	 }
	 return heap;
 };

 void afisareHeap(MaxHeap heap) {
	 for (int i = 0; i < heap.nrPacienti; i++) {
		 afisarePacient(heap.vector[i]);
	 }
 }

 void afisareHeapAscuns(MaxHeap heap) {
	 for (int i = heap.nrPacienti; i < heap.lungime; i++) {
		 afisarePacient(heap.vector[i]);
	 }
 }

 Pacient extragePacient(MaxHeap* heap) {
	 if (heap->nrPacienti > 0) {
		 Pacient aux = heap->vector[0];
		 heap->vector[0] = heap->vector[heap->nrPacienti - 1];
		 heap->vector[heap->nrPacienti - 1] = aux;
		 heap->nrPacienti--;
		 for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--) {
			 filtreazaHeap(*heap, i);
		 }
		 return aux;
	 }
 }

 void dezalocareHeap(MaxHeap* heap) {
	 for (int i = 0; i < heap->lungime; i++) {
		 free(heap->vector[i].nume);
		 free(heap->vector[i].simptome);
	 }
	 free(heap->vector);
	 heap->vector = NULL;
	 heap->lungime = 0;
	 heap->nrPacienti = 0;
 }

void prioritizare(MaxHeap* heap, int index){
	if(index && heap->vector[(index - 1)/2].gradUrgenta < heap->vector[index].gradUrgenta){
		Pacient aux = heap->vector[index];
		heap->vector[index] = heap->vector[(index-1)/2];
		heap->vector[(index-1)/2] = aux;
		prioritizare(heap, (index-1)/2);
	}
}

void inserarePacient(MaxHeap* heap, Pacient p){
	if(heap->nrPacienti >= heap->lungime){
		heap->lungime *=2;
		heap->vector = (Pacient*)realloc(heap->vector, sizeof(Pacient)*heap->lungime);
	}
	heap->vector[heap->nrPacienti] = p;
	prioritizare(heap, heap->nrPacienti);
	heap->nrPacienti++;
}

 int main() {
	 MaxHeap heap = citireHeapDinFisier("pacienti.txt");
	 afisareHeap(heap);

	 Pacient p = extragePacient(&heap);
	 printf("Pacientul cu prioritate maxima:");
	 afisarePacient(p);
	 
	 inserarePacient(&heap, initializarePacient(6, "Matei Ion", 45, "Febra", 41));
	 afisareHeap(heap);
 }


