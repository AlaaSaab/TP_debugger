#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    long int decal, i;
    char *chaine;

    if (argc != 3) {
        fprintf(stderr,
                "Ce programme attend deux arguments : le décalage et la chaine à décaler (en majuscules)\n");
        exit(1);
    }

    decal = (long int) argv[1];
    decal = decal % 26;
    chaine = strdup(argv[2]);

    for (i = 0; chaine[i] != '\0'; i++) {
        char code = chaine[i];
        if ((code >= 'A') && (code <= 'Z')) {
            code = code + decal;
            chaine[i] = code;
        }
    }

    printf("Chaine codée : %s\n", chaine);
    return 0;
}
