#ifndef _MSGS_H
#define _MSGS_H

#include "game.h"   // sGame
#include "sigmsg.h" // MAX_SIGMSG_SZ

typedef enum {
    MSG_JOINGAME,
    MSG_CONFUPDATE,
    MSG_GAMETURN,
    MSG_ENDGAME
} eMsgsTypes;

typedef struct {
    eMsgsTypes type;

    char data[MAX_SIGMSG_SZ-sizeof(eMsgsTypes)];    // payload
} sMsg;

extern sMsg last_msg;
extern unsigned int last_msg_len;

int msg_init        (char *path, int msgflg, sGame *g);

int msg_send        (sMsg *msg, unsigned int datasz);
int msg_transfer    (sMsg *msg, unsigned int *datasz);
int msg_answer      (sMsg *msg, unsigned int datasz);

int msg_deinit      (int destroy);

#endif

