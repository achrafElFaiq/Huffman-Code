#include<stdio.h>
#include "TableDeCodage.h"
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>

TableDeCodage* TDC_obtenirTableDeCodage() {
    TableDeCodage* table = malloc(sizeof(TableDeCodage));
    if (table != NULL) {
        table->ligne = NULL;
    }
    return table;
}

CodeBinaire* TDC_obtenirCode(TableDeCodage tab, char c) {
    Ligne* actuel = tab.ligne;
    while (actuel != NULL) {
        if (actuel->c == c) {
            return &actuel->code;
        }
        actuel = actuel->listeSuivante;
    }
    return NULL;
}

void TDC_ajouter(TableDeCodage *tab, char c, CodeBinaire *code) {
    Ligne* nouvelleLigne = malloc(sizeof(Ligne));
    if (nouvelleLigne != NULL) {
        nouvelleLigne->code = *code;
        nouvelleLigne->c = c;
        nouvelleLigne->listeSuivante = tab->ligne;
        tab->ligne = nouvelleLigne;
    }
}

int TDC_estPresent(TableDeCodage tab, char car) {
    TableDeCodage temp;
    if (TDC_estVide(tab)){
        return 0;
    }
    if ( tab.ligne->c == car) {
        return 1;
    }
    else {
        temp.ligne = tab.ligne->listeSuivante;
        return TDC_estPresent(temp, car);
    }
}

bool TDC_estVide(TableDeCodage tab) {
    return tab.ligne == NULL;
}
