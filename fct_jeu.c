/*##########################################
#                                          #
#               fct_jeu.c                  #
#                                          #
#  JALON 3                    par Clément  # 
#                                          #
# Ce fichier regroupe tous les algorithmes #
# utilisé pour le déroulement des phases   #
# du jeu.                                  #
#                                          #
##########################################*/


#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ressources.h"
#include "fct_jeu.h"
#include "sound_moteur.h"
#include "gfx_moteur.h"
#include "main.h"

//DECLARATION DES FONCTIONS CONTENUES DANS CE FICHIER

void distributiondescartes(int action);

void reconnaissancecombinaison();

void selectioncarte(int carte);

void changerargent(int action, int somme);

int checkargent();

int checkcartes(int car);

void deselection();

//***************************************************
     
typedef struct 
{  
       int valeur;
       int type;
       int nom;
       int selection;  
          
}defineCarte;

defineCarte carteAjouer[10];

char argentsomme[50] = "";
char misesomme[50] = "";
char gainsomme[50] = "";
int argent = 100;
int mise = 0;
int passage = 0;

void distributiondescartes(int action) {
     
     //Ici nous effectuons un tirage de 10 cartes aléatoires, 5 pour la première main et 5 pour le remplacement des cartes non conservées
     if(action == PREMIERTIRAGE)
     {
               srand(time(NULL));
     
               int y, var, var2, var3, var4;

               y = 0;
               var = 0;
               var2 = 0;
               var3 = 0;
               var4 = 0;
     
               int cartepassage[2][10];
     
               while(var <= 9)
               {
                         cartepassage[0][var] = (rand() % (12 - 0 + 0)) + 0;
                         cartepassage[1][var] = (rand() % (3 - 0 + 0)) + 0;
                         var2 = (var - 1);
            
                         while(var2 >= 0)
                         {
                                    if(cartepassage[0][var] == cartepassage[0][var2] && cartepassage[1][var] == cartepassage[1][var2])
                                    {
                                       
                                                            cartepassage[0][var] = (rand() % (13 - 0 + 0)) + 0;
                                                            cartepassage[1][var] = (rand() % (4 - 0 + 0)) + 0;
                                                            var2 = (var - 1);
                                    
                                    }
                    
                                    else
                                    {
                                                            var2--;
                                    }
                         }
            
                         var++;
               }
    
                   
               while(var4 <= 9)
               {           
                           
                            carteAjouer[var4].valeur = cartepassage[0][var3];
                            carteAjouer[var4].type = cartepassage[1][var3];
                            
                            var4++;
                            var3++;
                            
               }
     
               //Ici on assigne un nom de carte en fonction des valeurs aléatoires précedentes
               while(y < 10)
               {
                       
                       switch(carteAjouer[y].type)
                       {
                                        
                                        case 0: 
                                        switch(carteAjouer[y].valeur)
                                        {
                                                     
                                                     case 0:
                                                          carteAjouer[y].nom = ASCARREAU;
                                                     break;                              
                                                     case 1:
                                                          carteAjouer[y].nom = ROICARREAU;
                                                     break;
                                                     case 2:
                                                          carteAjouer[y].nom = DAMECARREAU;
                                                     break;
                                                     case 3:
                                                          carteAjouer[y].nom = VALETCARREAU;
                                                     break;
                                                     case 4:
                                                          carteAjouer[y].nom = DEUXCARREAU;
                                                     break;
                                                     case 5:
                                                          carteAjouer[y].nom = TROISCARREAU;
                                                     break;
                                                     case 6:
                                                          carteAjouer[y].nom = QUATRECARREAU;
                                                     break;
                                                     case 7:
                                                          carteAjouer[y].nom = CINQCARREAU;
                                                     break;
                                                     case 8:
                                                          carteAjouer[y].nom = SIXCARREAU;
                                                     break;
                                                     case 9:
                                                          carteAjouer[y].nom = SEPTCARREAU;
                                                     break;
                                                     case 10:
                                                          carteAjouer[y].nom = HUITCARREAU;
                                                     break;
                                                     case 11:
                                                          carteAjouer[y].nom = NEUFCARREAU;
                                                     break;
                                                     case 12:
                                                          carteAjouer[y].nom = DIXCARREAU;
                                                     break;
                                   
                                        }          
                                        break;
                                        case 1:
                                        switch(carteAjouer[y].valeur)
                                        {

                                                     case 0:
                                                          carteAjouer[y].nom = ASCOEUR;
                                                     break;                              
                                                     case 1:
                                                          carteAjouer[y].nom = ROICOEUR;
                                                     break;
                                                     case 2:
                                                          carteAjouer[y].nom = DAMECOEUR;
                                                     break;
                                                     case 3:
                                                          carteAjouer[y].nom = VALETCOEUR;
                                                     break;
                                                     case 4:
                                                          carteAjouer[y].nom = DEUXCOEUR;
                                                     break;
                                                     case 5:
                                                          carteAjouer[y].nom = TROISCOEUR;
                                                     break;
                                                     case 6:
                                                          carteAjouer[y].nom = QUATRECOEUR;
                                                     break;
                                                     case 7:
                                                          carteAjouer[y].nom = CINQCOEUR;
                                                     break;
                                                     case 8:
                                                          carteAjouer[y].nom = SIXCOEUR;
                                                     break;
                                                     case 9:
                                                          carteAjouer[y].nom = SEPTCOEUR;
                                                     break;
                                                     case 10:
                                                          carteAjouer[y].nom = HUITCOEUR;
                                                     break;
                                                     case 11:
                                                          carteAjouer[y].nom = NEUFCOEUR;
                                                     break;
                                                     case 12:
                                                          carteAjouer[y].nom = DIXCOEUR;
                                                     break;
                                   
                                        }          
                                        break;
                                        case 2:
                                        switch(carteAjouer[y].valeur)
                                        {

                                                     case 0:
                                                          carteAjouer[y].nom = ASPIQUE;
                                                     break;
                                                     case 1:
                                                          carteAjouer[y].nom = ROIPIQUE;
                                                     break;
                                                     case 2:
                                                          carteAjouer[y].nom = DAMEPIQUE;
                                                     break;
                                                     case 3:
                                                          carteAjouer[y].nom = VALETPIQUE;
                                                     break;
                                                     case 4:
                                                          carteAjouer[y].nom = DEUXPIQUE;
                                                     break;
                                                     case 5:
                                                          carteAjouer[y].nom = TROISPIQUE;
                                                     break;
                                                     case 6:
                                                          carteAjouer[y].nom = QUATREPIQUE;
                                                     break;
                                                     case 7:
                                                          carteAjouer[y].nom = CINQPIQUE;
                                                     break;
                                                     case 8:
                                                          carteAjouer[y].nom = SIXPIQUE;
                                                     break;
                                                     case 9:
                                                          carteAjouer[y].nom = SEPTPIQUE;
                                                     break;
                                                     case 10:
                                                          carteAjouer[y].nom = HUITPIQUE;
                                                     break;
                                                     case 11:
                                                          carteAjouer[y].nom = NEUFPIQUE;
                                                     break;
                                                     case 12:
                                                          carteAjouer[y].nom = DIXPIQUE;
                                                     break;
                                   
                                        }          
                                        break;
                                        case 3:
                                        switch(carteAjouer[y].valeur)
                                        {

                                                     case 0:
                                                          carteAjouer[y].nom = ASTREFLE;
                                                     break;
                                                     case 1:
                                                          carteAjouer[y].nom = ROITREFLE;
                                                     break;
                                                     case 2:
                                                          carteAjouer[y].nom = DAMETREFLE;
                                                     break;
                                                     case 3:
                                                          carteAjouer[y].nom = VALETTREFLE;
                                                     break;
                                                     case 4:
                                                          carteAjouer[y].nom = DEUXTREFLE;
                                                     break;
                                                     case 5:
                                                          carteAjouer[y].nom = TROISTREFLE;
                                                     break;
                                                     case 6:
                                                          carteAjouer[y].nom = QUATRETREFLE;
                                                     break;
                                                     case 7:
                                                          carteAjouer[y].nom = CINQTREFLE;
                                                     break;
                                                     case 8:
                                                          carteAjouer[y].nom = SIXTREFLE;
                                                     break;
                                                     case 9:
                                                          carteAjouer[y].nom = SEPTTREFLE;
                                                     break;
                                                     case 10:
                                                          carteAjouer[y].nom = HUITTREFLE;
                                                     break;
                                                     case 11:
                                                          carteAjouer[y].nom = NEUFTREFLE;
                                                     break;
                                                     case 12:
                                                          carteAjouer[y].nom = DIXTREFLE;
                                                     break;
                                   
                                        }          
                                        break;
                        
                       }
             
                       y++;
               }
     }
     
     //Ici nous allons remplacer les cartes qui n'ont pas été sélectionné par d'autres cartes déjà choisies
     if(action == SECONDTIRAGE)
     {
               int stirage;
               stirage = 0;
               
               while(stirage <= 4)
               {
                             if(carteAjouer[stirage].selection == 0)
                             {
                                                               carteAjouer[stirage].nom = carteAjouer[stirage+5].nom;
                                                               carteAjouer[stirage].valeur = carteAjouer[stirage+5].valeur;
                                                               carteAjouer[stirage].type = carteAjouer[stirage+5].type;
                             }
            
                             stirage++;
               }
     }  
     
}

void reconnaissancecombinaison() {  
             
     //variable de validation
     int paire = 0;
     int doublepaire = 0;
     int brelan = 0;
     int carre = 0;
     int flush = 0;
     int full = 0;
     int petitesuite = 0;
     int grossesuite = 0;
     
     int combitrouve = 0;
     //***********************
     
     //mise en ordre croissant
     int comparaison[5];
     int var1, var2, var3, var4;
     var1 = 0;
     var4 = 0;
     
     while(var1 <= 4)
     {
                comparaison[var1] = carteAjouer[var1].valeur;
                var1++;
     }
     
     for(var2 = 0; var2 <= 4; var2++)
     {
              for(var3 = 0; var3 <= 4; var3++)
              {
                       if(comparaison[var2] < comparaison[var3])
                       {
                                            var4 = comparaison[var2];
                                            comparaison[var2] = comparaison[var3];
                                            comparaison[var3] = var4;
                       }
              }
     }
                           
     //********************************************************
     
     //reconnaisance paire et double paire
     int x, y, tempo, nombredepaire, nombredepaireprovi;
     x = 0;
     y = 0;
     tempo = 21;
     nombredepaire = 0;
     nombredepaireprovi = 0;
     
     tempo = comparaison[0];
     
     while(x <= 4)
     {
             if(comparaison[x+1] == tempo)
             {
                              nombredepaireprovi++;
             }
             else
             {
                 if(nombredepaireprovi == 1)
                 {
                                       nombredepaire++;
                 }
                 tempo = comparaison[x+1];
                 nombredepaireprovi = 0;
             }      
             
             x++;
                        
     }
     
     if(nombredepaire == 1) {
     paire = 1;
     }    
     
     if(nombredepaire == 2) {
     doublepaire = 1;
     }
     //******************************************************
     
     //reconnaissance couleur
     if(carteAjouer[0].type == carteAjouer[1].type && carteAjouer[0].type == carteAjouer[1].type && carteAjouer[0].type == carteAjouer[2].type && carteAjouer[0].type == carteAjouer[3].type && carteAjouer[0].type == carteAjouer[4].type) {
     flush = 1;
     }        
     //******************************************************
     
     //reconnaissance suite
     int suite, compsuite, validation;
     suite = 0;
     validation = 0;
     
     compsuite = comparaison[0];
     
     while(suite <= 4)
     {
                 if(comparaison[suite] == compsuite)
                 {
                                       suite++;
                                       compsuite++;
                                       validation++;
                 }
                 else
                 {
                                       suite = 5;
                 }
     }
     
     if(validation == 5)
     {
         if(comparaison[0] == 8)
                           grossesuite = 1;
         else
                           petitesuite = 1;
     }
     if(validation == 4 && comparaison[4] == 13 && comparaison[0] == 0)
     {
                   petitesuite = 1;
     }
     //******************************************************
     
     //reconnaissance brelan (ou) carré
     int e, temp, egalite;
     e = 0;
     temp = 0;
     egalite = 0;
     
     while(e <= 4)
     {
             temp = comparaison[e];
             
             if(comparaison[e+1] == temp)
             {
                                 egalite++;

                                 if(egalite == 2)
                                 {
                                            brelan = 1;
                                 }
                                 
                                 if(egalite == 3)
                                 {
                                            carre = 1;
                                            brelan = 0;
                                 }
                                 
             }
             else
             {
                                 egalite = 0;
             }
             
             e++;
     }
     //******************************************************
     
     //affichage combinaison paire
     if(paire == 1 && brelan == 0 && carre == 0)
     {
              show_text(PAIRE);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         changerargent(CALCULDEGAIN, 0);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison double paire
     if(doublepaire == 1)
     {
              show_text(DBPAIRE);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         changerargent(CALCULDEGAIN, 1);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison brelan
     if(brelan == 1 && paire == 0)
     {
              show_text(BRELAN);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {   
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 2);
                         changerargent(MISEAZERO, 0);
                         passage = 1;   
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison carré
     if(carre == 1)
     {
              show_text(CARRE);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 8);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison full
     if(paire == 1 && brelan == 1)
     {
              show_text(FULL);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 5);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison flush (couleur)
     if(flush == 1 && petitesuite == 0 && grossesuite == 0)
     {
              show_text(FLUSH);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 4);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison quinte flush royale
     if(grossesuite == 1 && flush == 1)
     {
              show_text(QFLUSHR);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 20);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison quinte flush
     if(petitesuite == 1 && flush == 1)
     {
              show_text(QFLUSH);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
                         
                         changerargent(CALCULDEGAIN, 10);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage combinaison quinte
     if((petitesuite == 1 || grossesuite == 1) && flush == 0)
     {
              show_text(QUINTE);
              show_text(GAIN);
              show_text(GAINSOMME);
              
              if(passage == 0)
              {
                         if(checksonoption() == 1)
                         {
                                             jouer(SON_WHAOU);
                         }
              
                         changerargent(CALCULDEGAIN, 3);
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
              
              combitrouve = 1;
     }
     //******************************************************
     
     //affichage si aucune combinaison n'est trouvée
     if(combitrouve == 0)
     {
              show_text(NOTHING); 
              
              if(passage == 0)
              {  
                         if(checksonoption() == 1)
                         { 
                                             jouer(SON_NOCOMBI);
                         }
                         
                         changerargent(MISEAZERO, 0);
                         passage = 1;
              }
     }
     //******************************************************
     
     flip();
}

void selectioncarte(int carte) {
     
     if(carteAjouer[carte].selection == 0) 
     {
          carteAjouer[carte].selection = 1;
     }
     else
     {
          carteAjouer[carte].selection = 0;
     }
}

void changerargent(int action, int somme) {
     
     int temp = 0;
     int temp2 = 0;
     int gain = 0;
     int gainaffiche = 0;
     
     switch(action)
     {
                   case AUGMENTERMISE:
                        if(argent > 0)
                        {
                            argent -= somme;
                            mise += somme;
                            
                            if(checksonoption() == 1)
                            {
                                jouer(SON_PION);
                            }
                            
                            passage = 0;
                        }
                        else
                        {
                            argent = 0;
                        }
                        break;
                   case CALCULDEGAIN:
                        gainaffiche = mise * somme;
                        gain = mise + (mise * somme);
                        argent += gain;
                        sprintf(gainsomme, "%d", gainaffiche);
                        modify_text(GAINSOMME, gainsomme, NOIR, 1);
                        break;
                   case MISEAZERO:
                        mise = 0;
                        break;
                   case DEBUTPARTIE:
                        argent = 100;
                        mise = 0;
                        break;
                   case ANNULEMISE:
                        if(mise > 0)
                        {
                                temp = mise;
                                mise = 0;
                                argent += temp;
                        }
                        break;
                   case SAVE:
                        temp2 = mise;
                        mise = 0;
                        argent += temp2;
                        break;
     }  
     
     sprintf(argentsomme, "%d", argent);
     sprintf(misesomme, "%d", mise);
     
     modify_text(MISESOMME, misesomme, NOIR, 1);
     
     if(argent < 30)
         modify_text(ARGENTSOMME, argentsomme, ROUGE, 1);
     else if(argent > 100)
         modify_text(ARGENTSOMME, argentsomme, VERT, 1);
     else
         modify_text(ARGENTSOMME, argentsomme, NOIR, 1);
}

int checkargent() {
    
    int argentaretourner = 0;
    
    argentaretourner = argent;
    
    return argentaretourner;
}

int checkcartes(int car) {
    
    int c1, c2, c3, c4, c5;
    
    c1 = carteAjouer[0].nom;
    c2 = carteAjouer[1].nom;
    c3 = carteAjouer[2].nom;
    c4 = carteAjouer[3].nom;
    c5 = carteAjouer[4].nom;
    
    if(car == 1)
           return c1;
    
    if(car == 2)
           return c2;
    
    if(car == 3)
           return c3;
    
    if(car == 4)
           return c4;
    
    if(car == 5)
           return c5;
}

void deselection() {
     
     carteAjouer[0].selection = 0;
     carteAjouer[1].selection = 0;
     carteAjouer[2].selection = 0;
     carteAjouer[3].selection = 0;
     carteAjouer[4].selection = 0;
}
