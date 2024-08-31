#include "TableDeCodage.h"
#include <stdio.h>
#include <CUnit/Basic.h>
#include "ArbreHuffman.h"
#include "Statistiques.h"

void test_obtenirTableDeCodage(void) {
    TableDeCodage* table = TDC_obtenirTableDeCodage();
    CU_ASSERT_PTR_NOT_NULL(table);
    CU_ASSERT_TRUE(TDC_estVide(*table));
}

void test_TDC_obtenirCode(void) {
    TableDeCodage* table = TDC_obtenirTableDeCodage();
    CodeBinaire cb_A = CB_creerCodeBinaire(3);
    CB_remplirCodeBinaire(&cb_A, "001");
    TDC_ajouter(table, 'A', &cb_A);
    CodeBinaire* res_A = TDC_obtenirCode(*table, 'A');
    CU_ASSERT_PTR_NOT_NULL(res_A);
    CU_ASSERT_STRING_EQUAL(CB_codeBinaireAStr(res_A), "001");
    CodeBinaire* res_B = TDC_obtenirCode(*table, 'B');
    CU_ASSERT_PTR_NULL(res_B);
    CB_libererCodeBinaire(&cb_A);
}

void test_TDC_ajouter(void) {
    TableDeCodage* table = TDC_obtenirTableDeCodage();
    CodeBinaire cb_A = CB_creerCodeBinaire(3);
    CB_remplirCodeBinaire(&cb_A, "001");
    TDC_ajouter(table, 'A', &cb_A);
    CU_ASSERT_FALSE(TDC_estVide(*table));
    CodeBinaire* res_A = TDC_obtenirCode(*table, 'A');
    CU_ASSERT_PTR_NOT_NULL(res_A);
    CU_ASSERT_STRING_EQUAL(CB_codeBinaireAStr(res_A), "001");
    CB_libererCodeBinaire(&cb_A);
}

void test_TDC_estPresent(void) {
    TableDeCodage* table = TDC_obtenirTableDeCodage();
    CodeBinaire cb_A = CB_creerCodeBinaire(3);
    CB_remplirCodeBinaire(&cb_A, "001");
    TDC_ajouter(table, 'A', &cb_A);
    CodeBinaire cb_B = CB_creerCodeBinaire(3);
    CB_remplirCodeBinaire(&cb_B, "010");
    TDC_ajouter(table, 'B', &cb_B);
    int present_A = TDC_estPresent(*table, 'A');
    CU_ASSERT_EQUAL(present_A, 1);
    int present_C = TDC_estPresent(*table, 'C');
    CU_ASSERT_EQUAL(present_C, 0);
    CB_libererCodeBinaire(&cb_A);
    CB_libererCodeBinaire(&cb_B);
}

void test_TDC_estVide(void) {
    TableDeCodage* table_vide = TDC_obtenirTableDeCodage();
    CU_ASSERT_TRUE(TDC_estVide(*table_vide));
    TableDeCodage* table_non_vide = TDC_obtenirTableDeCodage();
    CodeBinaire cb_A = CB_creerCodeBinaire(3);
    CB_remplirCodeBinaire(&cb_A, "001");
    TDC_ajouter(table_non_vide, 'A', &cb_A);
    CU_ASSERT_FALSE(TDC_estVide(*table_non_vide));
    CB_libererCodeBinaire(&cb_A);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);
    CU_add_test(suite, "test_obtenirTableDeCodage", test_obtenirTableDeCodage);
    CU_add_test(suite, "test_TDC_obtenirCode", test_TDC_obtenirCode);
    CU_add_test(suite, "test_TDC_ajouter", test_TDC_ajouter);
    CU_add_test(suite, "test_TDC_estPresent", test_TDC_estPresent);
    CU_add_test(suite, "test_TDC_estVide", test_TDC_estVide);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");    CU_cleanup_registry();
    return CU_get_error();
}