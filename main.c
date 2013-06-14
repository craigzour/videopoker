/*##########################################
#                                          #
#                  main.c                  #
#                                          #
#               par Clément                # 
#                                          #
# Ce fichier est l'assemblage des fonctions#
# provenant de tous les moteurs du jeu.    #
#                                          #
##########################################*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "ressources.h"
#include "gfx_moteur.h"
#include "fct_jeu.h"
#include "main.h"
#include "sound_moteur.h"

int bouclejeu = TRUE;

int selectmusiquesans = 0;
int selectmusiquefaible = 0;
int selectmusiquemoyen = 0;
int selectmusiqueforte = 1;
int selectsonssans = 0;
int selectsonsavec = 1;

int selectmusique1 = 1;
int selectmusique2 = 0;
int musiquechoisi = 0;

int carte1 = 0;
int carte2 = 0;
int carte3 = 0;
int carte4 = 0;
int carte5 = 0;
int affiche = 0;
int affichagealea = 0;
     
void afficherjeu();

void afficheroption();

void afficheraide();

void affichercombi();

void afficherresultat(int action);

void affichagealeatoire(int alea);

int checksonoption();

int checkmusiquechoisi();

int main(int argc, char *argv[]) {

	engine_init();
	
    loadmusique();

	musiquedefond();
	
	int buttonpush;
     
	while (bouclejeu) {	
    
    show_menu();
    
		wait_event();
	   	switch(event.type){
			case QUIT:
				bouclejeu = 0;
			break;
			case M_MOUSE:
				apply_hover(event.motion.x, event.motion.y, 2, 5, 0);
				//curseurplacement(event.motion.x, event.motion.y);
			break;
			case CLICK:
				buttonpush = who_is_clicked(event.button.x, event.button.y);
				if (event.button.button == SDL_BUTTON_LEFT)
				{
                   switch(buttonpush)
                   {
                             case BOUTON_QUITTER:
                                  bouclejeu = FALSE;
                                  break;
                             case BOUTON_JOUER:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }                
                                  afficherjeu();
                                  break;
                             case BOUTON_OPTIONS:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }
                                  afficheroption();
                                  break;
                             case BOUTON_AIDE:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }
                                  afficheraide();
                                  break;   
                   }
			break;
            }
	    	}
    flip(); 
	}	
}

void afficherjeu() {
     
     int boucle = TRUE;
     int buttonpush;
     int selectC1 = 0;
     int selectC2 = 0;
     int selectC3 = 0;
     int selectC4 = 0;
     int selectC5 = 0;
     int secondtirageok = FALSE;
     int mise = 0;
     int etape = 0;
     int hovmax = 13;
     int hovexep = 19;
     
     carte1 = 0;
     carte2 = 0;
     carte3 = 0;
     carte4 = 0;
     carte5 = 0;

     srand(time(NULL));
     
     affichagealea = (rand() % (3 - 0 + 0)) + 0;
     affiche = 0;
     
     change_img(FOND, "content/jeu/fondjeu.png");
     
     change_img(BOUTON_MENU, "content/jeu/buttonmenu.png");
     set_hover_img(BOUTON_MENU, "content/jeu/buttonmenuhover.png");
     set_state(BOUTON_MENU, 68, 9); 
     
     change_img(BOUTON_ANNULEMISE, "content/jeu/buttontapis.png");
     set_hover_img(BOUTON_ANNULEMISE, "content/jeu/buttontapishover.png");
     set_state(BOUTON_ANNULEMISE, ((900-230)/2), 9);
     
     set_state(BOUTON_OPTIONS, 1000, 1000); 
     set_state(BOUTON_QUITTER, 1000, 1000); 
     
     set_state(SCARTEO1, 1000, 1000); 
     set_state(SCARTEO2, 1000, 1000);
     set_state(SCARTEO3, 1000, 1000);
     set_state(SCARTEO4, 1000, 1000);
     set_state(SCARTEO5, 1000, 1000);
     set_state(SCARTEN1, 200, 120);
     set_state(SCARTEN2, 350, 120);
     set_state(SCARTEN3, 500, 120);
     set_state(SCARTEN4, 650, 120);
     set_state(SCARTEN5, 800, 120);
         
     deselection();                         
     distributiondescartes(PREMIERTIRAGE); 
     
     while (boucle) { 

     blit_img(FOND, FALSE);
     blit_img(BOUTON_MENU, FALSE);
     blit_img(BOUTON_CARTES, FALSE);
     
     if(etape == 0)
     {
              blit_img(BOUTON_ANNULEMISE, FALSE);
     }
     
     if(etape == 1)
     {
              blit_img(GCARTE1, FALSE);
              blit_img(GCARTE2, FALSE);
              blit_img(GCARTE3, FALSE);
              blit_img(GCARTE4, FALSE);
              blit_img(GCARTE5, FALSE);
     }
     
     if(etape == 0)
     {
              if(checkargent() >= 1)
                               blit_img(PION1, FALSE);
              if(checkargent() >= 5)
                               blit_img(PION5, FALSE);
              if(checkargent() >= 10)
                               blit_img(PION10, FALSE);
              if(checkargent() >= 20)
                               blit_img(PION20, FALSE);
              if(checkargent() >= 100)
                               blit_img(PION100, FALSE);
              if(checkargent() >= 200)
                               blit_img(PION200, FALSE);
     }
     
     if(mise == 0)
     {
             show_text(TEXTE_MISE);
     }
     
     if(etape == 1)
     {
             show_text(TEXTE_SELECT);
             show_text(TEXTE_SELECT2);
     }
     
     show_text(ARGENT); 
     show_text(ARGENTSOMME); 
     show_text(MISE); 
     show_text(MISESOMME); 
     
     carte1 = checkcartes(1);
     carte2 = checkcartes(2);
     carte3 = checkcartes(3);
     carte4 = checkcartes(4);
     carte5 = checkcartes(5);
     
     set_state(carte1, 79, 111);
     set_state(carte2, 230, 111);
     set_state(carte3, 380, 111);
     set_state(carte4, 530, 111);
     set_state(carte5, 681, 111);

     if(etape == 1)
     {
              affichagealeatoire(affichagealea);
     }
     
     if(etape == 1)
     { 
              blit_img(SCARTEO1, FALSE);
              blit_img(SCARTEO2, FALSE);
              blit_img(SCARTEO3, FALSE);
              blit_img(SCARTEO4, FALSE);
              blit_img(SCARTEO5, FALSE);
              blit_img(SCARTEN1, FALSE);
              blit_img(SCARTEN2, FALSE);
              blit_img(SCARTEN3, FALSE);
              blit_img(SCARTEN4, FALSE);
              blit_img(SCARTEN5, FALSE);
     }
     
     if(secondtirageok == TRUE)
     {
              affichagealeatoire(affichagealea);
              reconnaissancecombinaison();         
              changecolor_text(TEXTE_MISE, NOIR);
     }
                                       
		wait_event();
	   	switch(event.type){
			case QUIT:
				boucle = FALSE;
				bouclejeu = FALSE;
			break;
			case M_MOUSE:
				apply_hover(event.motion.x, event.motion.y, 6, hovmax, hovexep);
				//curseurplacement(event.motion.x, event.motion.y);                
			break;
			case CLICK:
				buttonpush = who_is_clicked(event.button.x, event.button.y);
				if (event.button.button == SDL_BUTTON_LEFT)
				{
				   switch(buttonpush)
                   {
                             case BOUTON_MENU:
                                  set_state(BOUTON_OPTIONS, ((900-310)/2), 310);
                                  set_state(BOUTON_QUITTER, ((900-310)/2), 390);
                                  change_img(FOND, "content/general/fond.png");
                                  
                                  set_state(PION1, 73, 320);
                                  set_state(PION5, 202, 320);
                                  set_state(PION10, 330, 320);
                                  set_state(PION20, 458, 320);
                                  set_state(PION100, 586, 320);
                                  set_state(PION200, 714, 320);
                                  
                                  changerargent(SAVE, 0); 
                                  boucle = FALSE;
                             break;
                             case BOUTON_CARTES:
                                  if(etape == 0)
                                  {
                                           if(mise == 1)
                                           {
                                                   if(selectsonsavec == 1)
                                                   {
                                                                     jouer(SON_CARTES);
                                                   }
                                                   
                                                   hovmax = 18;
                                                   hovexep = 0;
                                                   etape = 1;  
                                                   
                                                   set_state(PION1, 1000, 1000);
                                                   set_state(PION5, 1000, 1000);
                                                   set_state(PION10, 1000, 1000);
                                                   set_state(PION20, 1000, 1000);
                                                   set_state(PION100, 1000, 1000);
                                                   set_state(PION200, 1000, 1000);
                                                   
                                                   change_img(BOUTON_CARTES, "content/jeu/buttonsecondtirage.png");
                                                   set_hover_img(BOUTON_CARTES, "content/jeu/buttonsecondtiragehover.png");
                                                   set_state(BOUTON_CARTES, 605, 9);   
                                           }
                                           else
                                           {
                                                   changecolor_text(TEXTE_MISE, ROUGE);
                                           }
                                  }
                                  else if(etape == 1)
                                  {
                                      if(selectsonsavec == 1)
                                      {
                                           jouer(SON_CARTES);
                                      }
                                      
                                      etape = 2;
                                      distributiondescartes(SECONDTIRAGE);
                                      secondtirageok = TRUE;
                                      hovmax = 13;
                                      
                                      set_state(PION1, 73, 320);
                                      set_state(PION5, 202, 320);
                                      set_state(PION10, 330, 320);
                                      set_state(PION20, 458, 320);
                                      set_state(PION100, 586, 320);
                                      set_state(PION200, 714, 320);
                                      
                                      change_img(BOUTON_CARTES, "content/jeu/buttoncontinuer.png");
                                      set_hover_img(BOUTON_CARTES, "content/jeu/buttoncontinuerhover.png");
                                      set_state(BOUTON_CARTES, 605, 9);
                                  }
                                  else
                                  {
                                      etape = 3;
                                      hovexep = 19;
                                      
                                      change_img(BOUTON_CARTES, "content/jeu/buttonpremiertirage.png");
                                      set_hover_img(BOUTON_CARTES, "content/jeu/buttonpremiertiragehover.png");
                                      set_state(BOUTON_CARTES, 605, 9); 
                                  }
                             break;
                             case BOUTON_ANNULEMISE:
                                  if(etape == 0)
                                  {
                                           if(mise == 0)
                                           {
                                                   if(selectsonsavec == 1)
                                                   {
                                                                     jouer(SON_TAPIS);
                                                   }
                                                   
                                                   changerargent(AUGMENTERMISE, checkargent()); 
                                                   mise = 1;  
                                           }
                                           else
                                           {
                                                   changerargent(ANNULEMISE, 0); 
                                                   changecolor_text(TEXTE_MISE, NOIR);
                                                   mise = 0;
                                           }
                                  }
                             break;
                             case GCARTE1:
                                  if(selectC1 == 0)
                                  {
                                              set_state(SCARTEO1, 200, 120); 
                                              set_state(SCARTEN1, 1000, 1000);
                                              selectC1 = 1;
                                              selectioncarte(0);
                                  }
                                  else
                                  {
                                              set_state(SCARTEO1, 1000, 1000);
                                              set_state(SCARTEN1, 200, 120);
                                              selectC1 = 0;
                                              selectioncarte(0);
                                  }
                             break;
                             case GCARTE2:
                                  if(selectC2 == 0)
                                  {
                                              set_state(SCARTEO2, 350, 120); 
                                              set_state(SCARTEN2, 1000, 1000);
                                              selectC2 = 1;
                                              selectioncarte(1);
                                  }
                                  else
                                  {
                                              set_state(SCARTEO2, 1000, 1000);
                                              set_state(SCARTEN2, 350, 120);
                                              selectC2 = 0;
                                              selectioncarte(1);
                                  }
                             break;
                             case GCARTE3:
                                  if(selectC3 == 0)
                                  {
                                              set_state(SCARTEO3, 500, 120); 
                                              set_state(SCARTEN3, 1000, 1000);
                                              selectC3 = 1;
                                              selectioncarte(2);
                                  }
                                  else
                                  {
                                              set_state(SCARTEO3, 1000, 1000);
                                              set_state(SCARTEN3, 500, 120);
                                              selectC3 = 0;
                                              selectioncarte(2);
                                  } 
                             break;
                             case GCARTE4:
                                  if(selectC4 == 0)
                                  {
                                              set_state(SCARTEO4, 650, 120); 
                                              set_state(SCARTEN4, 1000, 1000);
                                              selectC4 = 1;
                                              selectioncarte(3);
                                  }
                                  else
                                  {
                                              set_state(SCARTEO4, 1000, 1000);
                                              set_state(SCARTEN4, 650, 120);
                                              selectC4 = 0;
                                              selectioncarte(3);
                                  }
                             break;
                             case GCARTE5: //bouton garder de la carte 5
                                  if(selectC5 == 0) //si la carte n'est pas sélectionnée
                                  {
                                              set_state(SCARTEO5, 800, 120); //on modifie le témoin de sélection
                                              set_state(SCARTEN5, 1000, 1000);
                                              selectC5 = 1; //on indique que la cartes est sélectionnée
                                              selectioncarte(4); //on envoi une sélection sur la carte 4
                                  }
                                  else //sinon si la carte est sélectionnée
                                  {
                                              set_state(SCARTEO5, 1000, 1000); //on modifie le témoin de sélection
                                              set_state(SCARTEN5, 800, 120);
                                              selectC5 = 0; //on indique que la cartes n'est plus sélectionnée
                                              selectioncarte(4); //on envoi une désélection sur la carte 4
                                  } 
                             break;
                             case PION1: //pion (valeur 1) de mise
                                  if(etape == 0 && checkargent() >= 1) //si on est à l'étape de mise et qu'il reste plus de 1 d'argent
                                  {   
                                              changerargent(AUGMENTERMISE, 1);  //on augmente la mise de 1
                                              mise = 1; //on indique que la mise à été effectué
                                  }                             
                             break;
                             case PION5:
                                  if(etape == 0 && checkargent() >= 5)
                                  {
                                              changerargent(AUGMENTERMISE, 5); 
                                              mise = 1; 
                                  }        
                             break;
                             case PION10:
                                  if(etape == 0 && checkargent() >= 10)
                                  {
                                              changerargent(AUGMENTERMISE, 10); 
                                              mise = 1; 
                                  }        
                             break;
                             case PION20:
                                  if(etape == 0 && checkargent() >= 20)
                                  {
                                              changerargent(AUGMENTERMISE, 20); 
                                              mise = 1; 
                                  }        
                             break;
                             case PION100:
                                  if(etape == 0 && checkargent() >= 100)
                                  {
                                              changerargent(AUGMENTERMISE, 100); 
                                              mise = 1;  
                                  }       
                             break;
                             case PION200:
                                  if(etape == 0 && checkargent() >= 200)
                                  {
                                              changerargent(AUGMENTERMISE, 200); 
                                              mise = 1;   
                                  }      
                             break;
                   }
			break;
            }
	    	} 
	    	
            if(mise == 1)
            {
                    change_img(BOUTON_ANNULEMISE, "content/jeu/buttonannulemise.png");
                    set_hover_img(BOUTON_ANNULEMISE, "content/jeu/buttonannulemisehover.png");
                    set_state(BOUTON_ANNULEMISE, ((900-230)/2), 9);
            }
            else
            {
                    change_img(BOUTON_ANNULEMISE, "content/jeu/buttontapis.png");
                    set_hover_img(BOUTON_ANNULEMISE, "content/jeu/buttontapishover.png");
                    set_state(BOUTON_ANNULEMISE, ((900-230)/2), 9);
            }    
            if(etape == 3)
            {
                     if(checkargent() > 0 && checkargent() < 10000)
                     {
                          boucle = FALSE;
                          afficherjeu();
                     }
                     
                     else if(checkargent() >= 10000)
                     {
                          changerargent(DEBUTPARTIE, 0);
                          
                          if(selectsonsavec == 1)
                          {
                                            jouer(SON_APPLAUDISSEMENT);
                          }
                          
                          boucle = FALSE;
                          afficherresultat(1);
                     }
                     
                     else
                     {
                          changerargent(DEBUTPARTIE, 0);
                          
                          if(selectsonsavec == 1)
                          {
                                            jouer(SON_PERDU);
                          }
                          
                          boucle = FALSE;
                          afficherresultat(0);
                          
                     }
            }       
    flip(); 
	}
}

void afficheroption() {
     
     int boucle = 1;
     int buttonpush;
     
     set_state(LOGO_MENU, 1000, 1000);
     set_state(BOUTON_QUITTER, 1000, 1000);
     
     change_img(BOUTON_MENU, "content/general/buttonmenu.png");
     set_hover_img(BOUTON_MENU, "content/general/buttonmenuhover.png");
     set_state(BOUTON_MENU, ((900-310)/2), 420);
     
     while (boucle) {	
     
     blit_img(FOND, FALSE);
     blit_img(BOUTON_MENU, FALSE);
     
     if(selectmusiquesans == 0)
         blit_img(BOUTON_MUSIQUESANS, FALSE);
     else
         blit_img(BOUTON_MUSIQUESANSCOCHE, FALSE);
     if(selectmusiquefaible == 0)
         blit_img(BOUTON_MUSIQUEFAIBLE, FALSE);
     else
         blit_img(BOUTON_MUSIQUEFAIBLECOCHE, FALSE);
     if(selectmusiquemoyen == 0)
         blit_img(BOUTON_MUSIQUEMOYEN, FALSE);
     else
         blit_img(BOUTON_MUSIQUEMOYENCOCHE, FALSE);
     if(selectmusiqueforte == 0)
         blit_img(BOUTON_MUSIQUEFORT, FALSE);
     else
         blit_img(BOUTON_MUSIQUEFORTCOCHE, FALSE);
         
     if(selectsonsavec == 0)
         blit_img(BOUTON_SONSAVEC, FALSE);
     else
         blit_img(BOUTON_SONSAVECCOCHE, FALSE);
     if(selectsonssans == 0)
         blit_img(BOUTON_SONSSANS, FALSE);
     else
         blit_img(BOUTON_SONSSANSCOCHE, FALSE);
     if(selectmusique1 == 0)
         blit_img(BOUTON_MUSIQUE1, FALSE);
     else
         blit_img(BOUTON_MUSIQUE1COCHE, FALSE);
     if(selectmusique2 == 0)
         blit_img(BOUTON_MUSIQUE2, FALSE);
     else
         blit_img(BOUTON_MUSIQUE2COCHE, FALSE);
     
     show_text(OPTIONSANS);
     show_text(OPTIONVOLUMEFAIBLE);
     show_text(OPTIONVOLUMEMOYEN);
     show_text(OPTIONVOLUMEFORT);
     show_text(OPTIONMUSIQUE);
     show_text(OPTIONSONS);
     show_text(OPTIONSONSAVEC);
     show_text(OPTIONSONSSANS);
     show_text(OPTIONCHOIXMUSIQUE);
     show_text(OPTIONCHOIXMUSIQUE2);
     show_text(MUSIQUE1);
     show_text(MUSIQUE2);
     
		wait_event();
	   	switch(event.type){
			case QUIT:
				boucle = FALSE;
				bouclejeu = FALSE;
			break;
			case M_MOUSE:
				apply_hover(event.motion.x, event.motion.y, 0, 0, 6);
				//curseurplacement(event.motion.x, event.motion.y);
			break;
			case CLICK:
				buttonpush = who_is_clicked(event.button.x, event.button.y);
				if (event.button.button == SDL_BUTTON_LEFT)
				{
                   switch(buttonpush)
                   {
                             case BOUTON_MUSIQUESANS:
                                  coupermusique();
                                  selectmusiquesans = 1;
                                  selectmusiquefaible = 0;
                                  selectmusiquemoyen = 0;
                                  selectmusiqueforte = 0;
                                  break;
                             case BOUTON_MUSIQUEFAIBLE:
                                  modifiervolume(10);
                                  selectmusiquesans = 0;
                                  selectmusiquefaible = 1;
                                  selectmusiquemoyen = 0;
                                  selectmusiqueforte = 0;
                                  break;
                             case BOUTON_MUSIQUEMOYEN:
                                  modifiervolume(40);
                                  selectmusiquesans = 0;
                                  selectmusiquefaible = 0;
                                  selectmusiquemoyen = 1;
                                  selectmusiqueforte = 0;
                                  break;
                             case BOUTON_MUSIQUEFORT:
                                  modifiervolume(80);
                                  selectmusiquesans = 0;
                                  selectmusiquefaible = 0;
                                  selectmusiquemoyen = 0;
                                  selectmusiqueforte = 1;
                                  break;
                             case BOUTON_SONSAVEC:
                                  selectsonsavec = 1;
                                  selectsonssans = 0;
                                  break;
                             case BOUTON_SONSSANS:
                                  selectsonsavec = 0;
                                  selectsonssans = 1;
                                  break;
                             case BOUTON_MUSIQUE1:
                                  selectmusique1 = 1;
                                  selectmusique2 = 0;
                                  selectmusiquesans = 0;
                                  selectmusiquefaible = 0;
                                  selectmusiquemoyen = 0;
                                  selectmusiqueforte = 1;
                                  musiquechoisi = 0;
                                  modifiermusique();
                                  break;
                             case BOUTON_MUSIQUE2:
                                  selectmusique1 = 0;
                                  selectmusique2 = 1;
                                  selectmusiquesans = 0;
                                  selectmusiquefaible = 0;
                                  selectmusiquemoyen = 0;
                                  selectmusiqueforte = 1;
                                  musiquechoisi = 1;
                                  modifiermusique();
                                  break;
                             case BOUTON_MENU:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }   
                                  
                                  set_state(LOGO_MENU, ((900-666)/2), 30);
                                  set_state(BOUTON_QUITTER, ((900-310)/2), 390);
                                  set_state(BOUTON_MENU, 1000, 1000);
                                  boucle = FALSE;
                                  break;
                   }
			break;
            }
	    	}
                          
    flip(); 
	}
}

void afficheraide() {
     
     int boucle = 1;
     int buttonpush;
     int a = -800;
     int b = 901;
     int c = -800;
     int d = 901;
     int e = -800;
     int f = 901;
     int g = -800;
     int regle = 0;
     
     int h = -50;
     int i = -50;
     int j = -50;
     int k = -50;
     
     set_state(BOUTON_QUITTER, 1000, 1000);
     
     change_img(BOUTON_MENU, "content/general/buttonmenu.png");
     set_hover_img(BOUTON_MENU, "content/general/buttonmenuhover.png");
     set_state(BOUTON_MENU, ((900-310)/2), 430);
     
     change_img(BOUTON_AIDE, "content/aide/buttoncombinaison.png");
     set_hover_img(BOUTON_AIDE, "content/aide/buttoncombinaisonhover.png");
     set_state(BOUTON_AIDE, 825, 435);
     
     while (boucle) {	
     
     blit_img(FOND, FALSE);

     while(k < 315)
     {
             blit_img(FOND, FALSE);
     
             set_state(BANDER1, -190, h);
             blit_img(BANDER1, FALSE);
     
             set_state(BANDER2, 190, i);
             blit_img(BANDER2, FALSE);
     
             set_state(BANDER3, -190, j);
             blit_img(BANDER3, FALSE);
     
             set_state(BANDER4, 190, k);
             blit_img(BANDER4, FALSE);
     
             flip();
     
             if(h < 15)
                  h += 1;
             if(i < 115)
                  i += 2;
             if(j < 215)
                  j += 3;
     
                  k += 4;
     }
     
     k = 315;
     
     set_state(BANDER1, -190, h);
     blit_img(BANDER1, FALSE);
     set_state(BANDER2, 190, i);
     blit_img(BANDER2, FALSE);
     set_state(BANDER3, -190, j);
     blit_img(BANDER3, FALSE);
     set_state(BANDER4, 190, k);
     blit_img(BANDER4, FALSE);
     
     if(regle == 0)
     {
              while(a <= 10)
              {
                      set_state(BANDER1, -190, h);
                      blit_img(BANDER1, FALSE);
                      
                      changeposition_text(REGLE1, a, 22);
                      changeposition_text(REGLE1BIS, a, 42);
                      changeposition_text(REGLE1BIS2, a, 62);
                      changeposition_text(REGLE1BIS3, a, 82);
                      
                      show_text(REGLE1);
                      show_text(REGLE1BIS);
                      show_text(REGLE1BIS2);
                      show_text(REGLE1BIS3);
                      
                      flip();
                      
                      a += 2;
     }
     
     regle = 1;
     
     }
     
     if(regle == 1)
     {
              while(b >= 210)
              {
                      set_state(BANDER2, 190, i);
                      blit_img(BANDER2, FALSE);
                      
                      changeposition_text(REGLE2, b, 122);
                      changeposition_text(REGLE2BIS, b, 142);
                      changeposition_text(REGLE2BIS2, b, 162);
                      changeposition_text(REGLE2BIS3, b, 182);
                      
                      show_text(REGLE2);
                      show_text(REGLE2BIS);
                      show_text(REGLE2BIS2);
                      show_text(REGLE2BIS3);
                      
                      flip();
                      
                      b -= 2;
     }
     
     regle = 2;
     
     }
     
     if(regle == 2)
     {
              while(c <= 10)
              {
                      set_state(BANDER3, -190, j);
                      blit_img(BANDER3, FALSE);
                      
                      changeposition_text(REGLE3, c, 224);
                      changeposition_text(REGLE3BIS, c, 238);
                      changeposition_text(REGLE3BIS2, c, 252);
                      changeposition_text(REGLE3BIS3, c, 266);
                      changeposition_text(REGLE3BIS4, c, 280);
                      
                      show_text(REGLE3);
                      show_text(REGLE3BIS);
                      show_text(REGLE3BIS2);
                      show_text(REGLE3BIS3);
                      show_text(REGLE3BIS4);
                      
                      flip();
                      
                      c += 2;
     }
     
     regle = 3;
     
     }
     
     if(regle == 3)
     {
              while(d >= 210)
              {
                      set_state(BANDER4, 190, k);
                      blit_img(BANDER4, FALSE);
                      
                      changeposition_text(REGLE4, d, 332);
                      changeposition_text(REGLE4BIS, d, 352);
                      changeposition_text(REGLE4BIS2, d, 372);
                      
                      show_text(REGLE4);
                      show_text(REGLE4BIS);
                      show_text(REGLE4BIS2);
                      
                      flip();
                      
                      d -= 2;
     }
     
     regle = 4;
     
     }
     
     blit_img(BOUTON_MENU, FALSE);
     blit_img(BOUTON_AIDE, FALSE);
     
     show_text(REGLE1);
     show_text(REGLE1BIS);
     show_text(REGLE1BIS2);
     show_text(REGLE1BIS3);
     show_text(REGLE2);
     show_text(REGLE2BIS);
     show_text(REGLE2BIS2);
     show_text(REGLE2BIS3);
     show_text(REGLE3);
     show_text(REGLE3BIS);
     show_text(REGLE3BIS2);
     show_text(REGLE3BIS3);
     show_text(REGLE3BIS4);
     show_text(REGLE4);
     show_text(REGLE4BIS);
     show_text(REGLE4BIS2);

		wait_event();
	   	switch(event.type){
			case QUIT:
				boucle = FALSE;
				bouclejeu = FALSE;
			break;
			case M_MOUSE:
				apply_hover(event.motion.x, event.motion.y, 5, 6, 0);
				//curseurplacement(event.motion.x, event.motion.y);
			break;
			case CLICK:
				buttonpush = who_is_clicked(event.button.x, event.button.y);
				if (event.button.button == SDL_BUTTON_LEFT)
				{
				   switch(buttonpush)
                   {
                             case BOUTON_MENU:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }   
                                  
                                  set_state(BOUTON_QUITTER, ((900-310)/2), 390);
                                  set_state(BOUTON_MENU, 10, 0);
                                  
                                  change_img(BOUTON_AIDE, "content/menu/buttonaide.png");
                                  set_hover_img(BOUTON_AIDE, "content/menu/buttonaidehover.png");
                                  set_state(BOUTON_AIDE, 825, 435);
                                  
                                  boucle = FALSE;
                                  break;
                             case BOUTON_AIDE:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  }
                                  
                                  boucle = FALSE;
                                  affichercombi();
                                  break;
                   }
			break;
            }
	    	}                  
    flip(); 
	}
}

void affichercombi() {
     
     int boucle = 1;
     int buttonpush;
     
     set_state(BOUTON_QUITTER, 1000, 1000);
     
     change_img(BOUTON_MENU, "content/general/buttonmenu.png");
     set_hover_img(BOUTON_MENU, "content/general/buttonmenuhover.png");
     set_state(BOUTON_MENU, ((900-310)/2), 420);
     
     while (boucle) {	
     
     blit_img(FOND, FALSE);
     blit_img(BOUTON_MENU, FALSE);
     
     blit_img(COMBIPAIRE, FALSE);
     blit_img(COMBIDOUBLEPAIRE, FALSE);
     blit_img(COMBIBRELAN, FALSE);
     blit_img(COMBICARRE, FALSE);
     blit_img(COMBICOULEUR, FALSE);
     blit_img(COMBIFULL, FALSE);
     blit_img(COMBIQUINTE, FALSE);
     blit_img(COMBIQUINTEFLUSH, FALSE);
     blit_img(COMBIQUINTEFLUSHROYALE, FALSE);
     
     show_text(TEXT_COMBIPAIRE);
     show_text(TEXT_COMBIDOUBLEPAIRE);
     show_text(TEXT_COMBIBRELAN);
     show_text(TEXT_COMBICARRE);
     show_text(TEXT_COMBICOULEUR);
     show_text(TEXT_COMBIFULL);
     show_text(TEXT_COMBIQUINTE);
     show_text(TEXT_COMBIQUINTEFLUSH);
     show_text(TEXT_COMBIQUINTEFLUSHROYALE);
     
		wait_event();
	   	switch(event.type){
			case QUIT:
				boucle = FALSE;
				bouclejeu = FALSE;
			break;
			case M_MOUSE:
				apply_hover(event.motion.x, event.motion.y, 0, 0, 6);
				//curseurplacement(event.motion.x, event.motion.y);
			break;
			case CLICK:
				buttonpush = who_is_clicked(event.button.x, event.button.y);
				if (event.button.button == SDL_BUTTON_LEFT)
				{
				   switch(buttonpush)
                   {
                             case BOUTON_MENU:
                                  if(selectsonsavec == 1)
                                  {
                                      jouer(SON_BOUTON);
                                  } 
                                    
                                  set_state(BOUTON_QUITTER, ((900-310)/2), 390);
                                  set_state(BOUTON_MENU, 10, 0);
                                  
                                  change_img(BOUTON_AIDE, "content/menu/buttonaide.png");
                                  set_hover_img(BOUTON_AIDE, "content/menu/buttonaidehover.png");
                                  set_state(BOUTON_AIDE, 825, 435);
                                  
                                  boucle = FALSE;
                                  break;
                   }
			break;
            }
	    	}
                          
    flip(); 
	}
}

void afficherresultat(int action) {
     
     int boucle = TRUE;
     int buttonpush;
     int x = 0;
     int etape = 0;
     
     while (boucle) { 
           
     blit_img(FOND, FALSE);
     
     if(etape == 0)
     {
              while(x <= 450)
              {
              
                      blit_img(FOND, FALSE);
                      set_state(BANDE, 0, x);
                      blit_img(BANDE, FALSE);
     
                      if(action == 0)
                      {
                                changeposition_text(PERDU, 325, (x+20));
                                show_text(PERDU);
                      }
     
                      if(action == 1)
                      {
                                changeposition_text(GAGNE, 325, (x+20));
                                show_text(GAGNE);
                      }
     
                      flip();
     
                      x += 1;
              }
     
              etape = 1;
     
     }
     
     blit_img(BANDE, FALSE);
     
     if(etape == 1)
     {
              while(x >= 225)
              {
                      blit_img(FOND, FALSE);
                      set_state(BANDE, 0, x);
                      blit_img(BANDE, FALSE);
                      
                      if(action == 0)
                      {
                                changeposition_text(PERDU, 325, (x+20));
                                show_text(PERDU);
                      }
                      
                      if(action == 1)
                      {
                                changeposition_text(GAGNE, 325, (x+20));
                                show_text(GAGNE);
                      }
                      
                      flip();
                      
                      x -= 2;
              }
              
              etape = 2;
     
     }
     
     blit_img(BANDE, FALSE);
     
     if(action == 0)
     {
               show_text(PERDU); 
     }
     if(action == 1)
     {
               show_text(GAGNE);
     }
     
     sleep(1000);
     
     changerargent(DEBUTPARTIE, 0);
     
     set_state(BOUTON_OPTIONS, ((900-310)/2), 310);
     set_state(BOUTON_QUITTER, ((900-310)/2), 390);
     change_img(FOND, "content/general/fond.png");
     
     boucle = FALSE;                     
	}
}

void affichagealeatoire(int alea) {   
       
     switch(alea)
     {
             case 0:
                  blit_img(carte1, FALSE);
                  blit_img(carte5, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte2, FALSE);
                  blit_img(carte4, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);
                  }
                  
                  blit_img(carte3, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           affiche = 1;
                  }
             break;
             case 1:
                  blit_img(carte1, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte2, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte3, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte4, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte5, FALSE); 
                                   
                  if(affiche == 0)
                  {
                           flip();
                           affiche = 1;
                  }
             break;
             case 2:
                  blit_img(carte3, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);  
                  }
                  
                  blit_img(carte2, FALSE);
                  blit_img(carte4, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           sleep(200);
                  }
                  
                  blit_img(carte1, FALSE);
                  blit_img(carte5, FALSE);
                  
                  if(affiche == 0)
                  {
                           flip();
                           affiche = 1;
                  }
             break;
     }
     
}

int checksonoption() {
    
    int valeuraretourner = 0;
    
    valeuraretourner = selectsonsavec;
    
    return valeuraretourner;
}

int checkmusiquechoisi() {
    
    int valeuraretourner = 0;
    
    valeuraretourner = musiquechoisi;
    
    return valeuraretourner;
}
