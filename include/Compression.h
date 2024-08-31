/**
 * \file Compression.h
 * \brief Implantation de l'analyse Descendante Compression pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */
#ifndef  __COMPRESSION__
#define __COMPRESSION__

#include <stdbool.h>
#include <stdio.h>
#include "ArbreHuffman.h"
#include "FileDePriorite.h"
#include "Statistiques.h"
#include "TableDeCodage.h"


/**
 * void COMP_ecrireBit(FILE *fichier, char bit)
 * \brief Fonction qui permet d'écrire des bits dans un fichier
 * \param fichier : fichier à remplir
 * \param bit : la valeur du bit
 */
void COMP_ecrireBit(FILE *fichier, char bit);

/**
 * void COMP_ecrireBitsDansFichier(FILE *fichier, const char *bits) 
 * \brief Fonction qui permet d'écrire des bits (en chaîne de caractères) dans un fichier
 * \param fichier : fichier à remplir
 * \param bit chaîne de caractères avec les bits que l'on veut écrire
 */
void COMP_ecrireBitsDansFichier(FILE *fichier, const char *bits) ;

/**
 * FILE* COMP_initFichier(const char* nomFichier)
 * \brief Fonction qui permet d'initialiser l'ouverture du fichier
 * \param nomFichier : nom du fichier à remplir
 * \return FILE
 */
FILE* COMP_initFichier(const char* nomFichier);

/**
 * void COMP_CreerArbreEtEnfiler(Statistiques stat,FileDePriorite* fp)
 * \brief Fonction qui permet d'initialiser l'arbre d'huffman et de l'enfiler dans une file de priorité
 * \param stat : la statistique à mettre dans l'arbre
 * \param fp : la file de priorité
 */
void COMP_CreerArbreEtEnfiler(Statistiques stat,FileDePriorite* fp);

/**
 * ArbreHuffman COMP_FusionnerArbreFDP(FileDePriorite fp)
 * \brief Fonction qui permet de fusionner les arbres dans la file afin d'obtenir l'arbre final
 * \param fp : la file de priorité
 * \return ArbreHuffman
 */
ArbreHuffman COMP_FusionnerArbreFDP(FileDePriorite fp);

/**
 * \fn COMP_compresser(char nomFichier[]);
 * \brief Fonction qui permet de créer un fichier compressé à partir d'un fichier donné
 * \param nomFichier : fichier à compresser
 * \return FILE
 */
FILE* COMP_compresser(const char* nomFichier);



#endif
