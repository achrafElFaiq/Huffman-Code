#include <stdio.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "ArbreHuffman.h" 
#include "Statistiques.h" 

void test_creation_arbreHuffman() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    CU_ASSERT_EQUAL(AH_obtenirPonderation(*arbre), 5);
    CU_ASSERT_PTR_NULL(AH_obtenirFilsDroit(arbre));
    CU_ASSERT_PTR_NULL(AH_obtenirFilsGauche(arbre));
}

void test_obtenirOccurences() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    int occurences = AH_obtenirPonderation(*arbre);
    CU_ASSERT_EQUAL(occurences, S_obtenirPonderation(stat));
}

void test_fusionner() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre1 = AH_arbreDeHuffman(stat);
    Statistiques stat2 = S_statistique('E', 2);
    ArbreHuffman* arbre2 = AH_arbreDeHuffman(stat2);
    ArbreHuffman* arbreF = AH_fusionner(arbre1,arbre2);
    CU_ASSERT_EQUAL(AH_obtenirPonderation(*arbreF), S_obtenirPonderation(arbre1->statistiques)+S_obtenirPonderation(arbre2->statistiques)); 
    CU_ASSERT_EQUAL(AH_obtenirFilsDroit(arbreF), arbre1);
    CU_ASSERT_EQUAL(AH_obtenirFilsGauche(arbreF), arbre2);
}

void test_fixerFilsGauche_et_obtenirFilsGauche() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    Statistiques statFils = S_statistique('T', 6);
    ArbreHuffman* filsGauche = AH_arbreDeHuffman(statFils);
    AH_fixerFilsGauche(arbre, filsGauche);
    ArbreHuffman* obtenu = AH_obtenirFilsGauche(arbre);
    CU_ASSERT_PTR_EQUAL(obtenu, filsGauche);
}

void test_fixerFilsDroit_et_obtenirFilsDroit() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    Statistiques statFils = S_statistique('T', 6);
    ArbreHuffman* filsDroit = AH_arbreDeHuffman(statFils);
    AH_fixerFilsDroit(arbre, filsDroit);
    ArbreHuffman* obtenu = AH_obtenirFilsDroit(arbre);
    CU_ASSERT_PTR_EQUAL(obtenu, filsDroit);
}

void test_estVide() {
    Statistiques stat;
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    CU_ASSERT_PTR_NULL(AH_obtenirFilsGauche(arbre));
}

void test_estFeuille() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    CU_ASSERT_TRUE(AH_estFeuille(*arbre));
}

void test_estPresent_caractere_present_a_la_racine() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    char caractere = 'A';

    CU_ASSERT_TRUE(AH_estPresent(arbre, caractere)); 
}

void test_estPresent_caractere_present_sous_arbre_gauche() {
    Statistiques stat = S_statistique('C', 7);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    Statistiques statFils = S_statistique('A', 5);
    ArbreHuffman* arbreFils = AH_arbreDeHuffman(statFils);
    AH_fixerFilsGauche(arbre,arbreFils);
    CU_ASSERT_TRUE(AH_estPresent(arbre, 'A'));
}

void test_estPresent_caractere_present_sous_arbre_droit() {
    Statistiques stat = S_statistique('C', 7);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    Statistiques statFils = S_statistique('A', 5);
    ArbreHuffman* arbreFils = AH_arbreDeHuffman(statFils);
    char caractere = 'A';
    AH_fixerFilsDroit(arbre,arbreFils);
    CU_ASSERT_TRUE(AH_estPresent(arbre, caractere));
}

void test_estPresent_caractere_absent() {
    Statistiques stat = S_statistique('A', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    char caractere = 'B';
    
    CU_ASSERT_FALSE(AH_estPresent(arbre, caractere)); 
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Tests ArbreHuffman", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "Test création ArbreHuffman", test_creation_arbreHuffman))
        || (NULL == CU_add_test(pSuite, "Test obtenirOccurences", test_obtenirOccurences))
        || (NULL == CU_add_test(pSuite, "Test fusionner", test_fusionner))
        || (NULL == CU_add_test(pSuite, "Test fixerFilsGauche et obtenirFilsGauche", test_fixerFilsGauche_et_obtenirFilsGauche))
        || (NULL == CU_add_test(pSuite, "Test fixerFilsDroit et obtenirFilsDroit", test_fixerFilsDroit_et_obtenirFilsDroit))
        || (NULL == CU_add_test(pSuite, "Test estVide", test_estVide))
        || (NULL == CU_add_test(pSuite, "Test estFeuille", test_estFeuille))
        || (NULL == CU_add_test(pSuite, "Test caractère présent à la racine", test_estPresent_caractere_present_a_la_racine))
        || (NULL == CU_add_test(pSuite, "Test caractère présent sous arbre gauche", test_estPresent_caractere_present_sous_arbre_gauche))
        || (NULL == CU_add_test(pSuite, "Test caractère présent sous arbre droit", test_estPresent_caractere_present_sous_arbre_droit))
        || (NULL == CU_add_test(pSuite, "Test caractère absent", test_estPresent_caractere_absent))) {
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
