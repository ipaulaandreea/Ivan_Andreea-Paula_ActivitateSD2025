# Homework Repository for the Data Structures (C) Course


## Lucru cu fisiere:
Considerand structura Produs utilizata in problemele cu liste sa se implementeze urmatoarele functii:

1. functie pentru scrierea unui vector de produse intr-un fisier binar cu acces direct (indicatie: fiecare camp dinamic are alocat in fisier un buffer de dimensiune fixa)
2. functie pentru scrierea unui vector de produse intr-un fisier binar secvential in care pentru fiecare camp dinamic se aloca un spatiu de dimensiune egala cu spatiul ocupat de valori in Heap;
3. functie pentru citirea unui vector de produse intr-un fisier binar (pentru ambele variante de stocare); vectorul se aloca dinamic dupa determinarea numarului de produse din fisier;
4. functie pentru scrierea unui vector de produse intr-un fisier text in care descrierea produsului se scrie pe o linie (formatare tip CSV);
5. functie pentru scrierea unui vector de produse intr-un fisier text in care fiecare atribut al produsului se scrie pe o linie;
6. functie pentru citirea vectorului de produse din fisierul text (pt. ambele variante de scriere)

## Lucru cu liste:
Toate problemele sunt scrise pentru a gestiona date stocate in structura Produs:

``` struct Produs {
    int id;
    float pret;
    char* denumire;
    int* stocMagazine; // vectorul stocheaz? num?rul de produse de acest tip din fiecare magazin
}; 
```

1. functie pentru citirea unui Produs de la consola (cu validare): Student creareConsola() si void creareConsola(Student* adresaStud)
2. functie pentru afisarea la consola a unui Produs
3. functie pentru calculul stocului total al unui produs; functia intoarce un int
4. functie pentru crearea unui nod dintr-o lista simplu inlantuita si dublu inlantuita ce contine un Produs: nodListaSimpla* creareNodLS(Produs p) si nodListaDubla *creareNodLD(Produs p)
5. functie pentru inserarea unui Produs intr-o lista simplu inlantuita si dublu inlantuita: la inceput si la sfarsit
6. functie pentru afisarea unei liste simplu inlantuite si dublu inlantuite ce contine Produse
7. functie pentru inserarea unui Produs intr-o lista simplu inlantuita astfel incat lista sa se mentina sortata dupa denumirea produselor; lista este circulara;
8. functie pentru stergerea unui Produs dintr-o lista simplu inlantuita si dublu inlantuita (cautare dupa id)
9. functie pentru stergerea totala a unei liste simplu/dublu inlantuita cu eliberarea memoriei
10. functii pentru inserare si stergere produse dintr-o lista considerata STIVA
11. functie pentru crearea unui vector ce contine stocul total pentru fiecare Produs din lista simplu inlantuita: int* raportStoc(nodListaSimpla* capat, int * nrProduse)

## Lucru cu masive unidimensionale:
1. functie pentru crearea unui masiv dinamic de la consola (numarul de elemente este dat, iar valorile sunt citite de la consola): int* creareConsola(int nrElemente) si void creareConsola2(int** vector, int nrElemente)
2. functie pentru crearea unui masiv dinamic de la consola (numarul de elemente este citit in functie): int* creareConsola(int* nrElemente) si void creareConsola2(int** vector, int* nrElemente)
3. functie pentru crearea unui masiv dinamic pe baza unui vector existent: int* copiereVector(int* existent, int nrElemente)
4. functie pentru afisarea unui mesiv la consola: void afisareVector(int* vector, int nrElemente)
5. functii pentru prelucrari matematice: suma elementelor, suma elementelor negative, suma elementelor pozitive, media aritmetica si geometrica a elementelor, determinarea minimului, determinarea maximului. Acestea vor avea forma: [tip returnat] numeFunctie(int* vector, int nrElemente); functiile trebuie sa trateze si cazul particular cand vectorul primit nu exista;
6. functii pentru prelucrari matematice pe baza unei valori date: determinarea existentei unei valori in vector, determinarea numarului de valori mai mari/mai mici decat o valoare data, determinarea primei aparitii in vector a unei valori date, determinarea numarului de aparitii pentru o valoare data. Acestea vor avea forma: [tip returnat] numeFunctie(int* vector, int nrElemente int valoare)
7. functii pentru sortare a elementelor: bule, interschimbare si selectie;
8. functie pentru adaugarea unui element nou la un vector existent: int* adauga(int* vector, int* nrElemente, int valoare) si void adauga2(int** vector, int * nrElemente, int valoare)
9. functie pentru dezalocarea unui vector existent: void dezlocare(int* vector)