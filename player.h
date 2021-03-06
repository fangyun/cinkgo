#ifndef CINKGO_PLAYER_H_
#define CINKGO_PLAYER_H_

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
#include "board.h"
#include "stone.h"

typedef struct {
	history_observer_t* history_observer;
	chinese_final_scorer_t* scorer;
	mc_runnable_t** runnables;
	time_descender_t* descender;
	tree_updater_t* updater;
	opening_book_t* book;
	bool time_left_was_sent;
} player_t;

player_t* player_build(player_builder_t* pb, copyable_struct_t* cs);
player_t* player_new(int threads, copyable_struct_t* stuff);
void player_clear(player_t* player, board_t* board);
void player_done(player_t* p);
void time_left(player_t* p, int time, stone_t stone);
int player_accept_move(player_t* player, board_t* board, point_t* point);
void player_set_handicap(player_t* player);
point_t* player_best_move();
#endif /* CINKGO_PLAYER_H_ */
