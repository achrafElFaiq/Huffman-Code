/**
 * \file FileDePriorite.h
 * \brief Implantation du TAD FileDePriorite pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */

#ifndef  __FILEDEPRIORITE__
#define __FILEDEPRIORITE__
#include <stdbool.h>
#include "ArbreHuffman.h"


/**
 * \brief Le type FileDePriorite est un type qui permet de faire une file d'arbre d'Huffman pour les trier
 *
 */
typedef struct Noeud {
    ArbreHuffman arbre;     /**< L'arbre d'Huffman à la position actuel de la file*/
    struct Noeud* suivant;  /**< La structure qui permet d'acceder à la partie suivante de la file*/
} Noeud;

typedef struct {
    Noeud* debut; /**< Début de la file*/
    int longueur; /**< Taille de la file */
} FileDePriorite;


/**
 * \fn void FDP_nouvelleFile(FileDePriorite* file)
 * \brief Fonction qui fusionne les deux arbres les plus prioritaires d'une file
 *
 * \param file : file sur laquelle on applique
 */
void FDP_nouvelleFile(FileDePriorite* file);

/**
 * \fn void FDP_defiler(FileDePriorite *fp)
 * \brief Fonction qui va défiler une file
 *
 * \param fp : file que l'on va defiler
 */
void FDP_defiler(FileDePriorite *fp);

/**
 * \fn ArbreHuffman FDP_obtenirElement(FileDePriorite fp, int i)
 * \brief Fonction qui va permettre d'obtenir l'ieme element d'une file
 *
 * \param fp : la file
 * \param i : la position de l'element que l'on souhaite obtenir
 * \return ArbreHuffman
 */
ArbreHuffman FDP_obtenirElement(FileDePriorite fp, int i);

/**
 * \fn bool FDP_estVide(FileDePriorite *fp)
 * \brief Fonction qui va permettre de verifier si une file est vide ou non
 *
 * \param fp : la file
 * \return bool
 */
bool FDP_estVide(FileDePriorite *fp);


/**
 * \fn FileDePriorite FDP_fileDePriorite()
 * \brief Permet de creer et initialiser une file
 *
 * \return FileDePriorite
 */
FileDePriorite FDP_fileDePriorite();

/**
 * \fn void FDP_enfiler(FileDePriorite *file,ArbreHuffman* arbre)
 * \brief Fonction qui enfile en prenant en consideration l'ordre
 *
 * \param file : file où on enfile
 * \param arbre : l'arbre à enfiler
 */
void FDP_enfiler(FileDePriorite *file,ArbreHuffman* arbre);


/**
 * \fn Noeud* FDP_createNoeud(ArbreHuffman* arbreOfLCA);
 * \brief Crée un noeud qui contient un arbre et un pointeur vers un autre
 * \param arbreOfLCA : Crée un noeud dans la file, en fixant son champ arbre
 * \return Noeud*
 */
Noeud* FDP_creerNoeud(ArbreHuffman* arbre);

/**
 * \fn void FDP_afficherFileDEPriorite(FileDePriorite* file);
 * \brief Affiche la file pour avoir une vision plus pratique et graphique
 * \param file : file à afficher
 *
 */
void FDP_afficherFileDEPriorite(FileDePriorite* file);


/**
 * \fn int FDP_trouverIndicePourInsere(ArbreHuffman* arbre,FileDePriorite* file);
 * \brief Permet de trouver l'indice du dernier élement plus grand que la ponderation de l'arbre qu'on veut insérer 
 * \param arbre : arbre à insérer
 * \param file : file à parcourir
 * \return int
 */
int FDP_trouverIndicePourInsere(ArbreHuffman* arbre,FileDePriorite* file);
#endif
