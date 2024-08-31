/**
 * \file Octet.h
 * \brief Implantation du TAD Octet pour le Compresseur d'Huffman
 * \author A. El Faïq, T. Barsot, W. Vilayvong, E. Lefeuvre
 *
 */

#ifndef __OCTET__
#define __OCTET__
#include "CodeBinaire.h"


/**
 * \brief Le type Octet est un type qui permet de stocker des codes binaire dans des tableaux de 8 bits
 *
 */
typedef struct {
    Bit bits[8];  /**< Tableau de 8 bits*/
} Octet;


/**
 * \fn Bit O_iemeBit(Octet octet,int i)
 * \brief Fonction qui permet d'obtenir le ieme bit d'un octet
 * \param octet : l'octet
 * \param i : position du bit que l'on recherche
 * \return Bit
 */
Bit O_iemeBit(Octet octet,int i);

/**
 * \fn Octet O_creerOctet()
 * \brief Fonction qui creer un octet
 * \return Octet
 */
Octet O_creerOctet();


/**
 * \fn O_currentisFull();
 * \brief retourne si l'octet courant est plein
 * \return boolean
 */
bool O_currentisFull();


/**
 * \fn Octet O_encoder(Octet octet,CodeBinaire cb)
 * \brief Fonction qui permet de remplir un octet avec un code binaire
 * \param octet : l'octet
 * \param cb : le code binaire que l'on souhaite intégrer
 * \return Octet
 */
Octet O_encoder(Octet octet,CodeBinaire cb);

/**
 * \fn void O_decaler(Octet *octet)
 * \brief Fonction qui va décaler tous les bits vers la gauche
 * \param octet : l'octet
 */
void O_decaler(Octet *octet);

/**
 * \fn void O_fixerBit(Octet* octet, int position, Bit valeur)
 * \brief Fonction qui va fixer l'un des bits d'un octet
 * \param octet : l'octet
 * \param position : la position du bit que l'on veut fixer
 * \param valeur : la valeur du bit 
 */
void O_fixerBit(Octet* octet, int position, Bit valeur);

/**
 * \fn char* O_bitsToStr(const Octet* octet)
 * \brief Fonction qui permet de convertir un octet en chaine de caractère
 * \param octet : l'octet
 * \return char*
 */
char* O_bitsAStr(const Octet* octet);

/**
 * \fn Octet O_strToBits(const char* chaine)
 * \brief Fonction qui permet de convertir une chaine de caractere en Octet
 * \param chaine : la chaine de caractere
 * \return Octet
 */
Octet O_strABits(const char* chaine);

/**
 * \fn bool O_estVide(const Octet* octet)
 * \brief Fonction qui permet de savoir si un octet est vide ou non
 * \param octet : l'octet
 * \return bool
 */
bool O_estVide(const Octet* octet);

/**
 * \fn void O_incrementStartPosition()
 * \brief Fonction qui va augmenter de 1 la position à laquelle l'octet va commencer à etre rempli
 */
void O_incrementStartPosition();

/**
 * \fn int O_obtenirStartPosition()
 * \brief Fonction qui permet d'obtenir la position à laquelle l'octet va commencer à etre rempli
 * \return int
 */
int O_obtenirStartPosition();

/**
 * \fn Octet O_obtenirBitRestants()
 * \brief Fonction qui permet de ressortir les bits qui avaient dépassé lors du remplissage d'un octet afin de les mettre dans un nouvel octet
 * \return Octet
 */
Octet O_obtenirBitRestants();

/**
 * \fn int O_obtenirIndicePlusImportantDeBitRestant()
 * \brief Fonction qui renvoie l'indice le plus important de l'octet bitRestants 
 * \return int
 */
int O_obtenirIndicePlusImportantDeBitRestant();

/**
 * \fn Octet O_inverser(Octet o)
 * \brief Fonction qui inverse un octet
 * \return Octet
 */
Octet O_inverser(Octet o);

#endif
