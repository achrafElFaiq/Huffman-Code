/**
 * \file CodeBinaire.h
 * \brief Implantation du TAD Code Binaire pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */

#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__
#include <stdbool.h>
#include "ArbreHuffman.h"
/**
 * \brief Le type CodeBinaire permet de donner un code en binaire pour chaque caractere present dans le fichier
 *
 */

typedef enum { BITA0, BITA1} Bit;

typedef struct {
    Bit* bits;         /**< Pointeur vers le tableau de bits */
    int taille;     /**< Taille du tableau (nombre de bits) */ 
} CodeBinaire;


/**
 * \fn bool CB_estVide(CodeBinaire cb)
 * \brief Fonction qui permet de savoir si un code est vide ou non
 *
 * \param cb : le code binaire
 * \return bool
 */
bool CB_estVide(CodeBinaire cb);


/**
 * \fn CodeBinaire CB_creerCodeBinaire(int taille)
 * \brief Fonction qui creer un code binaire à partir de sa taille
 *
 * \param taille : le nombre de bits 
 * \return CodeBinaire
 */
CodeBinaire CB_creerCodeBinaire(int taille); 

/**
 * \fn void CB_libererCodeBinaire(CodeBinaire* code)
 * \brief Fonction qui libère un code binaire 
 *
 * \param code : le code à liberer
 */
void CB_libererCodeBinaire(CodeBinaire* code);

/**
 * \fn Bit CB_obtenirIemeBit(CodeBinaire code,int i)
 * \brief Fonction qui permet d'obtenir le ieme bit d'un code binaire
 *
 * \param code : le code
 * \param i : la position du bit à obtenir
 * \return Bit
 */
Bit CB_obtenirIemeBit(CodeBinaire code,int i);

/**
 * \fn CodeBinaire CB_concatener(const CodeBinaire* code1, const CodeBinaire* code2)
 * \brief Fonction qui permet de concatener 2 codes binaires
 *
 * \param code1 : le 1er code
 * \param code2 : la 2nd code
 * \return CodeBinaire
 */
CodeBinaire CB_concatener(const CodeBinaire* code1, const CodeBinaire* code2);

/**
 * \fn char* CB_codeBinaireToStr(const CodeBinaire* code)
 * \brief Fonction qui permet de convertir un code binaire en chaîne de caractères
 *
 * \param code : le code
 * \return char*  (la chaîne de caractère)
 */
char* CB_codeBinaireAStr(const CodeBinaire* code);

/**
 * \fn void CB_remplirCodeBinaire(CodeBinaire* code, const char* chaine)
 * \brief Fonction qui permet de remplir un code binaire avec une chaîne de caractère
 *
 * \param code : le code à remplir
 * \param chaine : la chaine que le veut mettre dans le code binaire
 */
void CB_remplirCodeBinaire(CodeBinaire* code, const char* chaine);

/**
 * \fn CodeBinaire AH_CbFromAH(ArbreHuffman *a, char car)
 * \brief Fonction qui permet de calculer un code binaire à partir d'un arbre d'Huffman et d'un caractere
 *
 * \param a : l' arbre
 * \param car : le caractere dont on veut calculer le code
 * \return CodeBinaire
 */
CodeBinaire CB_CbDeAH(ArbreHuffman *a, char car);

/**
 * \fn char* AH_obtenirCodeBinaire(ArbreHuffman *a, char car)
 * \brief Fonction qui permet de trouver la chaine de caractere qui va être convertie en code binaire par AH_CbFromAH
 * \param a : l'arbre
 * \param car : le caractere dont on veut calculer le code
 * \return char*  (la chaîne de caractère)
 */
char* CB_obtenirCodeBinaire(ArbreHuffman *a, char car);

/**
 * \fn char* obtenirCodeBinaireR(ArbreHuffman *a, char car )
 * \brief Fonction récursive qui va permettre d'avoir le code binaire d'un caractere et qui va être appelé dans AH_obtenirCodeBinaire
 * \param a : l'arbre
 * \param car : le caractere dont on veut calculer le code
 * \return char*  (la chaîne de caractère)
 */
char* obtenirCodeBinaireR(ArbreHuffman *a, char car );

#endif
