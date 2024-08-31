/**
 * \file Statistiques.h
 * \brief Implantation du TAD Statistiques pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */

#ifndef __STATISTIQUES__
#define __STATISTIQUES__

/**
 * \brief Le type Statistiques permet de donner le nombre d'occurences d'un caractere dans un fichier
 *
 */

typedef struct {
    char caractere; /**< Le caractère*/
    int ponderation; /**< Son nombre d'occurences*/
}Statistiques;

/**
 * \fn Statistiques S_statistique(char caracter, int ponderation)
 * \brief Fonction qui permet de creer une statistique à partir d'un caractere et de son nombre d'occurences
 * 
 * \param char : le caractère
 * \param int : le nombre d'occurences
 * \return Statistiques
 */
Statistiques S_statistique(char caracter, int ponderation);


/**
 * \fn char S_obtenirCaractere(Statistiques stat)
 * \brief Fonction qui permet d'obtenir un caractere à partir d'une statistique
 * 
 * \param stat : la statistique
 * \return char
 */
char S_obtenirCaractere(Statistiques stat);

/**
 * \fn int S_obtenirPonderation(Statistiques stat)
 * \brief Fonction qui permet d'obtenir la pondération d'un caractere à partir d'une statistique
 * 
 * \param stat : la statistique
 * \return int
 */
int S_obtenirPonderation(Statistiques stat);


#endif
