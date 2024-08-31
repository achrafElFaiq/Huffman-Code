/**
 * \file TableDeCodage.h
 * \brief Implantation du TAD TableDeCodage pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong
 *
 */

#ifndef __TABLEDECODAGE__
#define __TABLEDECODAGE__


#include "CodeBinaire.h"
#include "ArbreHuffman.h"

/**
 * \brief Le type TableDeCodage permet de faire un tableau avec les caracteres et leur code binaire associé
 */
typedef struct Ligne{
    CodeBinaire code; /**< Le code binaire*/
    char c; /**< Le caractère*/
    struct Ligne* listeSuivante; /**< la combinaison de caractere/code binaire suivante*/
} Ligne;

typedef struct {
    Ligne* ligne; /**< Pointeur vers la structure contenant une ligne du tableau*/
} TableDeCodage;

/**
 * \fn TableDeCodage TDC_obtenirTableDeCodage(ArbreHuffman a)
 * \brief Fonction qui permet d'obtenir une table de codage à partir d'un arbre d'Huffman
 * 
 * \param a : l'arbre dont l'on veut obtenir la table de codage
 * \return TableDeCodage
 */
TableDeCodage* TDC_obtenirTableDeCodage();

/**
 * \fn CodeBinaire TDC_obtenirCode(TableDeCodage tab,char c)
 * \brief Fonction qui permet d'obtenir le code binaire d'un caractere à partir d'une table de codage
 * \param tab : la table de codage
 * \param c : le caractere dont on cherche le code binaire
 * \return CodeBinaire
 */
CodeBinaire* TDC_obtenirCode(TableDeCodage tab,char c);


/**
 * \fn void TDC_ajouter(TableDeCodage *tab,char *c,CodeBinaire *code)
 * \brief Fonction qui permet d'ajouter une ligne (caractere + code binaire) dans la table de codage
 * \param tab : la table de codage
 * \param c : le caractere a ajouter
 * \param code : le code binaire a ajouter
 */
void TDC_ajouter(TableDeCodage *tab,char c,CodeBinaire *code);


/**
 * \fn int TDC_estPresent(TableDeCodage tab,char c)
 * \brief Fonction qui permet de savoir si un caractere est present dans une table de codage
 * \param tab : la table de codage
 * \param c : le caractere que l'on cherche
 * \return int (0 si faux 1 si vrai)
 */
int TDC_estPresent(TableDeCodage tab,char c);

/**
 * \fn bool TDC_estVide(TableDeCodage tab)
 * \brief Fonction qui permet de savoir si une table de codage est vide ou non
 * \param tab : la table de codage
 * \return bool
 */
bool TDC_estVide(TableDeCodage tab);

#endif
