#include<stdio.h>
#include<stdbool.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "Octet.h"
#include "CodeBinaire.h"

void test_creer_Octet() {
    Octet octet = O_creerOctet();
    for (int i = 0; i < 8;i++) {
        CU_ASSERT_EQUAL(O_iemeBit(octet, i), BITA0);
    }  
}

void test_fixer_bit() {
    Octet octet = O_creerOctet();
    O_fixerBit(&octet, 0, BITA1);
    O_fixerBit(&octet, 7, BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octet, 0), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octet, 7), BITA1);
}

void test_encoder() {
    CodeBinaire code = CB_creerCodeBinaire(1);
    CB_remplirCodeBinaire(&code, "1");
    const char* chaineBinaire = "1010";
    Octet octet = O_strABits(chaineBinaire);
    for(int i = 0; i < 7; i++) {
        octet = O_encoder(octet, code);
    }
    CU_ASSERT_EQUAL(strcmp(O_bitsAStr(&octet), "10101111"), 0);
    Octet octetRes = O_obtenirBitRestants();
    CU_ASSERT_EQUAL(strcmp(O_bitsAStr(&octetRes), "00000111"), 0);
}

void test_iemeBit() {
    Octet octet = O_creerOctet();
    O_fixerBit(&octet, 7, BITA1);
    O_fixerBit(&octet, 0, BITA0);
    CU_ASSERT_EQUAL(O_iemeBit(octet, 7), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octet, 0), BITA0);
}

void test_decaler() {
    char* octet = "01011100";
    Octet octetInBits = O_strABits(octet);
    O_decaler(&octetInBits);
    CU_ASSERT_EQUAL(strcmp(O_bitsAStr(&octetInBits), "10111000"), 0);
}

void test_str_to_bits() {
    char* octetInstr = "11110011";
    Octet octetInBits= O_strABits(octetInstr);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 0), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 1), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 2), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 3), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 4), BITA0);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 5), BITA0);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 6), BITA1);
    CU_ASSERT_EQUAL(O_iemeBit(octetInBits, 7), BITA1);
}

void test_bits_to_str() {
    Octet octet = O_creerOctet();
    O_fixerBit(&octet, 0, BITA1);
    O_fixerBit(&octet, 1, BITA1);
    O_fixerBit(&octet, 2, BITA1);
    O_fixerBit(&octet, 3, BITA1);
    O_fixerBit(&octet, 4, BITA1);
    O_fixerBit(&octet, 5, BITA1);
    O_fixerBit(&octet, 6, BITA1);
    O_fixerBit(&octet, 7, BITA1);
    char* octetInstr= O_bitsAStr(&octet);
    CU_ASSERT_EQUAL(strcmp(octetInstr, "11111111"), 0);
}

int main (int argc, char** argv) {
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Tests Octet", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "Test création d'octet", test_creer_Octet))
        || (NULL == CU_add_test(pSuite, "Test fixer bit", test_fixer_bit))
        || (NULL == CU_add_test(pSuite, "Test encoder", test_encoder))
        || (NULL == CU_add_test(pSuite, "Test obtenir ieme bit", test_iemeBit))
        || (NULL == CU_add_test(pSuite, "Test decaler", test_decaler))
        || (NULL == CU_add_test(pSuite, "Test string to bits", test_str_to_bits))
        || (NULL == CU_add_test(pSuite, "Test bits to string", test_bits_to_str))) {
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