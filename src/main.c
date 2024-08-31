#include "Octet.h"
#include "./Compression.h"
#include "FileDePriorite.h"
#include "Octet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CodeBinaire.h"
#include "Statistiques.h"
#include "ArbreHuffman.h"
#include "FileDePriorite.h"
#include "TableDeCodage.h"
#include "Decompression.h"

int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <-c ou -d> <fichier original>\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1],"-c")==0) {
        COMP_compresser(argv[2]);
        return 0;
    }
    else {
        if (strcmp(argv[1],"-d")==0) {
        DECOMP_decompresser(argv[2]);
        return 0;
        }
        else {
            fprintf(stderr, "Option non reconnue : %s\n", argv[1]);
            return 1;
            }
    }
}

