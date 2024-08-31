#include<stdio.h>
#include "Statistiques.h"

Statistiques S_statistique(char c, int n) {
    Statistiques res;
    res.caractere = c;
    res.ponderation = n ;
    return res;
}

int S_obtenirPonderation(Statistiques stat) {
    return stat.ponderation;
}

char S_obtenirCaractere(Statistiques stat) {
    return stat.caractere;
}
