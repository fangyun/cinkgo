#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "engine.h"
#include "move.h"
#include "engines/random.h"

struct engine *
engine_random_init(char *arg, struct board *b)
{
	struct engine *e = calloc2(1, sizeof(struct engine));
	e->name = "RandomMove";
	e->comment = "I just make random moves. I won't pass as long as there is a place on the board where I can play. When we both pass, I will consider all the stones on the board alive.";
	e->genmove = random_genmove;

	if (arg)
		fprintf(stderr, "Random: I support no engine arguments\n");

	return e;
}
