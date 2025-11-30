#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

#include "fap.h"   

// global counters
extern int fap_taille_courante;
extern int fap_taille_max;

// prototypes for our wrapped functions
fap instrumentation_inserer(fap f, int element, int priorite);
fap instrumentation_extraire(fap f, int *element, int *priorite);

// Replace calls to inserer/extraire with our wrappers
#define inserer  instrumentation_inserer
#define extraire instrumentation_extraire

#endif
