/*##########################################
#                                          #
#               fct_jeu.h                  #
#                                          #
#  JALON 3                    par Clément  # 
#                                          #
# Ce fichier regroupe tous les algorithmes #
# utilisé pour le déroulement des phases   #
# du jeu.                                  #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

//Cette fonction permet de définir aléatoirement les cartes utilisé pour un tour de jeu
void distributiondescartes(int action);

//Cette fonction recherche une possible combinaison parmis les 5 cartes finales affiché sur la table
void reconnaissancecombinaison();

//Cette fonction permet de conserver ou non une carte
void selectioncarte(int carte);

//Cette fonction permet d'interagir sur l'argent possédé ou la mise engagée
void changerargent(int action, int somme);

//Cette fonction (utilitaire pour une vérification de variable) permet de verifier l'argent possédé par le joueur
int checkargent();

//Cette fonction (utilitaire pour une vérification de variables) permet de connaitre les cartes tirées aléatoirement
int checkcartes(int car);

//Cette fonction permet de déselectionner toutes les cartes pour un nouveau tour de jeu
void deselection();
