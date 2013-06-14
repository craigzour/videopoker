/*##########################################
#                                          #
#               gfx_moteur.h               #
#                                          #
#  JALON 1                    par Timoth�e # 
#                                          #
# Ce fichier regroupe toutes les fonctions #
# du moteur graphique.                     #
#                                          #
#        (PROTOTYPES DES FONCTIONS)        #
##########################################*/

#ifndef MOTEUR
#define MOTEUR

#include <SDL/SDL.h>

#define QUIT SDL_QUIT
#define M_MOUSE SDL_MOUSEMOTION
#define CLICK SDL_MOUSEBUTTONDOWN

SDL_Surface *screen;

SDL_Event event;

SDL_Rect positionDoubleFleche;


// couche basse
int engine_init();
  // Initialise le moteur

int load_all_img();
  // Charge toutes les images, à faire avant d'en afficher une

void load_img(int objet, char *str, int x, int y, int trans);
  // Charge une image en particulier, fonction à utiliser dans load_all_img et nul part ailleurs
void change_img(int objet, char* strmodify);
void blit_img(int objet, int hover);
  // indique au programme que l'image va être placé, attention, ne pas oublier flip() pour l'afficher

void flip();
  // Rafraichit l'écran

int* get_state(int objet);
  // permet de récuperer les infos d'une image

void set_state(int objet, int x, int y);
  // permet de modifier la position d'une image

void set_hover_img(int objet, char* str);
  // indique l'image à placer en hover

//couche systeme
void engine_error(char *str);
  // Indique l'erreur dans le flux stderr, arrête le programme

void engine_warning(char *str);
  // Indique l'erreur mais ne quitte pas le programme

void free_all_memory();
  // Libère la mémoire à la fin 

//couche interface
void show_animation();
  // Affiche l'animation de départ, fonction bloquante
void show_menu();
  // Affiche le menu
//couche interaction
void wait_event();
  // Attend un evenement et renvoie l'event dans SDL_Event *event

int who_is_clicked(int x, int y);
  // Retourne l'id de l'objet cliqué

int is_clickable(int x, int y);
  // Booleen, indique si un objet est cliquable ou non

int is_on(int object, int x, int y);
  // Indique si la souris est sur l'objet

void apply_hover(int x, int y, int min, int max, int exep);
  // fonction automatique qui gere les hover sur les images

//couche texte
void text_init();
  // Initalise le texte

void load_text(int objet, char* str, int x, int y, int r, int g, int b, int fontchoix);
  // charge un objet, il faut indiquer le texte, la position, et pour la couleur, utiliser les defines NOIR et BLANC (a completer)

void load_all_texts();
  // fonction où tous les textes doivent être chargés

void show_text(int objet);
  // Indique au programme qu'une image est sur le point d'etre placé ne pas oublier flip() pour l'afficher
void modify_text(int objet, char* strmodify, int r, int g, int b, int fontchoix);
void changecolor_text(int objet, int r, int g, int b);
void changeposition_text(int objet, int x, int y);
void curseurchargement();
void curseurplacement(int x, int y);
#endif
