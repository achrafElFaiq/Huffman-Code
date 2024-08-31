#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <CUnit/Basic.h>
#include "FileDePriorite.h"
#include "ArbreHuffman.h"
#include "Statistiques.h"

void test_creation_file() {
    FileDePriorite file;
    file = FDP_fileDePriorite();
    CU_ASSERT_PTR_NULL(file.debut);
    CU_ASSERT_EQUAL(file.longueur,0);
}

void testEnfiler_milieu() {
    FileDePriorite file1; 
    FileDePriorite file2;
    file1 = FDP_fileDePriorite();
    file2 = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat3));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat3));    
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat2));
    for (int i = 1; i <= file1.longueur; i++) {
        ArbreHuffman arbre1 = FDP_obtenirElement(file1, i);
        ArbreHuffman arbre2 = FDP_obtenirElement(file2, i);
        CU_ASSERT_EQUAL(AH_obtenirPonderation(arbre1), AH_obtenirPonderation(arbre2));
        CU_ASSERT_EQUAL(AH_obtenirCaractere(arbre1), AH_obtenirCaractere(arbre2));
    }
    CU_ASSERT_EQUAL(file1.longueur, file2.longueur);
}

void testEnfiler_debut() {
    FileDePriorite file1; 
    FileDePriorite file2;
    file1 = FDP_fileDePriorite();
    file2 = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat3));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat1));    
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat3));
    for (int i = 1; i <= file1.longueur; i++) {
        ArbreHuffman arbre1 = FDP_obtenirElement(file1, i);
        ArbreHuffman arbre2 = FDP_obtenirElement(file2, i);
        CU_ASSERT_EQUAL(AH_obtenirPonderation(arbre1), AH_obtenirPonderation(arbre2));
        CU_ASSERT_EQUAL(AH_obtenirCaractere(arbre1), AH_obtenirCaractere(arbre2));
    }
    CU_ASSERT_EQUAL(file1.longueur, file2.longueur);
}

void testEnfiler_fin() {
   FileDePriorite file1; 
    FileDePriorite file2;
    file1 = FDP_fileDePriorite();
    file2 = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat3));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat3));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat2));    
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat1));
    for (int i = 1; i <= file1.longueur; i++) {
        ArbreHuffman arbre1 = FDP_obtenirElement(file1, i);
        ArbreHuffman arbre2 = FDP_obtenirElement(file2, i);
        CU_ASSERT_EQUAL(AH_obtenirPonderation(arbre1), AH_obtenirPonderation(arbre2));
        CU_ASSERT_EQUAL(AH_obtenirCaractere(arbre1), AH_obtenirCaractere(arbre2));
    }
    CU_ASSERT_EQUAL(file1.longueur, file2.longueur);
}

void testDefiler() {
    FileDePriorite file1; 
    FileDePriorite file2;
    file1 = FDP_fileDePriorite();
    file2 = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file1, AH_arbreDeHuffman(stat3));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file2, AH_arbreDeHuffman(stat3));
    FDP_defiler(&file2);
    for (int i = 1; i <= file1.longueur; i++) {
        ArbreHuffman arbre1 = FDP_obtenirElement(file1, i);
        ArbreHuffman arbre2 = FDP_obtenirElement(file2, i);
        CU_ASSERT_EQUAL(AH_obtenirPonderation(arbre1), AH_obtenirPonderation(arbre2));
        CU_ASSERT_EQUAL(AH_obtenirCaractere(arbre1), AH_obtenirCaractere(arbre2));
    }
    CU_ASSERT_EQUAL(file1.longueur, file2.longueur);
}

void test_obtenirIElement_debut() {
    FileDePriorite file; 
    file = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file, AH_arbreDeHuffman(stat3));
    ArbreHuffman arbre_obtenu = FDP_obtenirElement(file, 1);
    ArbreHuffman arbre_theorique = *AH_arbreDeHuffman(stat3);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsDroit, arbre_theorique.filsDroit);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsGauche, arbre_theorique.filsGauche);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.caractere, arbre_theorique.statistiques.caractere);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.ponderation, arbre_theorique.statistiques.ponderation);
}

void test_obtenirIElement_milieu() {
    FileDePriorite file; 
    file = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file, AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file, AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file, AH_arbreDeHuffman(stat3));
    ArbreHuffman arbre_obtenu = FDP_obtenirElement(file, 2);
    ArbreHuffman arbre_theorique = *AH_arbreDeHuffman(stat2);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsDroit, arbre_theorique.filsDroit);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsGauche, arbre_theorique.filsGauche);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.caractere, arbre_theorique.statistiques.caractere);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.ponderation, arbre_theorique.statistiques.ponderation);
}

void test_obtenirIElement_fin() {
    FileDePriorite file;
    file = FDP_fileDePriorite();
    Statistiques stat1 = S_statistique('a', 3);
    Statistiques stat2 = S_statistique('b', 4);
    Statistiques stat3 = S_statistique('c', 7);
    FDP_enfiler(&file,AH_arbreDeHuffman(stat1));
    FDP_enfiler(&file,AH_arbreDeHuffman(stat2));
    FDP_enfiler(&file,AH_arbreDeHuffman(stat3));
    ArbreHuffman arbre_obtenu = FDP_obtenirElement(file, 3);
    ArbreHuffman arbre_theorique = *AH_arbreDeHuffman(stat1);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsDroit, arbre_theorique.filsDroit);
    CU_ASSERT_PTR_EQUAL(arbre_obtenu.filsGauche, arbre_theorique.filsGauche);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.caractere, arbre_theorique.statistiques.caractere);
    CU_ASSERT_EQUAL(arbre_obtenu.statistiques.ponderation, arbre_theorique.statistiques.ponderation);
}

int main (int argc, char** argv) {
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Tests FileDePriorite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "Test création File", test_creation_file)
        || (NULL == CU_add_test(pSuite, "Test enfiler milieu", testEnfiler_milieu))
        || (NULL == CU_add_test(pSuite, "Test enfiler début", testEnfiler_debut))
        || (NULL == CU_add_test(pSuite, "Test enfiler fin", testEnfiler_fin))
        || (NULL == CU_add_test(pSuite, "Test défiler", testDefiler))
        || (NULL == CU_add_test(pSuite, "Test obtenirElement début", test_obtenirIElement_debut))
        || (NULL == CU_add_test(pSuite, "Test obtenirElement milieu", test_obtenirIElement_milieu))
        || (NULL == CU_add_test(pSuite, "Test obtenirElement fin", test_obtenirIElement_fin)))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    CU_cleanup_registry();
    return CU_get_error();
}
