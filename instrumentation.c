#include <stdio.h>
#include "fap.h"

// global variables
int fap_taille_courante = 0;
int fap_taille_max = 0;

// We must call the REAL functions, so declare them:
fap inserer(fap f, int element, int priorite);
fap extraire(fap f, int *element, int *priorite);

fap instrumentation_inserer(fap f, int element, int priorite) {
    // Call the REAL insertion
    f = inserer(f, element, priorite);

    // Update size
    fap_taille_courante++;

    // Update max
    if (fap_taille_courante > fap_taille_max) {
        fap_taille_max = fap_taille_courante;
        printf("[Instrumentation] Nouvelle taille max: %d\n", fap_taille_max);
    }

    return f;
}

fap instrumentation_extraire(fap f, int *element, int *priorite) {
    // Call the real extraction
    fap ancien = f;
    f = extraire(f, element, priorite);

    // If extraction actually removed an element:
    if (f != ancien) {
        fap_taille_courante--;
    }

    return f;
}
