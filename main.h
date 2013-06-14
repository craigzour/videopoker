/*##########################################
#                                          #
#                  main.h                  #
#                                          #
#               par Clément                # 
#                                          #
# Ce fichier est l'assemblage des fonctions#
# provenant de tous les moteurs du jeu.    #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

//Cette fonction gère toute l'interface de la partie jeu
void afficherjeu();

//Cette fonction gère toute l'interface de la partie options
void afficheroption();

//Cette fonction gère toute l'interface de la partie aide
void afficheraide();

//Cette fonction gère toute l'interface de la partie énumération des combinaisons
void affichercombi();

//Cette fonction gère toute l'interface de la partie affichage du résultat
void afficherresultat(int action);

//Cette fonction gère toute l'interface de la partie affichage des cartes
void affichagealeatoire(int alea);

//Cette fonction permet de savoir si l'option activation des sons du jeu est activé
int checksonoption();

//Cette fonction permet de savoir qu'elle musique a été choisi par l'utilisateur
int checkmusiquechoisi();
