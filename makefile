SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
SRCTESTDIR=src/tests
TESTDIR=tests
CC = gcc
AR = ar
CFLAGS=-Wall -pedantic -g -std=gnu99  -I$(INCLUDEDIR)  
LDFLAGS=-lm -lcurses -lcunit
EXEC=CompDecomp
DOCUMENTATION=./doc
LATEX_FILE = ../rapport/Rapport.tex
RAPPORT=../rapport/Rapport.aux ../rapport/Rapport.log ../rapport/Rapport.out ../rapport/Rapport.pdf ../rapport/Rapport.toc
DOC ?=
all :  $(BINDIR)/$(EXEC)

tests: $(SRCTESTDIR)/testArbreHuffman.o $(SRCTESTDIR)/testCodeBinaire.o $(SRCTESTDIR)/testFileDePriorite.o $(SRCTESTDIR)/testOctet.o $(SRCTESTDIR)/testStatistiques.o $(SRCTESTDIR)/testTableDeCodage.o
	$(CC) -o $(TESTDIR)/testArbreHuffman $(SRCTESTDIR)/testArbreHuffman.o $(SRCDIR)/ArbreHuffman.o $(SRCDIR)/Statistiques.o $(LDFLAGS)
	$(CC) -o $(TESTDIR)/testCodeBinaire $(SRCTESTDIR)/testCodeBinaire.o  $(SRCDIR)/CodeBinaire.o $(SRCDIR)/Statistiques.o $(SRCDIR)/ArbreHuffman.o $(LDFLAGS)
	$(CC) -o $(TESTDIR)/testFileDePriorite $(SRCTESTDIR)/testFileDePriorite.o $(SRCDIR)/FileDePriorite.o $(SRCDIR)/Statistiques.o $(SRCDIR)/ArbreHuffman.o $(LDFLAGS)
	$(CC) -o $(TESTDIR)/testOctet $(SRCTESTDIR)/testOctet.o $(SRCDIR)/Octet.o $(SRCDIR)/CodeBinaire.o $(SRCDIR)/ArbreHuffman.o $(SRCDIR)/Statistiques.o $(LDFLAGS)
	$(CC) -o $(TESTDIR)/testStatistiques $(SRCTESTDIR)/testStatistiques.o  $(SRCDIR)/Statistiques.o $(LDFLAGS)
	$(CC) -o $(TESTDIR)/testTableDeCodage $(SRCTESTDIR)/testTableDeCodage.o $(SRCDIR)/TableDeCodage.o $(SRCDIR)/CodeBinaire.o $(SRCDIR)/Statistiques.o $(SRCDIR)/ArbreHuffman.o $(LDFLAGS)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(SRCDIR)/ArbreHuffman.o $(SRCDIR)/CodeBinaire.o $(SRCDIR)/Compression.o $(SRCDIR)/Decompression.o $(SRCDIR)/FileDePriorite.o $(SRCDIR)/Octet.o $(SRCDIR)/Statistiques.o $(SRCDIR)/TableDeCodage.o
	$(CC)  -o $@ $^ $(LDFLAGS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
$(SRCTESTDIR)/%.o : $(SRCTESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

rapport :
	pdflatex -output-directory=../rapport $(LATEX_FILE)

doc : Doxyfile
	doxygen $<
	
clean :
	rm -rf $(BINDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(SRCDIR)/*.o
	rm -rf $(SRCTESTDIR)/*.o
	rm -rf $(TESTDIR)/*
	if [ "$(DOC)" != "" ]; then rm -rf $(DOCUMENTATION); fi
	rm $(RAPPORT)