# Task-uri suplimentare

## 1. Structura și funcții
Se consideră prima literă din numele vostru și prima literă din prenumele vostru. Se va construi un articol care să conțină aceste două litere.

**Exemplu:**  
Alin Zamfiroiu → A și Z.  
**Structura:**  
```c
struct Magazin {
    int cod;
    char* denumire;
    int nrProduse;
    float *preturi;
};
```
- Articolul trebuie să aibă logică.
- Articolul trebuie să fie un substantiv.
- Trebuie să aibă cel puțin trei atribute, dintre care unul alocat dinamic.
- Funcții necesare:
  - Funcție pentru citirea unui articol de la tastatură.
  - Funcție care calculează o valoare (ex: medie, sumă, maxim, minim).
  - Funcție care modifică un atribut al articolului.
  - Funcție pentru afișarea unui articol.

---

## 2. Vectori
- Crearea unui vector alocat dinamic cu cel puțin 5 obiecte de tipul structurii definite.
- Funcție pentru copierea obiectelor care îndeplinesc o condiție într-un nou vector.
- Funcție pentru mutarea obiectelor care îndeplinesc o altă condiție într-un nou vector.
- Funcție pentru concatenarea a doi vectori.
- Funcție pentru afișarea unui vector de obiecte.
- Apelarea tuturor funcțiilor în `main()`.

---

## 3. Fișiere
- Crearea unui fișier cu cel puțin 10 obiecte.
- Funcție pentru citirea obiectelor din fișier și salvarea într-un vector.
- Funcție pentru salvarea unui obiect într-un fișier text.
- Funcție pentru salvarea unui vector de obiecte într-un fișier text.

---

## 4. Matrice
- Citirea obiectelor dintr-un fișier și salvarea într-un vector.
- Copierea elementelor într-o matrice alocată dinamic, aplicând un criteriu de grupare pe linii.
- Funcție pentru sortarea liniilor matricei după numărul de elemente.
- Funcție pentru afișarea elementelor din matrice.

---

## 5. Liste simplu înlănțuite
- Funcție pentru ștergerea unui nod de pe o poziție dată.
- Funcție pentru inserarea elementelor în ordine crescătoare după un atribut.
- Funcție pentru salvarea într-un vector a elementelor care îndeplinesc o condiție (deep copy).
- Funcție pentru interschimbarea a două elemente în listă pe baza pozițiilor.

---

## 6. Liste dublu înlănțuite
- Funcție pentru ștergerea unui nod de pe o poziție dată.
- Funcție pentru inserarea elementelor în ordine crescătoare după un atribut.
- Funcții pentru parcurgerea listei în ordine crescătoare și descrescătoare.
- Funcție pentru salvarea elementelor într-o listă simplu înlănțuită (deep copy).
- Funcție pentru interschimbarea a două elemente din listă pe baza pozițiilor.

---

## 7. HashTable
- Crearea unei tabele de dispersie pentru stocarea clădirilor din București (clustere pe baza anului construirii).
- Funcție pentru afișarea clădirilor dintr-un anumit an.
- Funcție pentru ștergerea unei clădiri pe baza ID-ului și anului construirii.
- Funcție pentru ștergerea unei clădiri doar pe baza ID-ului.
- Observarea diferenței dintre cele două funcții de ștergere.
- Funcție pentru salvarea într-un vector a clădirilor dintr-un anumit an (deep copy).
- Funcție pentru modificarea anului de construire a unei clădiri (cu actualizarea clusterizării).

---

## 8. Heap
- Implementarea unui sistem pentru gestiunea pacienților la Unitatea de Primiri Urgențe (UPU).
- Structura **Pacient** include un grad de urgență.
- Utilizarea unui **Max-Heap** pentru gestionarea pacienților astfel încât cei mai urgenti să fie preluați cu prioritate.

---

## 9. Arbori binari de căutare (BST)
- Funcție pentru ștergerea unui nod pe baza unui ID, menținând proprietățile arborelui BST.
- Funcție pentru returnarea subarborelui cu înălțimea mai mare.
- Funcție pentru numărarea nodurilor subordonate unui nod.
- Funcție pentru returnarea subarborelui cu mai multe noduri în subordine.

---

## 10. Arbori AVL
- Implementarea unui arbore binar de căutare echilibrat (AVL).
- Verificarea și aplicarea rotațiilor pentru menținerea echilibrului.
- Funcție de căutare a unui nod în arbore pe baza unui ID.
- Funcție pentru salvarea nodurilor într-un vector folosind **preordine, inordine, postordine**.
- Funcție pentru salvarea nodurilor într-o listă simplu înlănțuită (preordine, inordine, postordine).
- Funcție pentru salvarea nodurilor într-o listă dublu înlănțuită (preordine, inordine, postordine).

---

## 11. Stive și cozi
- **Stivă (LIFO):**
  - Pe un **vector**.
  - Pe o **listă simplu înlănțuită**.
  - Pe o **listă dublu înlănțuită**.
- **Coada (FIFO):**
  - Pe un **vector**.
  - Pe o **listă simplu înlănțuită**.
  - Pe o **listă dublu înlănțuită**.

---

## Instrucțiuni de rulare
1. Compilați programul folosind un compilator C (ex: `gcc`).
2. Rulați executabilul generat.
3. Asigurați-vă că fișierele necesare sunt prezente pentru testare.

---

## Autor
- **Nume:** [Numele vostru]
- **Data:** [Data completării]
