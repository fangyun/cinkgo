#include "engine.h"

#include <stdlib.h>
#include <glib.h>
#include <stdbool.h>

engine_t* engine_new(int threads, copyable_struct_t* stuff) {
	engine_t* p = malloc(sizeof(engine_t));
	copyable_struct_t* copy = copyable_struct_copy(stuff);
	p->history_observer =(history_observer_t*) copyable_struct_get(copy, T_HISTORY_OBSERVER);
	p->scorer = (chinese_final_scorer_t*)copyable_struct_get(copy, T_SCORER);
	p->runnables = calloc(threads, sizeof(mc_runnable_t));
	p->descender = NULL;
	p->updater = NULL;
	p->book = NULL;
	p->time_left_was_sent = false;
	return p;
}

engine_t* engine_builder_build(engine_builder_t* pb, copyable_struct_t* cs) {
	g_debug("begin build player");
	engine_t* p = engine_new(pb->threads, cs);
	g_debug("begin build transposition table");
	transposition_table_t* table = transposition_table_new(pb->memory, simple_search_node_new((coord_system_t*) NULL),(coord_system_t*) NULL);
	return p;
}

void engine_done(engine_t* player){

}

void time_left(engine_t* e, int time, stone_t stone){

}
