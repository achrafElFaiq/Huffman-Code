#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "CodeBinaire.h"
#include <stdlib.h>

// Fonctions de configuration et de nettoyage pour CUnit
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

// Tests pour CB_estVide
void test_CB_estVide(void) {
    CodeBinaire code1 = CB_creerCodeBinaire(4);
    CU_ASSERT_FALSE(CB_estVide(code1));
    CodeBinaire code2 = CB_creerCodeBinaire(8);
    CU_ASSERT_FALSE(CB_estVide(code2));
    CB_libererCodeBinaire(&code1);
    CB_libererCodeBinaire(&code2);
}

// Tests pour CB_creerCodeBinaire
void test_CB_creerCodeBinaire(void) {
    CodeBinaire code = CB_creerCodeBinaire(4);
    CU_ASSERT_EQUAL(code.taille, 4);
    for (size_t i = 0; i < code.taille; ++i) {
        CU_ASSERT_EQUAL(code.bits[i], BITA0);
    }
    CB_libererCodeBinaire(&code);
}

// Tests pour CB_remplirCodeBinaire
void test_CB_remplirCodeBinaire(void) {
    CodeBinaire code;
    code.taille = 4;
    code.bits = malloc(4 * sizeof(Bit));
    const char *bits =  "1101";
    CB_remplirCodeBinaire(&code, bits);
    for (int i = 0; i < code.taille; ++i) {
        if (bits[i] == '0') {
            CU_ASSERT_EQUAL(code.bits[i], BITA0);
        } 
        else if (bits[i] == '1') {
            CU_ASSERT_EQUAL(code.bits[i], BITA1);
        }
    }
    CB_libererCodeBinaire(&code);
}


// Tests pour CB_obtenirIemeBit
void test_CB_obtenirIemeBit(void) {
    CodeBinaire code = CB_creerCodeBinaire(4);

    for (size_t i = 0; i < code.taille; ++i) {
        CU_ASSERT_EQUAL(CB_obtenirIemeBit(code, i), BITA0);
    }
    CB_libererCodeBinaire(&code);
}

// Tests pour CB_concatener
void test_CB_concatener(void) {
    CodeBinaire code1 = CB_creerCodeBinaire(2);
    CodeBinaire code2 = CB_creerCodeBinaire(3);
    CodeBinaire resultat = CB_concatener(&code1, &code2);
    CU_ASSERT_EQUAL(resultat.taille, code1.taille + code2.taille);
    for (size_t i = 0; i < code1.taille; ++i) {
        CU_ASSERT_EQUAL(resultat.bits[i], BITA0);
    }
    for (size_t i = 0; i < code2.taille; ++i) {
        CU_ASSERT_EQUAL(resultat.bits[code1.taille + i], BITA0);
    }
    CB_libererCodeBinaire(&code1);
    CB_libererCodeBinaire(&code2);
    CB_libererCodeBinaire(&resultat);
}

// Tests pour CB_codeBinaireAStr
void test_CB_codeBinaireAStr(void) {
    CodeBinaire code = CB_creerCodeBinaire(3);
    CU_ASSERT_STRING_EQUAL(CB_codeBinaireAStr(&code), "000");
    CB_remplirCodeBinaire(&code, "101");
    CU_ASSERT_STRING_EQUAL(CB_codeBinaireAStr(&code), "101");
    CB_libererCodeBinaire(&code);
}

void test_CB_CbFromAH() {
    Statistiques stat = S_statistique('X', 5);
    ArbreHuffman* arbre = AH_arbreDeHuffman(stat);
    Statistiques statA = S_statistique('A', 3);
    ArbreHuffman* arbreA = AH_arbreDeHuffman(statA);
    Statistiques statB = S_statistique('B', 3);
    ArbreHuffman* arbreB = AH_arbreDeHuffman(statB);
    Statistiques statC = S_statistique('C', 3);
    ArbreHuffman* arbreC = AH_arbreDeHuffman(statC);
    Statistiques statD = S_statistique('D', 4);
    ArbreHuffman* arbreD = AH_arbreDeHuffman(statD);
    Statistiques statE = S_statistique('E', 5);
    ArbreHuffman* arbreE = AH_arbreDeHuffman(statE);
    Statistiques statF = S_statistique('F', 3);
    ArbreHuffman* arbreF = AH_arbreDeHuffman(statF);
    AH_fixerFilsGauche(arbre, arbreA);
    AH_fixerFilsDroit(arbre, arbreB);
    AH_fixerFilsGauche(arbreA , arbreC);
    AH_fixerFilsDroit(arbreA, arbreD);
    AH_fixerFilsGauche(arbreB , arbreE);
    AH_fixerFilsDroit(arbreB, arbreF);
    CodeBinaire cb = CB_CbDeAH(arbre, 'E');
    CU_ASSERT_STRING_EQUAL(CB_codeBinaireAStr(&cb), "10");
}

int main() {
    // Initialisation de CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    // Ajout des suites de tests
    CU_pSuite suite_CB = CU_add_suite("Suite CodeBinaire", init_suite, clean_suite);
    CU_add_test(suite_CB, "Test CB_estVide", test_CB_estVide);
    CU_add_test(suite_CB, "Test CB_creerCodeBinaire", test_CB_creerCodeBinaire);
    CU_add_test(suite_CB, "Test CB_remplirCodeBinaire", test_CB_remplirCodeBinaire);
    CU_add_test(suite_CB, "Test CB_obtenirIemeBit", test_CB_obtenirIemeBit);
    CU_add_test(suite_CB, "Test CB_concatener", test_CB_concatener);
    CU_add_test(suite_CB, "Test CB_codeBinaireAStr", test_CB_codeBinaireAStr);
    CU_add_test(suite_CB, "Test CB_CbFromAH", test_CB_CbFromAH);
    // Exécution des tests
    CU_basic_run_tests();
    // Nettoyage de CUnit
    CU_cleanup_registry();
    return CU_get_error();
}
