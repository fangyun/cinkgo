#include "copyable_struct.h"
#include "util.h"
#include "board.h"
#include "feature/history_observer.h"
#include "feature/stone_count_observer.h"
#include "score/chinese_final_scorer.h"
#include "score/chinese_playout_scorer.h"
#include "feature/escape_suggester.h"
#include "feature/atari_observer.h"

#define copyable_struct_get(cs,pointer) {\
	guint length = g_list_length(cs->contents); \
	for (guint i = 0; i < length; i++) { \
		if (__builtin_types_compatible_p(typeof(g_list_nth_data(cs->contents, i)), typeof(pointer))) { \
			pointer = g_list_nth_data(cs->contents, i); \
		} \
	}\
}

copyable_struct_t* copyable_struct_new() {
	copyable_struct_t* cs = malloc(sizeof(copyable_struct_t));
	return cs;
}

static copyable_struct_t* basic_parts(int width, double komi) {
	copyable_struct_t* cs = copyable_struct_new();
	board_t* board = board_new(width);
	g_list_append(cs->contents, board);
	chinese_playout_scorer_t* scorer = chinese_playout_scorer_new(board, komi);
	g_list_append(cs->contents, scorer);
	g_list_append(cs->contents, stone_count_observer_new(board, scorer));
	g_list_append(cs->contents, history_observer_new(board));
	g_list_append(cs->contents, chinese_final_scorer_new(board, komi));
	return cs;
}

static copyable_struct_t* use_with_bias(int width, double komi) {
	copyable_struct_t* base = basic_parts(width, komi);
	board_t* board = NULL;
	copyable_struct_get(base, board);
	atari_observer_t* ao = atari_observer_new(board);
	escape_suggester_t* escape = escape_suggester_new(board, ao, 20);
	g_list_append(base->contents, escape);
	return base;
}

