#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "board.h"
#include "engine.h"
#include "move.h"
#include "../joseki.h"
#include "playout/moggy.h"
#include "playout/light.h"
#include "engines/montecarlo.h"
#include "playout.h"
#include "timeinfo.h"

struct engine *
engine_montecarlo_init(char *arg, struct board *b)
{
	struct montecarlo *mc = montecarlo_state_init(arg, b);
	struct engine *e = calloc2(1, sizeof(struct engine));
	e->name = "MonteCarlo";
	e->comment = "I'm playing in Monte Carlo. When we both pass, I will consider all the stones on the board alive. If you are reading this, write 'yes'. Please bear with me at the game end, I need to fill the whole board; if you help me, we will both be happier. Filling the board will not lose points (NZ rules).";
	e->genmove = montecarlo_genmove;
	e->done = montecarlo_done;
	e->data = mc;

	return e;
}
