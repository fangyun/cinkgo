#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "debug.h"
#include "engine.h"
#include "move.h"
#include "engines/patternplay.h"
#include "pattern.h"
#include "patternsp.h"
#include "patternprob.h"
#include "random.h"

struct engine *
engine_patternplay_init(char *arg, struct board *b)
{
	struct patternplay *pp = patternplay_state_init(arg);
	struct engine *e = calloc2(1, sizeof(struct engine));
	e->name = "PatternPlay Engine";
	e->comment = "I select moves blindly according to learned patterns. I won't pass as long as there is a place on the board where I can play. When we both pass, I will consider all the stones on the board alive.";
	e->genmove = patternplay_genmove;
	e->best_moves = patternplay_best_moves;
	e->evaluate = patternplay_evaluate;
	e->data = pp;

	return e;
}
