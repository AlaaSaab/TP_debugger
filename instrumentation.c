#include <stdio.h>
#include "fap.h"

// remove macros so we can call the real functions
#undef inserer
#undef extraire

// now declare the REAL functions
fap inserer(fap f, int element, int priorite);
fap extraire(fap f, int *element, int *priorite);

int fap_taille_courante = 0;
int fap_taille_max = 0;

fap instrumentation_inserer(fap f, int element, int priorite) {
    f = inserer(f, element, priorite);  // now calls REAL function

    fap_taille_courante++;
    if (fap_taille_courante > fap_taille_max) {
        fap_taille_max = fap_taille_courante;
        printf("[Instrumentation] Nouvelle taille max: %d\n", fap_taille_max);
    }
    return f;
}

fap instrumentation_extraire(fap f, int *element, int *priorite) {
    fap old = f;
    f = extraire(f, element, priorite); // REAL extraction

    if (f != old) {
        fap_taille_courante--;
    }
    return f;
}
