#include "Octet.h"
#include "FileDePriorite.h"
#include <stdio.h>
#include <stdlib.h>
#include "CodeBinaire.h"
#include "Statistiques.h"
#include "ArbreHuffman.h"
#include "FileDePriorite.h"
#include "TableDeCodage.h"
#include "Compression.h"
#include <string.h>

void COMP_ecrireBit(FILE *fichier, char bit) {
    static unsigned char octet = 0;
    static int bitsEcrits = 0;
    octet |= (bit - '0') << (7 - bitsEcrits);
    bitsEcrits++;
    if (bitsEcrits == 8) {
        fwrite(&octet, sizeof(unsigned char), 1, fichier);
        octet = 0;
        bitsEcrits = 0;
    }
}

void COMP_ecrireBitsDansFichier(FILE *fichier, const char *bits) {
    size_t longueur = strlen(bits);
    for (size_t i = 0; i < longueur; i++) {
        COMP_ecrireBit(fichier, bits[i]);
    }
}

FILE* COMP_initFichier(const char* nomFichier) {
    FILE* file = fopen(nomFichier,"r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    return file;
}

void COMP_CreerArbreEtEnfiler(Statistiques stat,FileDePriorite* fp) {
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    FDP_enfiler(fp,arbre);
}

ArbreHuffman COMP_FusionnerArbreFDP(FileDePriorite fp){
    while(fp.longueur != 1){
        ArbreHuffman arbre1 = FDP_obtenirElement(fp, fp.longueur);
        ArbreHuffman arbre2 = FDP_obtenirElement(fp, fp.longueur - 1);
        FDP_defiler(&fp);
        FDP_defiler(&fp);
        ArbreHuffman* arbreFusionne1 = AH_fusionner(&arbre1,&arbre2);
        ArbreHuffman* copy = AH_copierArbreHuffman(arbreFusionne1);
        FDP_enfiler(&fp, copy);
    }
    return FDP_obtenirElement(fp,0);
}

FILE* COMP_compresser(const char* nomFichier) {
    FILE* file = COMP_initFichier(nomFichier);
    FileDePriorite fp = FDP_fileDePriorite();
    const char *nomFichierComp = "compressedFile.huff";
    FILE *compressedFile = fopen(nomFichierComp, "wb");
    if (compressedFile == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s en écriture.\n", nomFichierComp);
    }
    int occurrences[256] = {0};
    int caracteresSansRepetition[256] = {0};
    int nbCaracteresSansRepetition = 0;
    int nbCaracAvecRepetition = 0;
    int caractere;
    while ((caractere = fgetc(file)) != EOF) {
        nbCaracAvecRepetition++;
        occurrences[caractere]++;
        if (occurrences[caractere] == 1) {
            caracteresSansRepetition[nbCaracteresSansRepetition++] = caractere;
        }
    }
    nbCaracAvecRepetition--;
    fwrite(&nbCaracAvecRepetition, sizeof(int), 1, compressedFile);
    for (int i = 0; i < 256; i++) {
        Statistiques stat = S_statistique(caracteresSansRepetition[i],occurrences[caracteresSansRepetition[i]]);
        char car = caracteresSansRepetition[i];
        int ent = occurrences[caracteresSansRepetition[i]];
        fwrite(&car, sizeof(char), 1, compressedFile);
        fwrite(&ent, sizeof(int), 1, compressedFile);
        if(ent != 0) {
            COMP_CreerArbreEtEnfiler(stat, &fp);
        }
    }
    ArbreHuffman ArbreFinal = COMP_FusionnerArbreFDP(fp);
    TableDeCodage* tableDeCodageFinale = TDC_obtenirTableDeCodage();
    for (int i = 0 ; i < nbCaracteresSansRepetition;i++) {
        char c = caracteresSansRepetition[i];
        CodeBinaire cb = CB_CbDeAH(&ArbreFinal, c);
        TDC_ajouter(tableDeCodageFinale, c, &cb);
    }
    fseek(file, 0, SEEK_SET);
    char car;
    while ((car = fgetc(file)) != EOF) {
        CodeBinaire* code = TDC_obtenirCode(*tableDeCodageFinale, car);
        char* bitsInstr = CB_codeBinaireAStr(code);
        COMP_ecrireBitsDansFichier(compressedFile, bitsInstr);
    }
    fclose(file);   
    return compressedFile;
}



