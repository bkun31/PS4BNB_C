# @file Makefile
# @author Bilel, Cedric
# @brief 
# @version 0.1
# @date 2021-02-26

# @copyright Domaine public 2021


# Variables générique du Makefile (compilateur)

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra
LDFLAGS =

# Variables architecture du programme (dossier)

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
DOCDIR = doc
TESTDIR = test

#  Variables liste fichiers

SRC = $(wildcard $(SRCDIR)/*.c)
INC = $(wildcard $(INCDIR)/*.h)
OBJ = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))
DOC = $(addprefix $(DOCDIR)/, html latex refman.pdf)

# Exécutable à créer (fichier(s) binaire(s))

BIN = $(addprefix $(BINDIR)/, simuBnb)


ifeq ($(DEBUG), yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

# Au cas où certaines commandes auraient des noms de fichiers existant
.PHONY: clean mrproper remake all doc doc-clean memcheck


# Permet la construction du projet
all: $(BIN)

# Reconstruit le projet proprement
remake: mrproper all


# Pour supprimer tous les fichiers intermédiaires.
# Supprime les fichier objets seulement
clean:
	
	@rm -rf $(OBJ)
	@echo "Cleanup complete!"

# Pour supprimer tous ce qui peut-être regénérer afin de faire une reconstruction propre du projet
# Supprime les fichier objets, binaires et la doc
mrproper: clean doc-clean
	@rm -rf $(BIN)
	@echo "Executable removed!"

# Permet de générer la documentation
doc: $(DOCDIR)/Doxyfile $(SRC) $(INC)
	@doxygen $<
	@cd $(DOCDIR)/latex && $(MAKE)
	@mv $(DOCDIR)/latex/refman.pdf $(DOCDIR)
	@echo  "Updated doc !"

# Supprime la documentation
doc-clean:
	@rm -rf $(DOC)

memcheck: all
	@valgrind -v --show-leak-kinds=all --leak-check=full -track-origins=yes ./$(BIN)

# Créer le dossier binaire si inexistant
$(BINDIR):
	@mkdir -p $@

# Créer le dossier objet si inexistant
$(OBJDIR):
	@mkdir -p $@


# Construit l'éxécutable
$(BIN) : $(BINDIR) $(OBJ)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)
	@echo "Linking complete!"

# Construction des fichiers objet
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

# Dépendences # À COMPLÉTER EN FONCTION DES DÉPÉPENDANCE RÉELLE #

$(OBJDIR)/block.o: $(INCDIR)/block.h $(INCDIR)/transaction.h $(INCDIR)/sha256.h $(INCDIR)/sha256_utils.h

$(OBJDIR)/blockchain.o: $(INCDIR)/blockchain.h $(INCDIR)/block.h

$(OBJDIR)/transaction.o: $(INCDIR)/transaction.h $(INCDIR)/user.h $(INCDIR)/queue.h $(INCDIR)/skiplist.h $(INCDIR)/sha256.h $(INCDIR)/sha256_utils.h

$(OBJDIR)/cheater_block.o: $(INCDIR)/block.h $(INCDIR)/transaction.h

$(OBJDIR)/cheater_transaction.o: $(INCDIR)/blockchain.h $(INCDIR)/block.h

$(OBJDIR)/main.o: $(INC)

$(OBJDIR)/sha256_utils.o: $(INCDIR)/sha256_utils.h

$(OBJDIR)/sha256.o: $(INCDIR)/sha256.h

$(OBJDIR)/bnb.o: $(INCDIR)/bnb.h

$(OBJDIR)/user.o: $(INCDIR)/user.h

$(OBJDIR)/queue.o: $(INCDIR)/queue.h

$(OBJDIR)/skiplist.o: $(INCDIR)/skiplist.h $(INCDIR)/rng.h

$(OBJDIR)/rng.o: $(INCDIR)/rng.h

$(OBJDIR)/config.o: $(INCDIR)/config.h