#include "Octet.h"
#include <stdio.h>
#include <stdlib.h>
#include "CodeBinaire.h"
#include "Statistiques.h"
#include "ArbreHuffman.h"
#include "FileDePriorite.h"
#include "TableDeCodage.h"
#include "Compression.h"
#define TAILLE_MAX 1000 

FileDePriorite DECOMP_obtenirFileFichier(FileDePriorite fp,char car,int ponderation) {
    Statistiques stat = S_statistique(car, ponderation); 
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    FDP_enfiler(&fp,arbre);
    return fp;
}

int DECOMP_lireBit(FILE *fichier) {
    static unsigned char octet = 0;
    static int bitsLus = 0;
    if (bitsLus == 0) {
        size_t result = fread(&octet, sizeof(unsigned char), 1, fichier);
        if (result == 0) {
            return EOF; 
        }
        bitsLus = 8;
    }
    int bit = (octet >> (bitsLus - 1)) & 1;
    bitsLus--;
    return bit;
}

ArbreHuffman DECOMP_arbrePrincipal(FileDePriorite fp) {
    while(fp.longueur != 1) {
        ArbreHuffman arbre1 = FDP_obtenirElement(fp, fp.longueur);
        ArbreHuffman arbre2 = FDP_obtenirElement(fp, fp.longueur - 1);
        FDP_defiler(&fp);
        FDP_defiler(&fp);
        ArbreHuffman* arbreFusionne = AH_fusionner(&arbre1, &arbre2);
        ArbreHuffman* copie = AH_copierArbreHuffman(arbreFusionne);
        FDP_enfiler(&fp, copie);
    }
    return FDP_obtenirElement(fp, 0);
}

FILE* DECOMP_decompresser(const char* nomFichier) {
    FILE *fichier = fopen(nomFichier, "rb");
    int taille = 1;
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fread(&taille, sizeof(int), 1, fichier);
    char c;
    FileDePriorite fp= FDP_fileDePriorite();
    int i = 0;
    while(i < 256) {
        c = fgetc(fichier);
        int statPonderation;
        fread(&statPonderation, sizeof(int), 1, fichier);
        if(statPonderation!=0) {
            fp = DECOMP_obtenirFileFichier(fp, c, statPonderation);
        }
        i++;
    }
    const char *decompressed = "decompressedFile.txt";
    FILE* decompresssedFile = fopen(decompressed, "w");
    ArbreHuffman arbrePrincipal = DECOMP_arbrePrincipal(fp);
    ArbreHuffman *tmp = &arbrePrincipal;
    int bit;
    while ((bit = DECOMP_lireBit(fichier)) != EOF) {
        if(bit == 0) tmp = tmp->filsGauche;
        else if (bit == 1) tmp  =tmp->filsDroit;   
        if (AH_estFeuille(*tmp)){
            fprintf(decompresssedFile, "%c", AH_obtenirCaractere(*tmp));
            tmp = &arbrePrincipal;
        }
    }
    fclose(fichier);
    return NULL;
}




