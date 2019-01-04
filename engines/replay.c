#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#include "board.h"
#include "debug.h"
#include "engine.h"
#include "move.h"
#include "playout.h"
#include "../joseki.h"
#include "playout/light.h"
#include "playout/moggy.h"
#include "engines/replay.h"


struct engine *
engine_replay_init(char *arg, struct board *b)
{
	struct replay *r = replay_state_init(arg, b);
        /* TODO engine_done(), free policy */

	struct engine *e = calloc2(1, sizeof(struct engine));
	e->name = "PlayoutReplay";
	e->comment = "I select the most probable move from moggy playout policy";
	e->genmove = replay_genmove;
	e->best_moves = replay_best_moves;
	e->done = replay_done;
	e->data = r;

	return e;
}
