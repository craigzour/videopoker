/*##########################################
#                                          #
#               fct_jeu.h                  #
#                                          #
#  JALON 3                    par Cl�ment  # 
#                                          #
# Ce fichier regroupe tous les algorithmes #
# utilis� pour le d�roulement des phases   #
# du jeu.                                  #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

//Cette fonction permet de d�finir al�atoirement les cartes utilis� pour un tour de jeu
void distributiondescartes(int action);

//Cette fonction recherche une possible combinaison parmis les 5 cartes finales affich� sur la table
void reconnaissancecombinaison();

//Cette fonction permet de conserver ou non une carte
void selectioncarte(int carte);

//Cette fonction permet d'interagir sur l'argent poss�d� ou la mise engag�e
void changerargent(int action, int somme);

//Cette fonction (utilitaire pour une v�rification de variable) permet de verifier l'argent poss�d� par le joueur
int checkargent();

//Cette fonction (utilitaire pour une v�rification de variables) permet de connaitre les cartes tir�es al�atoirement
int checkcartes(int car);

//Cette fonction permet de d�selectionner toutes les cartes pour un nouveau tour de jeu
void deselection();
