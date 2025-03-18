+ACM- Task-uri suplimentare

+ACMAIw- 1. Structura +Ahk-i func+Ahs-ii
Se consider+AQM- prima liter+AQM- din numele vostru +Ahk-i prima liter+AQM- din prenumele vostru. Se va construi un articol care s+AQM- con+Ahs-in+AQM- aceste dou+AQM- litere.

+ACoAKg-Exemplu:+ACoAKg-  
Alin Zamfiroiu +IZI- A +Ahk-i Z.  
+ACoAKg-Structura:+ACoAKg-  
+AGAAYABg-c
struct Magazin +AHs-
    int cod+ADs-
    char+ACo- denumire+ADs-
    int nrProduse+ADs-
    float +ACo-preturi+ADs-
+AH0AOw-
+AGAAYABg-
- Articolul trebuie s+AQM- aib+AQM- logic+AQM-.
- Articolul trebuie s+AQM- fie un substantiv.
- Trebuie s+AQM- aib+AQM- cel pu+Ahs-in trei atribute, dintre care unul alocat dinamic.
- Func+Ahs-ii necesare:
  - Func+Ahs-ie pentru citirea unui articol de la tastatur+AQM-.
  - Func+Ahs-ie care calculeaz+AQM- o valoare (ex: medie, sum+AQM-, maxim, minim).
  - Func+Ahs-ie care modific+AQM- un atribut al articolului.
  - Func+Ahs-ie pentru afi+Ahk-area unui articol.

---

+ACMAIw- 2. Vectori
- Crearea unui vector alocat dinamic cu cel pu+Ahs-in 5 obiecte de tipul structurii definite.
- Func+Ahs-ie pentru copierea obiectelor care +AO4-ndeplinesc o condi+Ahs-ie +AO4-ntr-un nou vector.
- Func+Ahs-ie pentru mutarea obiectelor care +AO4-ndeplinesc o alt+AQM- condi+Ahs-ie +AO4-ntr-un nou vector.
- Func+Ahs-ie pentru concatenarea a doi vectori.
- Func+Ahs-ie pentru afi+Ahk-area unui vector de obiecte.
- Apelarea tuturor func+Ahs-iilor +AO4-n +AGA-main()+AGA-.

---

+ACMAIw- 3. Fi+Ahk-iere
- Crearea unui fi+Ahk-ier cu cel pu+Ahs-in 10 obiecte.
- Func+Ahs-ie pentru citirea obiectelor din fi+Ahk-ier +Ahk-i salvarea +AO4-ntr-un vector.
- Func+Ahs-ie pentru salvarea unui obiect +AO4-ntr-un fi+Ahk-ier text.
- Func+Ahs-ie pentru salvarea unui vector de obiecte +AO4-ntr-un fi+Ahk-ier text.

---

+ACMAIw- 4. Matrice
- Citirea obiectelor dintr-un fi+Ahk-ier +Ahk-i salvarea +AO4-ntr-un vector.
- Copierea elementelor +AO4-ntr-o matrice alocat+AQM- dinamic, aplic+AOI-nd un criteriu de grupare pe linii.
- Func+Ahs-ie pentru sortarea liniilor matricei dup+AQM- num+AQM-rul de elemente.
- Func+Ahs-ie pentru afi+Ahk-area elementelor din matrice.

---

+ACMAIw- 5. Liste simplu +AO4-nl+AQM-n+Ahs-uite
- Func+Ahs-ie pentru +Ahk-tergerea unui nod de pe o pozi+Ahs-ie dat+AQM-.
- Func+Ahs-ie pentru inserarea elementelor +AO4-n ordine cresc+AQM-toare dup+AQM- un atribut.
- Func+Ahs-ie pentru salvarea +AO4-ntr-un vector a elementelor care +AO4-ndeplinesc o condi+Ahs-ie (deep copy).
- Func+Ahs-ie pentru interschimbarea a dou+AQM- elemente +AO4-n list+AQM- pe baza pozi+Ahs-iilor.

---

+ACMAIw- 6. Liste dublu +AO4-nl+AQM-n+Ahs-uite
- Func+Ahs-ie pentru +Ahk-tergerea unui nod de pe o pozi+Ahs-ie dat+AQM-.
- Func+Ahs-ie pentru inserarea elementelor +AO4-n ordine cresc+AQM-toare dup+AQM- un atribut.
- Func+Ahs-ii pentru parcurgerea listei +AO4-n ordine cresc+AQM-toare +Ahk-i descresc+AQM-toare.
- Func+Ahs-ie pentru salvarea elementelor +AO4-ntr-o list+AQM- simplu +AO4-nl+AQM-n+Ahs-uit+AQM- (deep copy).
- Func+Ahs-ie pentru interschimbarea a dou+AQM- elemente din list+AQM- pe baza pozi+Ahs-iilor.

---

+ACMAIw- 7. HashTable
- Crearea unei tabele de dispersie pentru stocarea cl+AQM-dirilor din Bucure+Ahk-ti (clustere pe baza anului construirii).
- Func+Ahs-ie pentru afi+Ahk-area cl+AQM-dirilor dintr-un anumit an.
- Func+Ahs-ie pentru +Ahk-tergerea unei cl+AQM-diri pe baza ID-ului +Ahk-i anului construirii.
- Func+Ahs-ie pentru +Ahk-tergerea unei cl+AQM-diri doar pe baza ID-ului.
- Observarea diferen+Ahs-ei dintre cele dou+AQM- func+Ahs-ii de +Ahk-tergere.
- Func+Ahs-ie pentru salvarea +AO4-ntr-un vector a cl+AQM-dirilor dintr-un anumit an (deep copy).
- Func+Ahs-ie pentru modificarea anului de construire a unei cl+AQM-diri (cu actualizarea clusteriz+AQM-rii).

---

+ACMAIw- 8. Heap
- Implementarea unui sistem pentru gestiunea pacien+Ahs-ilor la Unitatea de Primiri Urgen+Ahs-e (UPU).
- Structura +ACoAKg-Pacient+ACoAKg- include un grad de urgen+AhsBAw-.
- Utilizarea unui +ACoAKg-Max-Heap+ACoAKg- pentru gestionarea pacien+Ahs-ilor astfel +AO4-nc+AOI-t cei mai urgenti s+AQM- fie prelua+Ahs-i cu prioritate.

---

+ACMAIw- 9. Arbori binari de c+AQM-utare (BST)
- Func+Ahs-ie pentru +Ahk-tergerea unui nod pe baza unui ID, men+Ahs-in+AOI-nd propriet+AQMCGw-ile arborelui BST.
- Func+Ahs-ie pentru returnarea subarborelui cu +AO4-n+AQM-l+Ahs-imea mai mare.
- Func+Ahs-ie pentru num+AQM-rarea nodurilor subordonate unui nod.
- Func+Ahs-ie pentru returnarea subarborelui cu mai multe noduri +AO4-n subordine.

---

+ACMAIw- 10. Arbori AVL
- Implementarea unui arbore binar de c+AQM-utare echilibrat (AVL).
- Verificarea +Ahk-i aplicarea rota+Ahs-iilor pentru men+Ahs-inerea echilibrului.
- Func+Ahs-ie de c+AQM-utare a unui nod +AO4-n arbore pe baza unui ID.
- Func+Ahs-ie pentru salvarea nodurilor +AO4-ntr-un vector folosind +ACoAKg-preordine, inordine, postordine+ACoAKg-.
- Func+Ahs-ie pentru salvarea nodurilor +AO4-ntr-o list+AQM- simplu +AO4-nl+AQM-n+Ahs-uit+AQM- (preordine, inordine, postordine).
- Func+Ahs-ie pentru salvarea nodurilor +AO4-ntr-o list+AQM- dublu +AO4-nl+AQM-n+Ahs-uit+AQM- (preordine, inordine, postordine).

---

+ACMAIw- 11. Stive +Ahk-i cozi
- +ACoAKg-Stiv+AQM- (LIFO):+ACoAKg-
  - Pe un +ACoAKg-vector+ACoAKg-.
  - Pe o +ACoAKg-list+AQM- simplu +AO4-nl+AQM-n+Ahs-uit+AQMAKgAq-.
  - Pe o +ACoAKg-list+AQM- dublu +AO4-nl+AQM-n+Ahs-uit+AQMAKgAq-.
- +ACoAKg-Coada (FIFO):+ACoAKg-
  - Pe un +ACoAKg-vector+ACoAKg-.
  - Pe o +ACoAKg-list+AQM- simplu +AO4-nl+AQM-n+Ahs-uit+AQMAKgAq-.
  - Pe o +ACoAKg-list+AQM- dublu +AO4-nl+AQM-n+Ahs-uit+AQMAKgAq-.
