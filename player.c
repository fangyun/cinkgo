#define G_LOG_DOMAIN "player"
#include <stdlib.h>
#include <glib.h>
#include <stdbool.h>
#include "player.h"

player_t* player_new(int threads, copyable_struct_t* stuff) {
	player_t* p = malloc(sizeof(player_t));
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

player_t* player_build(player_builder_t* pb, copyable_struct_t* cs) {
	g_debug("begin build player");
	player_t* p = player_new(pb->threads, cs);
	g_debug("begin build transposition table");
	transposition_table_t* table = transposition_table_new(pb->memory, simple_search_node_new((coord_system_t*) NULL),(coord_system_t*) NULL);
	return p;
}

void player_done(player_t* player){

}

void time_left(player_t* e, int time, stone_t stone){

}

int player_accept_move(player_t* player, board_t* board, point_t* point){
//TODO
	g_debug("TODO");
	return 0;
}

void player_clear(player_t* player, board_t* board){
	//TODO
	g_debug("TODO");
}

void player_set_handicap(player_t* player){
	//TODO
	g_debug("TODO");
}
