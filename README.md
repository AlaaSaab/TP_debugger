# 📝 TP Débogage — Compte-Rendu / README

## 🎯 Objectif du TP

Ce TP a pour but de pratiquer différentes techniques de débogage sur un programme manipulant une File à Priorité (FAP) :

- Débogage interactif (gdb / lldb)
- Tests automatisés et fuzzing
- Analyse mémoire (Valgrind)
- Instrumentation (analyse structurelle dynamique)
- Profiling (gprof)

---

## 1️⃣ Compilation pour le débogage

Pour utiliser un débogueur, il faut compiler avec les **symboles de debug** :

```sh
gcc -g fap_bug.c essai_fap.c -o essai_fap
```

Sous macOS, `gdb` est difficile à faire fonctionner → donc **lldb** a été privilégié.

---

## 2️⃣ Débogage avec LLDB (équivalent GDB)

🎯 **But :** trouver le bug principal dans `extraire()` et explorer la pile.

### Commandes essentielles LLDB :

| Action | LLDB |
|--------|-------|
| Lancer avec un breakpoint | `breakpoint set -n extraire` |
| Lancer le programme | `run` |
| Pas-à-pas dans les fonctions | `step` |
| Pas à pas sans entrer | `next` |
| Afficher une variable | `p var` |
| Voir le frame complet | `frame variable` |
| Quitter | `quit` |

### Exemple d’analyse réelle

1. Breakpoint dans `extraire`
2. `next` jusqu’à `courant = f->prochain`
3. Vérification :  
   ```
   p f
   p courant
   ```
4. Résultat :  
   `courant = NULL`, mais le code faisait quand même `free(courant)` → **segfault confirmé**.

---

## 3️⃣ Création d’un jeu de tests aléatoires (fuzzing)

But : provoquer des comportements erratiques dans la FAP.

### Générateur (1000 lignes aléatoires) :

```c
for (int i=0; i<1000; i++){
    if (rand() % 3)  // 2/3 des cas
        printf("i %d %d\n", rand(), rand());
    else
        printf("e\n");
}
printf("q\n");
```

### Exécution :

```sh
./essai | ./essai_fap
```

Ou :

```sh
./essai > test.txt
./essai_fap < test.txt
```

---

## 4️⃣ Tests massifs automatiques (fuzzing amélioré)

```bash
#!/bin/bash
for i in {1..1000}; do
   ./essai > t.txt
   ./essai_fap < t.txt && echo "OK test $i" || {
      echo "CRASH on test $i!"
      exit 1
   }
done
```

Ce script a permis de détecter un crash reproductible.

---

## 5️⃣ Analyse mémoire avec Valgrind (via Docker Linux)

Valgrind ne fonctionne pas correctement sous macOS ARM → utilisation via Docker :

```sh
docker run -it --rm -v "$PWD":/src ubuntu:22.04 bash
apt update
apt install -y gcc make valgrind
```

### Compilation compatible Valgrind (DWARF4)

```sh
gcc -g -gdwarf-4 *.c -o essai_fap
valgrind ./essai_fap < test.txt
```

### Résultats obtenus

- **Invalid read**
- **Double free**
- **776 erreurs**
- Structure chaînée corrompue (cycles, double libération)

Valgrind permet de diagnostiquer :

- lectures interdites  
- double free  
- use-after-free  
- fuites mémoire  

---

## 6️⃣ Instrumentation (mesure dynamique)

🎯 **But : mesurer**  
- la taille actuelle de la FAP  
- la taille maximale atteinte  
- sans modifier le code source existant

### Implémentation

Ajout de :

- `instrumentation_inserer()`
- `instrumentation_extraire()`

Et redéfinition :

```c
#define inserer instrumentation_inserer
#define extraire instrumentation_extraire
```

Grâce au `-include instrumentation.h`, tout le programme utilise automatiquement les fonctions instrumentées.

### Exemple réel :

```
[Instrumentation] Nouvelle taille max : 373
[Instrumentation] Nouvelle taille max : 374
[Instrumentation] Nouvelle taille max : 375
...
```

### Scénario d’utilisation réelle

Pour une structure dynamique dans un vrai système (serveur, ordonnanceur, queue de messages) :

- observer les pics d’activité  
- détecter une surcharge mémoire  
- prévoir une réallocation  
- décider de changer d’implémentation (heap binaire, etc.)

---

## 7️⃣ Profiling avec gprof

### Compilation

```sh
gcc -pg -g *.c -o essai_fap
```

### Exécution

```sh
./essai_fap < test.txt
```

### Analyse

```sh
gprof essai_fap > rapport.txt
```

Le profiler donne :

- temps dans `inserer`
- temps dans `extraire`
- nombre d’appels
- arbre d’appels complet

### Conclusion (exigée dans le TP)

Notre FAP utilise une **liste chaînée triée** :

- `inserer()` = **O(n)** (lent)
- `extraire()` = **O(1)** (rapide)

Pour optimiser :

- utiliser un **tas (heap)**  
- `inserer()` = **O(log n)**  
- `extraire()` = **O(log n)**  

---

## 📌 Résumé final

| Technique | Objectif | Ce que nous avons fait |
|----------|-----------|------------------------|
| LLDB / GDB | Trouver crash | Breakpoints, step, print |
| Fuzzing | Faire sortir les bugs cachés | Génération aléatoire + script |
| Valgrind | Analyse mémoire | Invalid read, double free |
| Instrumentation | Mesure dynamique | Taille/max FAP |
| Profiling (gprof) | Performance | Temps dans inserer/extraire |

