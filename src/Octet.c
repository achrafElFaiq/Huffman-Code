#include<stdio.h>
#include<stdbool.h>
#include <string.h>
#include "Octet.h"
#include "CodeBinaire.h"
#include <stdlib.h>
#include "ArbreHuffman.h"
static int positionDeDebut=0;     
static bool actuelEstPlein;
static Octet bitRestant;
static int indicePlusImportantDeBitRestant=8;

Octet O_obtenirBitRestants() {
    return bitRestant;
}

int O_obtenirIndicePlusImportantDeBitRestant() {
    return indicePlusImportantDeBitRestant;
}

void O_incrementPositionDeDebut() {
    positionDeDebut++;
}

int O_obtenirPositionDeDebut() {
    return positionDeDebut;
}

Octet O_creerOctet() {
    Octet result;
    positionDeDebut = 0;
    actuelEstPlein = false;
    for (size_t i = 0; i < 8; ++i) {
        result.bits[i] = BITA0;
    }
    return result;
}

void O_fixerBit(Octet* octet, int position, Bit valeur) {
    if (position < 8) {
        octet->bits[position] = valeur;
    } 
    else {
        fprintf(stderr, "Erreur : Position hors limites.\n");
    }
}

bool O_actuelEstPlein() {
    return actuelEstPlein;
}

Bit O_iemeBit(Octet octet, int i) {
    return octet.bits[i];
}

void O_decaler(Octet *octet) {
    for(int i = 0 ;i < 7;i++) {
        octet->bits[i] = octet->bits[i+1];
    }
    octet->bits[7] = BITA0;
}

char* O_bitsAStr(const Octet* octet) {
    char* str = malloc(9 * sizeof(char));
    for (int i = 0; i < 8; ++i) {
        str[i] = (octet->bits[i] == BITA0) ? '0' : '1';
    }
    str[8] = '\0';
    return str;
}

Octet O_strABits(const char* chaine) {
    Octet octet = O_creerOctet();
    
    int longueurChaine = strlen(chaine);
    for (int i = 0; i < longueurChaine; ++i) {
        octet.bits[i] = (chaine[i] == '0') ? BITA0 : BITA1;
        O_incrementPositionDeDebut();
    }
    return octet;
}

Octet O_encoder(Octet octet, CodeBinaire cb) {
    Bit bit;
    if (indicePlusImportantDeBitRestant <= 7 && !actuelEstPlein) {
        for (int i = indicePlusImportantDeBitRestant ;i < 8;i++) {     
            bit = O_iemeBit(bitRestant, i);
            O_fixerBit(&octet, positionDeDebut, bit);
            positionDeDebut++;
            O_fixerBit(&bitRestant, indicePlusImportantDeBitRestant, BITA0);
            indicePlusImportantDeBitRestant++;  
        }
    }
    for (int i = 0;i < cb.taille;i++) {
        Bit bit = CB_obtenirIemeBit(cb, i);
        if(!actuelEstPlein ) {
            O_fixerBit(&octet, positionDeDebut, bit);
            positionDeDebut++;
        }
        else {
            O_decaler(&bitRestant);
            O_fixerBit(&bitRestant, 7, bit);
            indicePlusImportantDeBitRestant--;
        }
        if(positionDeDebut > 7) {
            actuelEstPlein =true;
        }
    }
    if(positionDeDebut > 7) {
        actuelEstPlein =true;
    }
    return octet;
}

bool O_estVide(const Octet* octet) {
    for (size_t i = 0; i < 8; ++i) {
        if (octet->bits[i] != BITA0) {
            return false;
        }
    }
    return true;
}

Octet O_inverser(Octet o) {
    Octet result = O_creerOctet();
    for(int i = 0;i < 8;i++){
        O_fixerBit(&result, i, O_iemeBit(o, 7-i));
    }
    return result;
}



