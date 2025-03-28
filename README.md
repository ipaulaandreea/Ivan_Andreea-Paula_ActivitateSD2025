# Task-uri suplimentare

## 1. Structura și funcții ✅
1.1. Se consideră prima literă din numele vostru și prima literă din prenumele vostru. Se va construi un articol care să conțină aceste două litere.
- Articolul trebuie să aibă logică.
- Articolul trebuie să fie un substantiv.
- Trebuie să aibă cel puțin trei atribute, dintre care unul alocat dinamic.
- 
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

- Funcții necesare:
  - 1.2. Funcție pentru citirea unui articol de la tastatură.
  - 1.3. Funcție care calculează o valoare (ex: medie, sumă, maxim, minim).
  - 1.4. Funcție care modifică un atribut al articolului.
  - 1.5. Funcție pentru afișarea unui articol.

---

## 2. Vectori ✅
- 2.1. Crearea unui vector alocat dinamic cu cel puțin 5 obiecte de tipul structurii definite.
- 2.2. Funcție pentru copierea obiectelor care îndeplinesc o condiție într-un nou vector.
- 2.3. Funcție pentru mutarea obiectelor care îndeplinesc o altă condiție într-un nou vector.
- 2.4. Funcție pentru concatenarea a doi vectori.
- 2.5. Funcție pentru afișarea unui vector de obiecte.
- Apelarea tuturor funcțiilor în `main()`.

---

## 3. Fișiere ✅
- Crearea unui fișier cu cel puțin 10 obiecte.
- 3.1. Funcție pentru citirea obiectelor din fișier și salvarea într-un vector.
- 3.2. Funcție pentru salvarea unui obiect într-un fișier text.
- 3.3. Funcție pentru salvarea unui vector de obiecte într-un fișier text.

---

## 4. Matrice
- 4.0. Citirea obiectelor dintr-un fișier și salvarea într-un vector.
- 4.1. Functie care sa copieze (deep copy) elementele din vector intr-o matrice alocată
  dinamic. Asezarea in matrice pe linii a obiectelor o faceti dupa un criteriu aplicat unui
  atribut. Astfel veti obține mai multe clustere reprezentate de liniile matricei.
- 4.2. Functie pentru mutarea liniile din matrice, astfel incat acestea sa fie sortate dupa numarul
  de elemente de pe linie
- 4.3. Funcție pentru afișarea elementelor din matrice.

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