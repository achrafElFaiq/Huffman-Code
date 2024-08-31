#include<stdio.h>
#include<stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "Statistiques.h"
#include "ArbreHuffman.h"


ArbreHuffman* AH_arbreDeHuffman(Statistiques stat) {
    ArbreHuffman *arbre = malloc(sizeof(ArbreHuffman));
    if (arbre != NULL) {
        arbre->statistiques = stat;
        arbre->filsGauche = NULL;
        arbre->filsDroit = NULL;
    }
    return arbre;
}

void AH_fixerStatistique(ArbreHuffman *arbre,  Statistiques stat) {
    arbre->statistiques=stat;
}

Statistiques AH_obtenirStat(ArbreHuffman arbre) {
    return arbre.statistiques;
}

int AH_obtenirPonderation(ArbreHuffman arbre) {
    return S_obtenirPonderation(AH_obtenirStat(arbre));
}

char AH_obtenirCaractere(ArbreHuffman arbre) {
    return arbre.statistiques.caractere;
}

ArbreHuffman* AH_fusionner(ArbreHuffman* arbre1,  ArbreHuffman* arbre2) {
    Statistiques stat ;
    stat.caractere = '\0';
    stat.ponderation = S_obtenirPonderation(arbre1->statistiques)+S_obtenirPonderation(arbre2->statistiques);
    ArbreHuffman* res = AH_arbreDeHuffman(stat);
    if (AH_obtenirPonderation(*arbre1)<AH_obtenirPonderation(*arbre2)) {
        AH_fixerFilsGauche(res, arbre1);
        AH_fixerFilsDroit(res, arbre2);
    }
    else {
        AH_fixerFilsGauche(res, arbre2);
        AH_fixerFilsDroit(res, arbre1);
    }
    return res;
}


void AH_fixerFilsGauche(ArbreHuffman *arbre,  ArbreHuffman *filsGauche) {
    if (arbre != NULL) {
        arbre->filsGauche = filsGauche;
    }
}

void AH_fixerFilsDroit(ArbreHuffman *arbre,  ArbreHuffman *filsDroit) {
    if (arbre != NULL) {
        arbre->filsDroit = filsDroit;
    }
}

ArbreHuffman* AH_obtenirFilsGauche(ArbreHuffman *arbre) {
    return (arbre != NULL) ? arbre->filsGauche : NULL;
}

ArbreHuffman* AH_obtenirFilsDroit(ArbreHuffman *arbre) {
    return (arbre != NULL) ? arbre->filsDroit : NULL;
}

bool AH_estVide(ArbreHuffman *arbre) {
    return arbre==NULL;
}

bool AH_estFeuille(ArbreHuffman arbre) {
    return (AH_estVide(AH_obtenirFilsGauche(&arbre)) && AH_estVide(AH_obtenirFilsDroit(&arbre)));
}

bool AH_estPresent(ArbreHuffman *arbre, char caractere) {
    if (!AH_estVide(arbre)) {
        if (arbre->statistiques.caractere == caractere) {
            return true;
        }
        else {
            return (AH_estPresent(AH_obtenirFilsDroit(arbre), caractere) || AH_estPresent(AH_obtenirFilsGauche(arbre), caractere));
        }
    }
    return false;
}


ArbreHuffman* AH_copierArbreHuffman(ArbreHuffman* arbre) {
    if (arbre == NULL) {
        return NULL;
    }
    Statistiques stat= S_statistique(AH_obtenirCaractere(*arbre), AH_obtenirPonderation(*arbre));
    ArbreHuffman* nouveauNoeud = AH_arbreDeHuffman(stat);
    nouveauNoeud->filsGauche = AH_copierArbreHuffman(AH_obtenirFilsGauche(arbre));
    nouveauNoeud->filsDroit = AH_copierArbreHuffman(AH_obtenirFilsDroit(arbre));
    return nouveauNoeud;
}

