/*##########################################
#                                          #
#             sound_moteur.h               #
#                                          #
#  JALON 2                    par Aurélien # 
#                                          #
# Ce fichier regroupe toutes les fonctions #
# du moteur audio.   .                     #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

//Cette fonction permet de charger tous sons ou toutes musique du jeu
void loadmusique ();

//Cette fonction permet de démmarer la lecture de la musique d'ambiance
void musiquedefond();

//Cette fonction permet de lancer un son simple
void jouer (int continuer);

//Cette fonction permet de modifier le volume de la musique d'ambiance du moment
void modifiervolume(int volume);

//Cette fonction permet d'arrêter la musique d'ambiance
void coupermusique();

//Cette fonction permet de changer de musique d'ambiance
void modifiermusique();

//Cette fonction permet de libérer tous sons ou toutes musique chargées au lancement du moteur audio
void sound_close ();
