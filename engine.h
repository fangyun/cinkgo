#ifndef CINKGO_PLAYER_H_
#define CINKGO_PLAYER_H_

#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN "engine"

#include <stdbool.h>
#include "mcts/copyable_struct.h"
#include "mcts/time_descender.h"
#include "mcts/tree_updater.h"
#include "mcts/mc_runnable.h"
#include "feature/history_observer.h"
#include "score/chinese_final_scorer.h"
#include "book/opening_book.h"
#include "engine_builder.h"
#include "mcts/transposition_table.h"
#include "board.h"
#include "stone.h"

typedef short (*engine_genmove_t)(struct _engine_t *e, board_t *b, stone_t color, bool pass_all_alive);

struct _engine_t {
	history_observer_t* history_observer;
	chinese_final_scorer_t* scorer;
	mc_runnable_t** runnables;
	time_descender_t* descender;
	tree_updater_t* updater;;
	opening_book_t* book;
	bool time_left_was_sent;
	engine_genmove_t  genmove;
};
typedef struct _engine_t engine_t;

engine_t* engine_builder_build(engine_builder_t* pb, copyable_struct_t* cs);
engine_t* engine_new(int threads, copyable_struct_t* stuff);
void engine_done(engine_t* e);
void time_left(engine_t* e, int time, stone_t stone);
#endif /* CINKGO_PLAYER_H_ */
