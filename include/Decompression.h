/**
 * \file Decompression.h
 * \brief Implantation de l'analyse Descendante Decompression pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */
#ifndef  __DECOMPRESSION__
#define __DECOMPRESSION__

#include <stdio.h>
#include <stdbool.h>
#include "ArbreHuffman.h"
#include "FileDePriorite.h"
#include "Statistiques.h"

/**
 * \fn DECOMP_lireBit(FILE *fichier)
 * \brief Fonction qui permet de lire un bit d'un fichier binaire
 *
 * \param fp: une file de priorite
 * \return un bit
 */
int DECOMP_lireBit(FILE *fichier);

/**
 * \fn DECOMP_fileFromFILE(FileDePriorite fp,char caracter,int ponderation)
 * \brief Fonction qui permet d'obtenir la file de priorité à partir des statistiques du fichier compressé
 *
 * \param fp: une file de priorite
 * \param caracter : un caractere
 * \param ponderation: une ponderation
 * \return FileDePriorite
 */

FileDePriorite DECOMP_obtenirFileFichier(FileDePriorite fp,char caracter,int ponderation);



/**
 * \fn DECOMP_decompresser(char nomFichierHuffman[])
 * \brief Fonction qui permet de décompresser un fichier compressé
 * \param nomFichier : fichier à décompresser
 * \return FILE
 */
FILE* DECOMP_decompresser(const char* fileName);


/**
 * \fn DECOMP_creerArbreHuffman(Statistiques stats)
 * \brief Fonction qui crée un arbre à partir de statistiques
 *
 * \param stat : statistiques de l'arbre créé
 * \return ArbreHuffman
 */
ArbreHuffman DECOMP_arbrePrincipal(FileDePriorite fp);





#endif
