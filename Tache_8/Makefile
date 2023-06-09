#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geom2d exemple_sequence_point test_contour test_eps test_distance_point_segment main test_simplifications


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul_contour.o : calcul_contour.c calcul_contour.h image.h liste_point.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
test_contour.o : test_contour.c calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

eps.o : eps.c liste_point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplifications.o : simplifications.c liste_point.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplifications"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_eps.o : test_eps.c eps.h calcul_contour.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_distance_point_segment.o : test_distance_point_segment.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_distance_point_segment"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main.o : main.c simplifications.h image.h eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_simplifications.o : test_simplifications.c simplifications.h geom2d.h liste_point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplifications"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

nom_fichiers.o: nom_fichiers.c nom_fichiers.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module nom_fichiers"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables


test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geom2d : test_geom2d.o geom2d.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

exemple_sequence_point : exemple_sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour : test_contour.o calcul_contour.o image.o liste_point.o geom2d.o nom_fichiers.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_eps : test_eps.o eps.o calcul_contour.o image.o liste_point.o geom2d.o nom_fichiers.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_distance_point_segment : test_distance_point_segment.o geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

main : main.o simplifications.o image.o eps.o calcul_contour.o liste_point.o geom2d.o nom_fichiers.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simplifications : test_simplifications.o simplifications.o geom2d.o liste_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


######################################################################
#                              Soutenance                            #
######################################################################

attente_utilisateur= \
	printf "\n\n\033[0;34m*************************************\n*\033[0m Appuyez sur ENTRÉE pour continuer \033[0;34m*\n*************************************\033[0m\n";\
	read line;

commandes= \
	"make clean --no-print-directory"\
	"make --no-print-directory"\
	"./curiosity-test.sh"\
	"./test_generation_terrains 20 25 25 0.5 terrains_alea2.txt"\
	"cat terrains_alea2.txt"\
	": graphiques"\
	"./test_limites_des_programmes.sh"\
	"./activer_desactiver_observateur.sh false true true false"\
	"make --no-print-directory"\
	": test observateur MA"\
	"./activer_desactiver_observateur.sh true false false true"\
	"make --no-print-directory"\
	": test observateur GD"\
	"./activer_desactiver_observateur.sh true false true false"\
	"make --no-print-directory"\
	": suite ?"

soutenance:
	@\
	clear;\
	printf "\n\033[0;34m*************************************\n\
	*\033[0m Appuyez sur ENTRÉE pour commencer \033[0;34m*\
	\n*************************************\033[0m\n";\
	read line;\
	for commande in $(commandes);\
	do  printf "\033[0;34m ==>\033[0m \033[0;33m$$commande\033[0m \n\n" ;\
	$$commande ;\
	$(attente_utilisateur)\
	done;\
	printf "\033[0;34m ************************************************************\033[0m FIN \033[0;34m************************************************************\033[0m"



########################################################
# regles pour "nettoyer" le répertoire
########################################################

clean_executables:
	rm -fR $(EXECUTABLES)

clean_objets:
	rm -fR *.o

clean_eps:
	rm -fR ../Sorties_eps/*

clean_contours:
	rm -fR ../Sorties_contours/*

clean: clean_executables clean_objets clean_eps clean_contours
