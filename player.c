#include "player.h"
#include <stdlib.h>
#include <glib.h>
#include <stdbool.h>

player_t* player_new(int threads, copyable_struct_t* stuff) {
	player_t* p = malloc(sizeof(player_t));
	copyable_struct_t* copy = copyable_struct_copy(stuff);
	p->history_observer = NULL;
	//copyable_struct_get(copy->contents, p->history_observer);
	p->scorer = NULL;
	//copyable_struct_get(copy->contents, p->scorer);
	p->runnables = malloc(sizeof(mc_runnable_t) * threads);
	p->descender = NULL;
	p->updater = NULL;
	p->book = NULL;
	p->time_left_was_sent = false;
	return p;
}

player_t* player_builder_build(player_builder_t* pb) {
	g_debug("begin build player");
	copyable_struct_t* cs = build_use_with_bias(pb);
	player_t* p = player_new(pb->threads, cs);
	g_debug("begin build transposition table");
	transposition_table_t* table = transposition_table_new(pb->memory, simple_search_node_new((coord_t*) NULL),(coord_t*) NULL);
	return p;
}
