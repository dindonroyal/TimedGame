#ifndef _GAME_H
#define _GAME_H

// this is where we handle the game

#include <string.h> // strcpy
#include <stdlib.h> // free
#include <time.h>   // time_t

#include "list.h"   // LIST, list_*

typedef enum {
    P_1=0,
    P_2=1
} ePlayer;

typedef enum {
    GS_INIT,    // initial state
    GS_TURN,    // turn in progress (see ePlayer to know which player turn it is)
    GS_WIN      // a player won (see ePlayer to know which one won)
} eGameState;

typedef enum {
    T_OK,
    T_INVALID,
    T_WIN
} eTurnTypes;

typedef struct {    // define a turn of the game
    ePlayer player;

    eTurnTypes type;

    time_t t_remaining;
} sGameTurn;

typedef struct {
    char gamename[64];  // game name
    char playername[2][9];  // players names
    ePlayer firstplayer;    // the player starting to play
    time_t t_total;
    time_t t_turn;
} sGameConf;

typedef struct {
    sGameConf conf; // configuration of the game

    eGameState state;   // current state of the game
    ePlayer player, me;    // current player, who i am
    time_t t_remaining;

    LIST *turns;    // list of game turns
} sGame;

// new game from scratch
sGame *     game_new                (sGame *g, const char *name);
char *      game_get_filepath       (const sGame *g);

// game from/to .histo file
LIST *      game_histo_getlist      ();   // get list of histo files in /tmp
// LIST *   game_histo_destroylist  (LIST *l);

int         game_histo_check        (char *filepath);
int         game_histo_load         (sGame *g, const char *name);
int         game_histo_save         (const sGame *g);

// manage a game
int         game_playturn           (sGame *g, const sGameTurn *t);

// destroy game
// void     game_destroy            (sGame *g)


// static functions declarations:
// game configuration
static inline
sGameConf *     game_get_conf           (sGame *g, sGameConf *c) { if(c) { memcpy(c, &g->conf, sizeof(*c)); return c; } else return &g->conf; }
static inline
void            game_set_conf           (sGame *g, sGameConf *c) { memcpy(&g->conf, c, sizeof(*c)); }

// game state
static inline
ePlayer         game_get_me             (sGame *g) { return g->me; }
static inline
void            game_set_me             (sGame *g, ePlayer p) { g->me=p; }
static inline
eGameState      game_get_state          (sGame *g) { return g->state; }
static inline
ePlayer         game_get_player         (sGame *g) { return g->player; }
static inline
void            game_set_player         (sGame *g, ePlayer p) { g->player=p; }
static inline
time_t          game_get_remainingtime  (sGame *g) { return g->t_remaining; }
static inline
void            game_set_remainingtime  (sGame *g, time_t t) { g->t_remaining=t; }

static inline
LIST *          game_histo_destroylist  (LIST *l) {
    return list_destroy_full(l, (free_handler)free);
}
static inline
void            game_destroy            (sGame *g) {
    g->turns=list_destroy_full(g->turns, (free_handler)free);   // free the turns stack

    g->state=GS_INIT;
}

#endif

