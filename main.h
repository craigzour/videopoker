/*##########################################
#                                          #
#                  main.h                  #
#                                          #
#               par Cl�ment                # 
#                                          #
# Ce fichier est l'assemblage des fonctions#
# provenant de tous les moteurs du jeu.    #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

//Cette fonction g�re toute l'interface de la partie jeu
void afficherjeu();

//Cette fonction g�re toute l'interface de la partie options
void afficheroption();

//Cette fonction g�re toute l'interface de la partie aide
void afficheraide();

//Cette fonction g�re toute l'interface de la partie �num�ration des combinaisons
void affichercombi();

//Cette fonction g�re toute l'interface de la partie affichage du r�sultat
void afficherresultat(int action);

//Cette fonction g�re toute l'interface de la partie affichage des cartes
void affichagealeatoire(int alea);

//Cette fonction permet de savoir si l'option activation des sons du jeu est activ�
int checksonoption();

//Cette fonction permet de savoir qu'elle musique a �t� choisi par l'utilisateur
int checkmusiquechoisi();
