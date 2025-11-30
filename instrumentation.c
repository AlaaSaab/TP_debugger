#include <stdio.h>
#include "fap.h"

int fap_compteur=0;
int fap_taille_maximale=0;

fap instrumentation_inserer(fap f, int element, int priorite)
{
    fap_compteur++;
    if (fap_compteur > fap_taille_maximale) {
        fap_taille_maximale = fap_compteur;
        printf("TAILLE MAX FAP : %d\n", fap_compteur);
    }
    return inserer(f, element, priorite);
};

fap instrumentation_extraire(fap f, int *element, int *priorite)
{
    fap_compteur--;
    return extraire(f, element, priorite);
}
