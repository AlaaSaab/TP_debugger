#include <stdio.h>
#include "fap.h"

// DO NOT include instrumentation.h here to avoid macro recursion
// Declare the REAL functions with a different approach
// We'll use function pointers to ensure we call the real functions

// Forward declarations of the real functions (from fap_bug.c)
// These are the actual implementations, not the macros
static fap (*real_inserer)(fap f, int element, int priorite) = NULL;
static fap (*real_extraire)(fap f, int *element, int *priorite) = NULL;

// Initialize function pointers - these will point to the real functions
// We need to get the addresses at link time, so we'll use a different approach
// Instead, we'll declare the real functions with a different name pattern

// Actually, the best approach is to ensure we never include instrumentation.h
// in this file, and call the functions directly by their declared names
// Since this file doesn't include instrumentation.h, the macros aren't active here

// Declare the real functions (these are the actual implementations from fap_bug.c)
extern fap inserer(fap f, int element, int priorite);
extern fap extraire(fap f, int *element, int *priorite);

int fap_taille_courante = 0;
int fap_taille_max = 0;

fap instrumentation_inserer(fap f, int element, int priorite) {
    // Call the real function directly - macros are not active in this file
    // because we don't include instrumentation.h
    f = inserer(f, element, priorite);

    fap_taille_courante++;
    if (fap_taille_courante > fap_taille_max) {
        fap_taille_max = fap_taille_courante;
        printf("[Instrumentation] Nouvelle taille max: %d\n", fap_taille_max);
    }
    return f;
}

fap instrumentation_extraire(fap f, int *element, int *priorite) {
    fap old = f;
    // Call the real function directly - macros are not active in this file
    f = extraire(f, element, priorite);

    if (f != old) {
        fap_taille_courante--;
    }
    return f;
}
