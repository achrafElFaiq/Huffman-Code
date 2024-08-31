#include <stdio.h>
#include <CUnit/Basic.h>
#include "Statistiques.h" 

// Fonction de test pour vérifier la création d'une statistique
void test_creation_statistique() {
    Statistiques stat = S_statistique('A', 5);
    CU_ASSERT_EQUAL(S_obtenirCaractere(stat), 'A');
    CU_ASSERT_EQUAL(S_obtenirPonderation(stat), 5);
}

int main() {
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Tests Statistiques", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Test création Statistique", test_creation_statistique)) {
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
