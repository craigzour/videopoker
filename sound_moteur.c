/*##########################################
#                                          #
#             sound_moteur.c               #
#                                          #
#  JALON 2                    par Aurélien # 
#                                          #
# Ce fichier regroupe toutes les fonctions #
# du moteur audio.   .                     #
#                                          #
##########################################*/

#include <FMOD/fmod.h>

#include "ressources.h"
#include "sound_moteur.h"
#include "main.h"

void loadmusique ();

void musiquedefond();

void jouer (int continuer);

void modifiervolume(int volume);

void coupermusique();

void modifiermusique();

void sound_close ();


int etatmusique = 1;

FSOUND_SAMPLE *sonpion = NULL;
FSOUND_SAMPLE *soncartes = NULL;
FSOUND_SAMPLE *sonbouton = NULL;
FSOUND_SAMPLE *sontapis = NULL;
FSOUND_SAMPLE *sonapplaudissement = NULL;
FSOUND_SAMPLE *sonwhaou = NULL;
FSOUND_SAMPLE *sonnocombi = NULL;
FSOUND_SAMPLE *sonperdu = NULL;
FSOUND_STREAM *musique = NULL;
FSOUND_STREAM *musique2 = NULL;

void loadmusique (){

    FSOUND_Init (48000, 32, 0);
    
    sonpion = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/pion.wav", 0, 0, 0);
    
    soncartes = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/cartes.wav", 0, 0, 0);
    
    sonbouton = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/effetbouton.mp3", 0, 0, 0);
    
    sontapis = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/tapis.mp3", 0, 0, 0);
    
    sonapplaudissement = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/applaudissement.mp3", 0, 0, 0);
    
    sonwhaou = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/whaou.mp3", 0, 0, 0);
    
    sonnocombi = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/nocombi.mp3", 0, 0, 0);
    
    sonperdu = FSOUND_Sample_Load(FSOUND_FREE, "content/sons/perdu.mp3", 0, 0, 0);
    
    musique = FSOUND_Stream_Open("content/sons/pulpremix.ogg", FSOUND_LOOP_NORMAL, 0, 0);
    
    musique2 = FSOUND_Stream_Open("content/sons/pokerproj.mp3", FSOUND_LOOP_NORMAL, 0, 0);
}

void musiquedefond() {
     
     FSOUND_Stream_SetLoopCount(musique, -1); /* On active la répétition de la musique à l'infini */
     
     FSOUND_Stream_Play(FSOUND_FREE, musique); /* On joue la musique */
     
     FSOUND_SetVolume(FSOUND_ALL, 80); //On modifie le volume de la musique
}

void jouer (int continuer) {
     
int i;

switch (continuer)
    {
    case SON_PION:
        FSOUND_PlaySound (FSOUND_FREE, sonpion);
    break;
    case SON_CARTES:
        FSOUND_PlaySound (FSOUND_FREE, soncartes);
    break;
    case SON_BOUTON:
         FSOUND_PlaySound (FSOUND_FREE, sonbouton);
    break;
    case SON_TAPIS:
         FSOUND_PlaySound (FSOUND_FREE, sontapis);
    break;
    case SON_APPLAUDISSEMENT:
         FSOUND_PlaySound (FSOUND_FREE, sonapplaudissement);
    break;
    case SON_WHAOU:
         FSOUND_PlaySound (FSOUND_FREE, sonwhaou);
    break;
    case SON_NOCOMBI:
         FSOUND_PlaySound (FSOUND_FREE, sonnocombi);
    break;
    case SON_PERDU:
         FSOUND_PlaySound (FSOUND_FREE, sonperdu);
    break;
    }
}

void modifiervolume(int volume) {
     
     int musiquetest = checkmusiquechoisi();
     
     if(etatmusique == 0)
     {
                    if(musiquetest == 0)
                    {
                        FSOUND_Stream_SetLoopCount(musique, -1);
                        FSOUND_Stream_Play(FSOUND_FREE, musique);
                    }
                    
                    else
                    {
                        FSOUND_Stream_SetLoopCount(musique2, -1);
                        FSOUND_Stream_Play(FSOUND_FREE, musique2);
                    }
                    
                    etatmusique = 1;
     }
     
     FSOUND_SetVolume(FSOUND_ALL, volume);
}

void coupermusique() {
     
     int musiquetest = checkmusiquechoisi();
     
     if(musiquetest == 0)
     {
                FSOUND_Stream_Stop(musique);     
     }
     
     else
     {
                FSOUND_Stream_Stop(musique2);
     }
     
     etatmusique = 0;     
}

void modifiermusique() {
     
     int musiquetest = checkmusiquechoisi();
     
     if(musiquetest == 0)
     {
                    FSOUND_Stream_Stop(musique2);
                    FSOUND_Stream_SetLoopCount(musique, -1);
                    FSOUND_Stream_Play(FSOUND_FREE, musique);
                    FSOUND_SetVolume(FSOUND_ALL, 80);
     }
     
     else
     {
                    FSOUND_Stream_Stop(musique);
                    FSOUND_Stream_SetLoopCount(musique2, -1);
                    FSOUND_Stream_Play(FSOUND_FREE, musique2);
                    FSOUND_SetVolume(FSOUND_ALL, 80);
     }
}

void sound_close (){
     
    FSOUND_Sample_Free(sonpion);
    FSOUND_Sample_Free(soncartes);
    FSOUND_Sample_Free(sonbouton);
    FSOUND_Sample_Free(sontapis);
    FSOUND_Sample_Free(sonapplaudissement);
    FSOUND_Sample_Free(sonwhaou);
    FSOUND_Sample_Free(sonnocombi);
    FSOUND_Sample_Free(sonperdu);
    FSOUND_Stream_Close(musique);
    FSOUND_Stream_Close(musique2);
    FSOUND_Close();
} 

