#ifndef CINKGO_PLAYER_H_
#define CINKGO_PLAYER_H_

#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN "player"

#include <stdbool.h>
#include "mcts/copyable_struct.h"
#include "mcts/time_descender.h"
#include "mcts/tree_updater.h"
#include "mcts/mc_runnable.h"
#include "feature/history_observer.h"
#include "score/chinese_final_scorer.h"
#include "book/opening_book.h"
#include "player_builder.h"
#include "mcts/transposition_table.h"

typedef struct {
	history_observer_t* history_observer;
	chinese_final_scorer_t* scorer;
	mc_runnable_t** runnables;
	time_descender_t* descender;
	tree_updater_t* updater;;
	opening_book_t* book;
	bool time_left_was_sent;
} player_t;

player_t* player_builder_build(player_builder_t* pb);
player_t* player_new(int threads, copyable_struct_t* stuff);
#endif /* CINKGO_PLAYER_H_ */
