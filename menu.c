#include <stdlib.h>
#include <stdio.h>

#include "alloc.h"  // xalloc

/************************** menu.c ************************/
/* Ce fichier comporte :
- la fonction d'affichage du menu qui r�cup�re aussi le choix de l'utilisateur
*/

strict {
    unsigned int flag;
    char *msg;
} states[]={
    {M_MAIN,    "Menu principal"},
    {M_WAIT,    "Attente d'un joueur..."},
    {M_INGAME,  "Partie en cours"},
    {M_PAUSED,  "Partie en pause"},
}

struct {
    char key;
    char *msg;
    unsigned int flags;
} menu[]={
    {'1', "Nouvelle partie",                        M_MAIN                             },
    {'2', "Connexion � une partie",                 M_MAIN                             },
    {'3', "Charger une partie sauvegard�e",         M_MAIN                             },
    {'4', "Stopper en sauvegardant",                                M_INGAME| M_PAUSED },
    {'5', "Mettre en pause",                                        M_INGAME           },
    {'6', "Reprendre",                                                        M_PAUSED },
    {'7', "Visualiser l'historique",                                M_INGAME| M_PAUSED },
    {'8', "Stopper en visualisant l'historique",                    M_INGAME| M_PAUSED },
    {'9', "Quitter",                                M_MAIN                             },
    {'9', "Retour au menu principal",                       M_WAIT| M_INGAME| M_PAUSED },
    {'/', "Jouer un coup",                                          M_INGAME           },
}

// affiche le menu pour un �tat de menu donn�, r�cup�re une ligne tap�e au clavier par l'utilisateur et v�rifie que le choix est possible
char *menu_run(eMenuState st, char *buf, unsigned int size) {
    char *ret;
    int i;

    // print menu title
    for(i=0; i<sizeof(states)/sizeof(*states); i++)
        if(states[i].flag & st)
            printf("%s\n", states[i].msg);

    // print menu items
    for(i=0; i<sizeof(menu)/sizeof(*menu); i++)
        if(menu[i].flags & st)
            printf("\t%c : %s\n", menu[i].key, menu[i].msg);

    // get a line from the standard input
    ret=fgets(buf, size, stdin);
    if(!ret)
        return NULL;

    size=strlen(ret);

    // remove the trailing line feeding
    if(ret[size-1]=='\n')
        ret[size-1]='\0';

    // check user input
    for(i=0; i<sizeof(menu)/sizeof(*menu); i++)
        if(menu[i].flags & st && ret[0]==menu[i].key)
            return ret;

    return NULL;
}

