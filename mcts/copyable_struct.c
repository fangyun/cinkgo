#include <stdlib.h>
#include <string.h>
#include "copyable_struct.h"
#include "../cinkgo.h"
#include "../board.h"
#include "../feature/history_observer.h"
#include "../feature/stone_count_observer.h"
#include "../score/chinese_final_scorer.h"
#include "../score/chinese_playout_scorer.h"
#include "../feature/escape_suggester.h"
#include "../feature/atari_observer.h"
#include "../comparable.h"

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
	comparable_t* cb = comparable_new[T_BOARD](pb);
	cs->contents = g_list_append(cs->contents, cb);
	chinese_playout_scorer_t* scorer = chinese_playout_scorer_new(cb->data, pb->komi);
	cs->contents = g_list_append(cs->contents, scorer);
	cs->contents = g_list_append(cs->contents, stone_count_observer_new(cb->data, scorer));
	cs->contents = g_list_append(cs->contents, history_observer_new(cb->data));
	cs->contents = g_list_append(cs->contents, comparable_new[T_SCORER](pb));
	return cs;
}

comparable_t* copyable_struct_get(copyable_struct_t* cs, type_t type) {
	guint length = g_list_length(cs->contents);
	for (guint i = 0; i < length; i++) {
		comparable_t* c = (comparable_t*) g_list_nth_data(cs->contents, i);
		if (c->type == type) {
			return c;
		}
	}
	return NULL;
}

copyable_struct_t* build_use_with_bias(player_builder_t* eb) {
	copyable_struct_t* base = build_basic_parts(eb);
	comparable_t* cb = copyable_struct_get(base, T_BOARD);
	atari_observer_t* ao = atari_observer_new(cb->data);
	escape_suggester_t* escape = escape_suggester_new(cb->data, ao, 20);
	base->contents = g_list_append(base->contents, escape);
	return base;
}

