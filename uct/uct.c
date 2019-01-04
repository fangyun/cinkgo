#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

#include "debug.h"
#include "board.h"
#include "gtp.h"
#include "chat.h"
#include "move.h"
#include "mq.h"
#include "joseki.h"
#include "playout.h"
#include "playout/moggy.h"
#include "playout/light.h"
#include "tactics/util.h"
#include "timeinfo.h"
#include "uct/dynkomi.h"
#include "uct/internal.h"
#include "uct/plugins.h"
#include "uct/prior.h"
#include "uct/search.h"
#include "uct/slave.h"
#include "uct/tree.h"
#include "uct/uct.h"
#include "uct/walk.h"
#include "dcnn.h"

struct engine *
engine_uct_init(char *arg, struct board *b)
{
	struct uct *u = uct_state_init(arg, b);
	struct engine *e = calloc2(1, sizeof(struct engine));
	e->name = "UCT";
	e->board_print = uct_board_print;
	e->notify_play = uct_notify_play;
	e->chat = uct_chat;
	e->undo = uct_undo;
	e->result = uct_result;
	e->genmove = uct_genmove;
#ifdef DISTRIBUTED
	e->genmoves = uct_genmoves;
	if (u->slave)
		e->notify = uct_notify;
#endif
	e->best_moves = uct_best_moves;
	e->evaluate = uct_evaluate;
	e->dead_group_list = uct_dead_group_list;
	e->stop = uct_stop;
	e->done = uct_done;
	e->ownermap = uct_ownermap;
	e->livegfx_hook = uct_livegfx_hook;
	e->data = u;

	const char banner[] = "If you believe you have won but I am still playing, "
		"please help me understand by capturing all dead stones. "
		"Anyone can send me 'winrate' in private chat to get my assessment of the position.";
	if (!u->banner) u->banner = "";
	e->comment = malloc2(sizeof(banner) + strlen(u->banner) + 1);
	sprintf(e->comment, "%s %s", banner, u->banner);

	return e;
}
