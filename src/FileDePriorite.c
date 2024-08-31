#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "FileDePriorite.h"
#include "ArbreHuffman.h"

bool FDP_estVide(FileDePriorite *fp) {
    return fp->longueur == 0;
}

FileDePriorite FDP_fileDePriorite() {
    FileDePriorite file;
    file.debut = NULL;
        file.longueur = 0;
    return file;
}

void FDP_enfiler(FileDePriorite *file, ArbreHuffman* arbre) {
    Noeud* noeud = FDP_creerNoeud(arbre);
    if (FDP_estVide(file)) {  
        file->debut = noeud;
        noeud->suivant = NULL;
        file->longueur++;
    }
    else {
        int positionDinsertion = FDP_trouverIndicePourInsere(arbre, file);
        if (positionDinsertion == 0) {
            noeud->suivant = file->debut;
            file->debut = noeud;
        } 
        else {
            Noeud *tmp = file->debut;
            for (int i = 0; i < positionDinsertion - 1; i++) {
                tmp = tmp->suivant;
            }
            noeud->suivant = tmp->suivant;
            tmp->suivant = noeud;
        }
        file->longueur++;
    }
}

Noeud* FDP_creerNoeud(ArbreHuffman* arbre) {
    Noeud* noeud = malloc(sizeof(Noeud));
    noeud->arbre = *arbre;
    noeud->suivant = NULL;
    return noeud;
}

int FDP_trouverIndicePourInsere(ArbreHuffman* arbre,FileDePriorite* file) {
    Noeud *tmp = file->debut;
    int ponderationArbre = AH_obtenirPonderation(*arbre);
    int resultat = 0;
    while (tmp != NULL && AH_obtenirPonderation(tmp->arbre) > ponderationArbre) {
        tmp = tmp->suivant;
        resultat++;
    }
    return resultat;
}

void FDP_defiler(FileDePriorite *file) {
        if (!FDP_estVide(file)) {
        Noeud *noeudActuel = file->debut;
        Noeud *noeudPrecedent = NULL;
        while (noeudActuel->suivant != NULL) {
            noeudPrecedent = noeudActuel;
            noeudActuel = noeudActuel->suivant;
        }
        if (noeudPrecedent != NULL) {
            noeudPrecedent->suivant = NULL;
        } 
        else {
            file->debut = NULL;
        }
        free(noeudActuel);
        file->longueur--;
    }
}

ArbreHuffman FDP_obtenirElement(FileDePriorite file, int i) {
    Noeud* temp;
    temp = file.debut;
    for (int j = 1; j < i; j++) {
         temp = temp->suivant;
     }
    return temp->arbre;
} 
