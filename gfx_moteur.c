/*##########################################
#                                          #
#               gfx_moteur.c               #
#                                          #
#  JALON 1                    par Timothée # 
#                                          #
# Ce fichier regroupe toutes les fonctions #
# du moteur graphique.                     #
#                                          #
##########################################*/

#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_ttf.h>

#include "ressources.h"
#include "gfx_moteur.h"
#include "sound_moteur.h"

unsigned const int nbr_img = 112;
unsigned const int nbr_text = 59;

struct img {
	int objet;
	SDL_Surface *surface;
	SDL_Surface *hover;
	SDL_Rect pos;
	int is_clickable;
	int is_menu;
	int is_hover;
	int get_hover;
};

struct img *imgs;

TTF_Font *font = NULL;
TTF_Font *font2 = NULL;

struct text {
	SDL_Surface *surface;
	char* content;
	SDL_Color color;
	SDL_Rect pos;	
};

struct text *texts;
int index_text = 0;

SDL_Surface *curseursurface = NULL;
SDL_Rect curseurposition;

// couche basse
int engine_init();
int load_all_img();
void load_img(int objet, char *str, int x, int y, int trans);
void change_img(int objet, char* strmodify);
void blit_img(int objet, int hover);
void flip();
int* get_state(int objet);
void set_state(int objet, int x, int y);
void set_hover_img(int objet, char* str);
//couche systeme
void engine_error(char *str);
void engine_warning(char *str);
void free_all_memory();
//couche interface
void show_animation();
void show_menu();
//couche interaction
void wait_event();
int who_is_clicked(int x, int y);
int is_clickable(int x, int y);
int is_on(int object, int x, int y);
void apply_hover(int x, int y, int min, int max, int exep);
//couche texte
void text_init();
void load_text(int objet, char* str, int x, int y, int r, int g, int b, int fontchoix);
void load_all_texts();
void show_text(int objet);
void modify_text(int objet, char* strmodify, int r, int g, int b, int fontchoix);
void changecolor_text(int objet, int r, int g, int b);
void changeposition_text(int objet, int x, int y);
void curseurchargement();
void curseurplacement(int x, int y);

	/* ------- Couche basse -------- */
int engine_init() {

	putenv("SDL_VIDEO_WINDOW_POS=center");

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		engine_error("Impossible d'initialiser SDL");
		exit(1);
	}
	atexit(SDL_Quit);

    screen = SDL_SetVideoMode(W_LARGEUR, W_HAUTEUR, W_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
    	engine_error("** Impossible de charger le mode vidéo **");
    }
    
	SDL_WM_SetCaption("VidÃ©o Poker Game", NULL);
	
    SDL_WM_SetIcon(IMG_Load("content/general/logopoker.png"), NULL);

    //SDL_ShowCursor(SDL_DISABLE);
    
	text_init();

	load_all_img();

	return TRUE;
}

int load_all_img() {

	imgs = malloc(nbr_img * sizeof(struct img));
	
	if(imgs == NULL)
		engine_error("Echec allocation memoire");
	
	load_img(FOND, "content/general/fond.png", 0, 0, 255);

	load_img(LOGO_MENU, "content/menu/logomenu.png", ((900-666)/2), 30, 255);
	
	load_img(BOUTON_JOUER, "content/menu/buttonjouer.png", ((900-310)/2), 230, 200);
	set_hover_img(BOUTON_JOUER, "content/menu/buttonjouerhover.png");

    load_img(BOUTON_OPTIONS, "content/menu/buttonoptions.png", ((900-310)/2), 310, 200);
	set_hover_img(BOUTON_OPTIONS, "content/menu/buttonoptionshover.png");
	
	load_img(BOUTON_QUITTER, "content/menu/buttonquitter.png", ((900-310)/2), 390, 200);
	set_hover_img(BOUTON_QUITTER, "content/menu/buttonquitterhover.png");
	
	load_img(BOUTON_AIDE, "content/menu/buttonaide.png", 825, 435, 200);
	set_hover_img(BOUTON_AIDE, "content/menu/buttonaidehover.png");
	
	load_img(BOUTON_MENU, "content/general/buttonmenu.png", 1000, 1000, 255);
	set_hover_img(BOUTON_MENU, "content/general/buttonmenuhover.png");
	
	load_img(BOUTON_CARTES, "content/jeu/buttonpremiertirage.png", 605, 9, 255);
	set_hover_img(BOUTON_CARTES, "content/jeu/buttonpremiertiragehover.png");
	
	load_img(BOUTON_ANNULEMISE, "content/jeu/buttontapis.png", ((900-230)/2), 9, 255);
	set_hover_img(BOUTON_ANNULEMISE, "content/jeu/buttontapishover.png");
	
	load_img(BOUTON_MUSIQUESANS, "content/options/case.png", 385, 82, 255);
	load_img(BOUTON_MUSIQUEFAIBLE, "content/options/case.png", 495, 82, 255);
	load_img(BOUTON_MUSIQUEMOYEN, "content/options/case.png", 615, 82, 255);
	load_img(BOUTON_MUSIQUEFORT, "content/options/case.png", 720, 82, 255);
	load_img(BOUTON_SONSAVEC, "content/options/case.png", 495, 178, 255);
	load_img(BOUTON_SONSSANS, "content/options/case.png", 385, 178, 255);
	load_img(BOUTON_MUSIQUE1, "content/options/case.png", 422, 295, 255);
	load_img(BOUTON_MUSIQUE2, "content/options/case.png", 645, 295, 255);
	
    load_img(BOUTON_MUSIQUESANSCOCHE, "content/options/casecoche.png", 385, 82, 255);
	load_img(BOUTON_MUSIQUEFAIBLECOCHE, "content/options/casecoche.png", 495, 82, 255);
	load_img(BOUTON_MUSIQUEMOYENCOCHE, "content/options/casecoche.png", 615, 82, 255);
	load_img(BOUTON_MUSIQUEFORTCOCHE, "content/options/casecoche.png", 720, 82, 255);	
	load_img(BOUTON_SONSAVECCOCHE, "content/options/casecoche.png", 495, 178, 255);
	load_img(BOUTON_SONSSANSCOCHE, "content/options/casecoche.png", 385, 178, 255);
	load_img(BOUTON_MUSIQUE1COCHE, "content/options/casecoche.png", 422, 295, 255);
	load_img(BOUTON_MUSIQUE2COCHE, "content/options/casecoche.png", 645, 295, 255);

	load_img(GCARTE1, "content/jeu/buttongarder.png", 101, 320, 255);
	set_hover_img(GCARTE1, "content/jeu/buttongarderhover.png");
	load_img(GCARTE2, "content/jeu/buttongarder.png", 252, 320, 255);
	set_hover_img(GCARTE2, "content/jeu/buttongarderhover.png");
	load_img(GCARTE3, "content/jeu/buttongarder.png", 402, 320, 255);
	set_hover_img(GCARTE3, "content/jeu/buttongarderhover.png");
	load_img(GCARTE4, "content/jeu/buttongarder.png", 552, 320, 255);
	set_hover_img(GCARTE4, "content/jeu/buttongarderhover.png");
	load_img(GCARTE5, "content/jeu/buttongarder.png", 703, 320, 255);
	set_hover_img(GCARTE5, "content/jeu/buttongarderhover.png");
	
	load_img(SCARTEO1, "content/jeu/ok.gif", 1000, 1000, 255);
	load_img(SCARTEO2, "content/jeu/ok.gif", 1000, 1000, 255);
	load_img(SCARTEO3, "content/jeu/ok.gif", 1000, 1000, 255);
	load_img(SCARTEO4, "content/jeu/ok.gif", 1000, 1000, 255);
	load_img(SCARTEO5, "content/jeu/ok.gif", 1000, 1000, 255);
	
	load_img(SCARTEN1, "content/jeu/no.gif", 225, 230, 255);
	load_img(SCARTEN2, "content/jeu/no.gif", 335, 230, 255);
	load_img(SCARTEN3, "content/jeu/no.gif", 445, 230, 255);
	load_img(SCARTEN4, "content/jeu/no.gif", 555, 230, 255);
	load_img(SCARTEN5, "content/jeu/no.gif", 665, 230, 255);
	
	load_img(BANDE, "content/jeu/bande.png", 0, 0, 255);
	load_img(BANDER1, "content/aide/bandeaide2.png", 1000, 1000, 255);
	load_img(BANDER2, "content/aide/bandeaide2.png", 1000, 1000, 255);
	load_img(BANDER3, "content/aide/bandeaide2.png", 1000, 1000, 255);
	load_img(BANDER4, "content/aide/bandeaide2.png", 1000, 1000, 255);
	
	load_img(COMBIPAIRE, "content/aide/paire.png", 15, 50, 255);
	load_img(COMBIDOUBLEPAIRE, "content/aide/doublepaire.png", 308, 50, 255);
	load_img(COMBIBRELAN, "content/aide/brelan.png", 602, 50, 255);
	load_img(COMBICARRE, "content/aide/carre.png", 15, 310, 255);
	load_img(COMBICOULEUR, "content/aide/couleur.png", 308, 180, 255);
	load_img(COMBIFULL, "content/aide/full.png", 602, 180, 255);
	load_img(COMBIQUINTE, "content/aide/quinte.png", 15, 180, 255);
	load_img(COMBIQUINTEFLUSH, "content/aide/quinteflush.png", 308, 310, 255);
	load_img(COMBIQUINTEFLUSHROYALE, "content/aide/quinteflushroyale.png", 602, 310, 255);

	load_img(PION1, "content/jeu/pion1.png", 73, 320, 240);
	load_img(PION5, "content/jeu/pion5.png", 202, 320, 255);
	load_img(PION10, "content/jeu/pion10.png", 330, 320, 255);
	load_img(PION20, "content/jeu/pion20.png", 458, 320, 255);
	load_img(PION100, "content/jeu/pion100.png", 586, 320, 255);
	load_img(PION200, "content/jeu/pion200.png", 714, 320, 255);
	
	load_img(DEUXCARREAU, "content/cartes/carreau2.png", 1000, 1000, 255);
	load_img(TROISCARREAU, "content/cartes/carreau3.png", 1000, 1000, 255);
	load_img(QUATRECARREAU, "content/cartes/carreau4.png", 1000, 1000, 255);
	load_img(CINQCARREAU, "content/cartes/carreau5.png", 1000, 1000, 255);
	load_img(SIXCARREAU, "content/cartes/carreau6.png", 1000, 1000, 255);
	load_img(SEPTCARREAU, "content/cartes/carreau7.png", 1000, 1000, 255);
	load_img(HUITCARREAU, "content/cartes/carreau8.png", 1000, 1000, 255);
	load_img(NEUFCARREAU, "content/cartes/carreau9.png", 1000, 1000, 255);
	load_img(DIXCARREAU, "content/cartes/carreau10.png", 1000, 1000, 255);
	load_img(ASCARREAU, "content/cartes/carreauas.png", 1000, 1000, 255);
	load_img(DAMECARREAU, "content/cartes/carreaudame.png", 1000, 1000, 255);
	load_img(ROICARREAU, "content/cartes/carreauroi.png", 1000, 1000, 255);
	load_img(VALETCARREAU, "content/cartes/carreauvalet.png", 1000, 1000, 255);
	load_img(DEUXCOEUR, "content/cartes/coeur2.png", 1000, 1000, 255);
	load_img(TROISCOEUR, "content/cartes/coeur3.png", 1000, 1000, 255);
	load_img(QUATRECOEUR, "content/cartes/coeur4.png", 1000, 1000, 255);
	load_img(CINQCOEUR, "content/cartes/coeur5.png", 1000, 1000, 255);
	load_img(SIXCOEUR, "content/cartes/coeur6.png", 1000, 1000, 255);
	load_img(SEPTCOEUR, "content/cartes/coeur7.png", 1000, 1000, 255);
	load_img(HUITCOEUR, "content/cartes/coeur8.png", 1000, 1000, 255);
	load_img(NEUFCOEUR, "content/cartes/coeur9.png", 1000, 1000, 255);
	load_img(DIXCOEUR, "content/cartes/coeur10.png", 1000, 1000, 255);
	load_img(ASCOEUR, "content/cartes/coeuras.png", 1000, 1000, 255);
	load_img(DAMECOEUR, "content/cartes/coeurdame.png", 1000, 1000, 255);
	load_img(ROICOEUR, "content/cartes/coeurroi.png", 1000, 1000, 255);
	load_img(VALETCOEUR, "content/cartes/coeurvalet.png", 1000, 1000, 255);
	load_img(DEUXPIQUE, "content/cartes/pique2.png", 1000, 1000, 255);
	load_img(TROISPIQUE, "content/cartes/pique3.png", 1000, 1000, 255);
	load_img(QUATREPIQUE, "content/cartes/pique4.png", 1000, 1000, 255);
	load_img(CINQPIQUE, "content/cartes/pique5.png", 1000, 1000, 255);
	load_img(SIXPIQUE, "content/cartes/pique6.png", 1000, 1000, 255);
	load_img(SEPTPIQUE, "content/cartes/pique7.png", 1000, 1000, 255);
	load_img(HUITPIQUE, "content/cartes/pique8.png", 1000, 1000, 255);
	load_img(NEUFPIQUE, "content/cartes/pique9.png", 1000, 1000, 255);
	load_img(DIXPIQUE, "content/cartes/pique10.png", 1000, 1000, 255);
	load_img(ASPIQUE, "content/cartes/piqueas.png", 1000, 1000, 255);
	load_img(DAMEPIQUE, "content/cartes/piquedame.png", 1000, 1000, 255);
	load_img(ROIPIQUE, "content/cartes/piqueroi.png", 1000, 1000, 255);
	load_img(VALETPIQUE, "content/cartes/piquevalet.png", 1000, 1000, 255);
	load_img(DEUXTREFLE, "content/cartes/trefle2.png", 1000, 1000, 255);
	load_img(TROISTREFLE, "content/cartes/trefle3.png", 1000, 1000, 255);
	load_img(QUATRETREFLE, "content/cartes/trefle4.png", 1000, 1000, 255);
	load_img(CINQTREFLE, "content/cartes/trefle5.png", 1000, 1000, 255);
	load_img(SIXTREFLE, "content/cartes/trefle6.png", 1000, 1000, 255);
	load_img(SEPTTREFLE, "content/cartes/trefle7.png", 1000, 1000, 255);
	load_img(HUITTREFLE, "content/cartes/trefle8.png", 1000, 1000, 255);
	load_img(NEUFTREFLE, "content/cartes/trefle9.png", 1000, 1000, 255);
	load_img(DIXTREFLE, "content/cartes/trefle10.png", 1000, 1000, 255);
	load_img(ASTREFLE, "content/cartes/trefleas.png", 1000, 1000, 255);
	load_img(DAMETREFLE, "content/cartes/trefledame.png", 1000, 1000, 255);
	load_img(ROITREFLE, "content/cartes/trefleroi.png", 1000, 1000, 255);
	load_img(VALETTREFLE, "content/cartes/treflevalet.png", 1000, 1000, 255);

	return TRUE;
}

void load_img(int objet, char *str, int x, int y, int trans) {

	SDL_Surface *fond;
	fond = IMG_Load(str);
	SDL_SetAlpha(fond, SDL_SRCALPHA, trans);
	if(fond == NULL) {
		engine_warning("-- Impossible de charger l'image --");
	}
	imgs[objet].surface = SDL_DisplayFormat(fond);
	set_state(objet, x, y);
	SDL_FreeSurface(fond);
}

void change_img(int objet, char* str) {
    SDL_Surface *fond;
	fond = IMG_Load(str);
	imgs[objet].surface = SDL_DisplayFormat(fond);
	set_state(objet, 0, 0);
	SDL_FreeSurface(fond);
}
     
int* get_state(int objet) {

	int *infos;
	infos = (int *) malloc(4 * sizeof(int));
	infos[0] = imgs[objet].surface->w;
	infos[1] = imgs[objet].surface->h;
	infos[2] = imgs[objet].pos.x;
	infos[3] = imgs[objet].pos.y;

	return infos;
}

void set_state(int objet, int x, int y) {
	imgs[objet].pos.x	= x;
	imgs[objet].pos.y	= y;
}

void set_hover_img(int objet, char* str) {
	imgs[objet].hover = IMG_Load(str);
	imgs[objet].get_hover = TRUE;
}

void blit_img(int objet, int hover) {
	if(hover == TRUE) {
		SDL_BlitSurface(imgs[objet].hover, NULL, screen, &imgs[objet].pos); 
		imgs[objet].is_hover = TRUE;
	}
	else {
		SDL_BlitSurface(imgs[objet].surface, NULL, screen, &imgs[objet].pos);
		imgs[objet].is_hover = FALSE;
	}
}

void flip() {
	SDL_Flip(screen);
}

	/* -------- Fin couche basse --------- */

	/* -------- Couche systeme --------- */

void engine_error(char *str) {
	fprintf(stderr, (char*)str, "%s");
	free_all_memory();
	exit(1);
}

void engine_warning(char *str) {
	fprintf(stderr, (char*)str, "%s");
}	

void free_all_memory() {
	SDL_FreeSurface(screen);
	SDL_FreeSurface(curseursurface);
	int i = 0;
	for(i = 0; i < nbr_img; i++) 
		SDL_FreeSurface(imgs[i].surface);
	TTF_Quit();
	SDL_Quit();
	sound_close();
}

	/* -------- Fin couche systeme --------- */

	/* -------- Couche interface --------- */

void show_animation() {

	int i;

	SDL_Surface *anim[3];
	anim[0] = IMG_Load("content/animation/1.jpg");
	anim[1] = IMG_Load("content/animation/2.jpg");
	anim[2] = IMG_Load("content/animation/3.jpg");
	SDL_Rect position;
	position.x = 0; 
    position.y = 0;
	
	for(i = 0; i < 100; i++)
	{
		Uint32 temps = SDL_GetTicks() / 800;
		SDL_BlitSurface(anim[temps%3], NULL, screen, &position);
		SDL_Flip(screen);
	}
	
	Sleep(1000);
}

void show_menu() {

	blit_img(FOND, FALSE);
    blit_img(LOGO_MENU, FALSE);
	blit_img(BOUTON_JOUER, FALSE);
	blit_img(BOUTON_OPTIONS, FALSE);
	blit_img(BOUTON_QUITTER, FALSE); 
	blit_img(BOUTON_AIDE, FALSE); 
    show_text(TEXTE_SUPINFO);	
}

	/* -------- Fin couche interface --------- */

	/* -------- Couche interaction --------- */

void wait_event() {
	SDL_WaitEvent(&event);
}

int who_is_clicked(int x, int y) {
	int i = 0;
	for(i = 1; i < nbr_img; i++) {
		if(is_on(i, x, y) && (i < 30 || i > 81)) {
            return i;		
		}
	} 
	return 0;
}

int is_on(int objet, int x, int y) {

	int *infos;
	infos = (int*) malloc(4 * sizeof(int));
	infos = get_state(objet);
	if(x >= infos[X] && x <= infos[X] + infos[W] && y >= infos[Y] && y <= infos[Y] + infos[H])
		return TRUE;
	return FALSE;
}

int is_clickable(int x, int y) {
	if(who_is_clicked(x, y) != FOND && who_is_clicked(x, y) != LOGO_MENU)
		return TRUE;
	return FALSE;
}

void apply_hover(int x, int y, int min, int max, int exep) {
	int id, i;
	id = who_is_clicked(x, y);
	
	if(id >= min && id <= max || id == exep)
	{
	    if(imgs[id].get_hover == TRUE && imgs[id].hover != NULL) {
		                      blit_img(id, TRUE);
        }
    }
    
	if(id == 0 || (id > 30 && id < 81))		
		for(i = 0; i < nbr_img; i++)
			if(imgs[i].is_hover == TRUE)
				blit_img(i, FALSE);
			
	flip();
}

	/* -------- Fin couche interaction --------- */

void text_init() {

	(TTF_Init() == -1) ?
	engine_error("Impossible d'utiliser TTF") : 1;

    font = TTF_OpenFont("content/polices/arkitech.ttf", 15);
    font2 = TTF_OpenFont("content/polices/arkitech.ttf", 10);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SetFontStyle(font2, TTF_STYLE_BOLD);
	load_all_texts();
}

void load_all_texts() {
	
	texts = malloc(nbr_text * sizeof(struct text));

	load_text(TEXTE_SUPINFO, "SUPINFO", 10, 475, BLANC, 1);
	load_text(TEXTE_MISE, "A vous de miser !", 335, 75, NOIR, 1);
	load_text(TEXTE_SELECT, "A vous de selectionner les cartes", 200, 65, NOIR, 1);
	load_text(TEXTE_SELECT2, "que vous voulez garder !", 265, 85, NOIR, 1);
    load_text(PAIRE, "Vous avez obtenu une paire", 245, 75, NOIR, 1);
	load_text(DBPAIRE, "Vous avez obtenu une double paire", 190, 75, NOIR, 1);
	load_text(BRELAN, "Vous avez obtenu un brelan", 242, 75, NOIR, 1);
	load_text(QUINTE, "Vous avez obtenu une quinte", 236, 75, NOIR, 1);
	load_text(FLUSH, "Vous avez obtenu une couleur", 225, 75, NOIR, 1);
	load_text(FULL, "Vous avez obtenu un full", 258, 75, NOIR, 1);
	load_text(CARRE, "Vous avez obtenu un carré", 250, 75, NOIR, 1);
	load_text(QFLUSH, "Vous avez obtenu une quinte flush", 190, 75, NOIR, 1);
	load_text(QFLUSHR, "Vous avez obtenu une quinte flush royale", 135, 75, NOIR, 1);
	load_text(NOTHING, "Vous n'avez obtenu aucune combinaison", 158, 75, NOIR, 1);
	load_text(ARGENT, "Vous possedez une somme de :", 15, 473, NOIR, 1);
	load_text(ARGENTSOMME, "100", 467, 473, NOIR, 1);
	load_text(MISE, "Vous avez mise :", 560, 473, NOIR, 1);
	load_text(MISESOMME, "0", 805, 473, NOIR, 1);
	load_text(OPTIONSANS, "Sans", 350, 30, BLANC, 1);
	load_text(OPTIONVOLUMEFAIBLE, "Faible", 450, 30, BLANC, 1);
	load_text(OPTIONVOLUMEMOYEN, "Moyen", 570, 30, BLANC, 1);
	load_text(OPTIONVOLUMEFORT, "Fort", 690, 30, BLANC, 1);
	load_text(OPTIONMUSIQUE, "Musique d'ambiance :", 20, 80, BLANC, 1);
	load_text(OPTIONSONS, "Sons du jeu :", 20, 180, BLANC, 1);
	load_text(OPTIONSONSAVEC, "Avec", 450, 130, BLANC, 1);
	load_text(OPTIONSONSSANS, "Sans", 350, 130, BLANC, 1);
	load_text(OPTIONCHOIXMUSIQUE, "Sélectionner votre", 20, 280, BLANC, 1);
	load_text(OPTIONCHOIXMUSIQUE2, "musique d'ambiance :", 20, 310, BLANC, 1);
	load_text(MUSIQUE1, "Pulpremix", 350, 230, BLANC, 1);
	load_text(MUSIQUE2, "Bassness", 570, 230, BLANC, 1);
	load_text(PERDU, "Vous avez perdu !", 325, 10, NOIR, 1);
	load_text(GAGNE, "Vous avez gagne !", 325, 10, NOIR, 1);
	load_text(GAIN, "Votre gain est de :", 320, 350, NOIR, 1);
	load_text(GAINSOMME, "0", 440, 400, NOIR, 1);
	load_text(REGLE1, "Tout d'abord, misez une somme à l'aide des jetons prédisposés", 1000, 1000, NOIR, 2);
	load_text(REGLE1BIS, "à cet effet. A l'instar d'un jeu de poker, vous avez la possibilité", 1000, 1000, NOIR, 2);
    load_text(REGLE1BIS2, "de tout miser en utilisant \"Tapis\". Une fois que la mise vous", 1000, 1000, NOIR, 2);
    load_text(REGLE1BIS3, "semble correcte, utilisez \"Premier tirage\" pour continuer !", 1000, 1000, NOIR, 2);
    load_text(REGLE2, "Puis, le principe est simple, vous disposez d'un premier tirage dans", 1000, 1000, NOIR, 2);
	load_text(REGLE2BIS, "lequel il va falloir sélectionner les cartes susceptibles de", 1000, 1000, NOIR, 2);
	load_text(REGLE2BIS2, "fournir une bonne combinaison lors du second tirage. Appuyez sur", 1000, 1000, NOIR, 2);
    load_text(REGLE2BIS3, "\"Garder\" en dessous de ladite carte et passez au second tirage !", 1000, 1000, NOIR, 2);
    load_text(REGLE3, "Lors du second tirage, les cartes qui n'ont pas été retenues", 1000, 1000, NOIR, 2);
    load_text(REGLE3BIS, "(marquées par une croix rouge) se voient changées par de nouvelles", 1000, 1000, NOIR, 2);
    load_text(REGLE3BIS2, "de façon aléatoire. Si vous obtenez une des nombreuses", 1000, 1000, NOIR, 2);
	load_text(REGLE3BIS3, "combinaisons possibles, alors votre mise sera multipliée selon", 1000, 1000, NOIR, 2);
    load_text(REGLE3BIS4, "des coefficients prédéfinis et ajoutée à votre argent.", 1000, 1000, NOIR, 2);
    load_text(REGLE4, "Vous pouvez dorénavant continuer votre partie sauf si votre", 1000, 1000, NOIR, 2);
	load_text(REGLE4BIS, "argent est arrivé à 0, auquel cas vous avez perdu ou alors votre", 1000, 1000, NOIR, 2);
	load_text(REGLE4BIS2, "argent dépasse 10 000, félicitations, vous avez gagné !", 1000, 1000, NOIR, 2);
	load_text(TEXT_COMBIPAIRE, "Paire", 15, 30, BLANC, 1);
	load_text(TEXT_COMBIDOUBLEPAIRE, "Double paire", 308, 30, BLANC, 1);
	load_text(TEXT_COMBIBRELAN, "Brelan", 602, 30, BLANC, 1);
	load_text(TEXT_COMBICARRE, "Carre", 15, 290, BLANC, 1);
	load_text(TEXT_COMBICOULEUR, "Couleur", 308, 160, BLANC, 1);
	load_text(TEXT_COMBIFULL, "Full", 602, 160, BLANC, 1);
	load_text(TEXT_COMBIQUINTE, "Quinte", 15, 160, BLANC, 1);
	load_text(TEXT_COMBIQUINTEFLUSH, "Quinte flush", 308, 290, BLANC, 1);
	load_text(TEXT_COMBIQUINTEFLUSHROYALE, "Quinte flush royale", 602, 290, BLANC, 1);
}

void load_text(int objet, char* str, int x, int y, int r, int g, int b, int fontchoix) {
	texts[objet].content = str;
	texts[objet].pos.x = x;
	texts[objet].pos.y = y;
	texts[objet].color.r = r;
	texts[objet].color.g = g;
	texts[objet].color.b = b;
	if(fontchoix == 1)
	texts[objet].surface = TTF_RenderText_Blended(font, texts[objet].content, texts[objet].color);
	if(fontchoix == 2)
	texts[objet].surface = TTF_RenderText_Blended(font2, texts[objet].content, texts[objet].color);
}

void show_text(int objet) {
	SDL_BlitSurface(texts[objet].surface, NULL, screen, &texts[objet].pos);
}

void modify_text(int objet, char* strmodify, int r, int g, int b, int fontchoix) {
     texts[objet].color.r = r;
	 texts[objet].color.g = g;
	 texts[objet].color.b = b;
	 if(fontchoix == 1)
     texts[objet].surface = TTF_RenderText_Blended(font, strmodify, texts[objet].color);
     if(fontchoix == 2)
	 texts[objet].surface = TTF_RenderText_Blended(font2, strmodify, texts[objet].color);
}

void changecolor_text(int objet, int r, int g, int b) {
     texts[objet].color.r = r;
	 texts[objet].color.g = g;
	 texts[objet].color.b = b;
     texts[objet].surface = TTF_RenderText_Blended(font, texts[objet].content, texts[objet].color);
}

void changeposition_text(int objet, int x, int y) {
     texts[objet].pos.x = x;
	 texts[objet].pos.y = y;
}

void curseurchargement() {
     curseursurface = IMG_Load("content/general/cursor.png");
}

void curseurplacement(int x, int y) {
     
     curseurchargement();
     
     curseurposition.x = x; 
     curseurposition.y = y;
     
     SDL_BlitSurface(curseursurface, NULL, screen, &curseurposition); 
}
