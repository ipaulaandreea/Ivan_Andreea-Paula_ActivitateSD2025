#ifndef PARTICIPANT_H_INCLUDED
#define PARTICIPANT_H_INCLUDED

//1.1 Se consideră prima literă din numele vostru și prima literă din prenumele vostru. Se va construi un articol care să conțină aceste două litere.
//Paula Ivan -> P si I
//Articolul trebuie să aibă logică.
//Articolul trebuie să fie un substantiv.
//Trebuie să aibă cel puțin trei atribute, dintre care unul alocat dinamic.
typedef struct StucturaParticipant {
    int id;
    char* rol;
    int nrCursuri;
    float* preturiCursuri;
} Participant;

Participant initializare(int id, const char* rol, int nrCursuri, float* preturiCursuri);
void afisareParticipant(Participant p);

#endif
