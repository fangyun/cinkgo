#include "player.h"
#include <stdlib.h>
#include <glib.h>

player_t* player_new(int threads, copyable_struct_t* stuff) {
	player_t* p = malloc(sizeof(player_t));
	copyable_struct_t* copy = copyable_struct_copy(stuff);
	p->board = NULL;
	copyable_struct_get(copy->contents, p->board);
	p->coord = p->board->coord;
	p->history_observer = NULL;
	copyable_struct_get(copy->contents, p->history_observer);
	p->scorer = NULL;
	copyable_struct_get(copy->contents, p->scorer);
	p->runnables = malloc(sizeof(mc_runnable_t) * threads);
	p->descender = NULL;
	p->updater = NULL;
	p->book = NULL;
	p->time_left_was_sent = false;
	return p;
}
