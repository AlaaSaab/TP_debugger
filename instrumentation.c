#include <stdio.h>
#include "fap.h"

// CRITICAL: Do NOT include instrumentation.h here!
// This file must call the REAL functions from fap_bug.c, not the instrumented wrappers

// Explicitly undefine any macros that might interfere (in case they're defined elsewhere)
#ifdef inserer
#undef inserer
#endif
#ifdef extraire
#undef extraire
#endif

// Forward declare the real functions from fap_bug.c
// Since this file doesn't include instrumentation.h, these will resolve to the real functions
fap inserer(fap f, int element, int priorite);
fap extraire(fap f, int *element, int *priorite);

int fap_taille_courante = 0;
int fap_taille_max = 0;

fap instrumentation_inserer(fap f, int element, int priorite) {
    // Direct call to real inserer - macros are NOT active in this file
    f = inserer(f, element, priorite);

    fap_taille_courante++;
    if (fap_taille_courante > fap_taille_max) {
        fap_taille_max = fap_taille_courante;
        printf("[Instrumentation] Nouvelle taille max: %d\n", fap_taille_max);
    }
    return f;
}

fap instrumentation_extraire(fap f, int *element, int *priorite) {
    // Only decrement if fap is not empty
    int was_empty = (f == NULL);
    fap old = f;
    
    // Direct call to real extraire - macros are NOT active in this file
    f = extraire(f, element, priorite);

    // Decrement counter only if extraction actually happened
    // (old was not NULL means fap had elements, and f != old means extraction occurred)
    if (!was_empty && old != NULL && f != old) {
        fap_taille_courante--;
    }
    return f;
}
