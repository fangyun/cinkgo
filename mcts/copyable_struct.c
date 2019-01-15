#include "copyable_struct.h"
#include "../board.h"
#include "../feature/history_observer.h"
#include "../feature/stone_count_observer.h"
#include "../score/chinese_final_scorer.h"
#include "../score/chinese_playout_scorer.h"
#include "../feature/escape_suggester.h"
#include "../feature/atari_observer.h"
#include <stdlib.h>
#include <string.h>

copyable_struct_t* copyable_struct_new() {
	copyable_struct_t* cs = calloc(1, sizeof(copyable_struct_t));
	return cs;
}

copyable_struct_t* copyable_struct_copy(copyable_struct_t* stuff) {
	copyable_struct_t* cs = calloc(1, sizeof(copyable_struct_t));
	memcpy(cs, stuff, sizeof(copyable_struct_t));
	return cs;
}

copyable_struct_t* build_basic_parts(player_builder_t* pb) {
	copyable_struct_t* cs = copyable_struct_new();
	board_t* board = board_new(pb);
	cs->contents = g_list_append(cs->contents, board);
	chinese_playout_scorer_t* scorer = chinese_playout_scorer_new(board, pb->komi);
	cs->contents = g_list_append(cs->contents, scorer);
	cs->contents = g_list_append(cs->contents, stone_count_observer_new(board, scorer));
	cs->contents = g_list_append(cs->contents, history_observer_new(board));
	cs->contents = g_list_append(cs->contents, chinese_final_scorer_new(board, pb->komi));
	return cs;
}

copyable_struct_t* build_use_with_bias(player_builder_t* pb) {
	copyable_struct_t* base = build_basic_parts(pb);
	board_t* board = NULL;
	//copyable_struct_get(base->contents, board);
	atari_observer_t* ao = atari_observer_new(board);
	escape_suggester_t* escape = escape_suggester_new(board, ao, 20);
	base->contents = g_list_append(base->contents, escape);
	return base;
}

