#include <stdio.h>
#include <stdbool.h>
#include "CodeBinaire.h"
#include <stdlib.h>
#include <string.h>
#define BITA_END '\0'

bool CB_estVide(CodeBinaire cb) {
    int  taille = cb.taille;
    return taille == 0;
}

CodeBinaire CB_creerCodeBinaire(int taille) {
    CodeBinaire code;
    code.bits = malloc(taille * sizeof(Bit));
    code.taille = taille;
    for (size_t i = 0; i < 4; ++i) {
        code.bits[i] = BITA0;
    }
    return code;
}

void CB_remplirCodeBinaire(CodeBinaire* code, const char* chaine) {
    int longueurChaine = strlen(chaine);
    if (longueurChaine != code->taille) {
        fprintf(stderr, "Erreur : La longueur de la chaîne ne correspond pas à la taille du CodeBinaire.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < code->taille; ++i) {
        code->bits[i] = (chaine[i] == '0') ? BITA0 : BITA1;
    }
}

void CB_libererCodeBinaire(CodeBinaire* code) {
    free(code->bits);
    code->taille = 0;
}

Bit CB_obtenirIemeBit(CodeBinaire code, int i) {
    if (i < code.taille) {
        return code.bits[i];
    } 
    else {
        fprintf(stderr, "Erreur : Indice hors limites.\n");
        exit(EXIT_FAILURE);
    }
}

CodeBinaire CB_concatener(const CodeBinaire* code1, const CodeBinaire* code2) {
    CodeBinaire resultat;
    resultat.taille = code1->taille + code2->taille;
    resultat.bits = malloc(resultat.taille * sizeof(Bit));
    for (size_t i = 0; i < code1->taille; ++i) {
        resultat.bits[i] = code1->bits[i];
    }
    for (size_t i = 0; i < code2->taille; ++i) {
        resultat.bits[code1->taille + i] = code2->bits[i];
    }
    return resultat;
}

char* CB_codeBinaireAStr(const CodeBinaire* code) {
    if (code == NULL || code->bits == NULL || code->taille < 0) {
        return NULL;
    }
    char* str = malloc((code->taille + 1) * sizeof(char));  
    if (str == NULL) {
        return NULL;
    }
    for (int i = 0; i < code->taille; ++i) {
        str[i] = (code->bits[i] == BITA0) ? '0' : '1';
    }
    str[code->taille] = '\0'; 
    return str;
}


CodeBinaire CB_CbDeAH(ArbreHuffman *a, char car) {
    char* result = CB_obtenirCodeBinaire(a, car);
    int taille = strlen(result);
    CodeBinaire CB_result = CB_creerCodeBinaire(taille);
    CB_remplirCodeBinaire(&CB_result, result);
    return CB_result;
}

char* CB_obtenirCodeBinaire(ArbreHuffman *a, char car) {
    if (!AH_estVide(a)) {
        if (AH_estFeuille(*a)) {
            return strdup("0");
        } 
        else {
            return obtenirCodeBinaireR(a, car);
        }
    }
    return NULL;
}

char* obtenirCodeBinaireR(ArbreHuffman *a, char car) {
    if (!AH_estVide(a)) {
        if (AH_estFeuille(*a)) {
            return strdup("");
        }
        if (AH_estPresent(AH_obtenirFilsGauche(a), car)) {
            a = AH_obtenirFilsGauche(a);
            char* resultatGauche = obtenirCodeBinaireR(a, car);
            if (resultatGauche != NULL) {
                char* resultat = malloc(strlen("0") + strlen(resultatGauche) + 1);
                if (resultat != NULL) {
                    strcpy(resultat, "0");
                    strcat(resultat, resultatGauche);
                }
                free(resultatGauche);
                return resultat;
            }
        } 
        else {
            a = AH_obtenirFilsDroit(a);
            char* resultatGauche = obtenirCodeBinaireR(a, car);
            if (resultatGauche != NULL) {
                char* resultat = malloc(strlen("1") + strlen(resultatGauche) + 1);
                if (resultat != NULL) {
                    strcpy(resultat, "1");
                    strcat(resultat, resultatGauche);
                }
                free(resultatGauche);
                return resultat;
            }
        }
    }
    return NULL;
}


