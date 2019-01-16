#include "comparable.h"
#include <stdlib.h>
#include "player_builder.h"
#include "feature/history_observer.h"
#include "score/chinese_final_scorer.h"
#include "board.h"

comparable_t* comparable_board_new(player_builder_t* pb, board_t* ignore) {
	comparable_t* c = malloc(sizeof(comparable_t));
	board_t* b = board_new(pb);
	c->data = b;
	c->type = T_BOARD;
	return c;
}


comparable_t* comparable_history_observer_new(player_builder_t* pb, board_t* board){
	comparable_t* c = malloc(sizeof(comparable_t));
	history_observer_t* ho = history_observer_new(board);
	c->data = ho;
	c->type = T_HISTORY_OBSERVER;
	return c;
}

comparable_t* comparable_chinese_final_scorer_new(player_builder_t* pb, board_t* board){
	comparable_t* c = malloc(sizeof(comparable_t));
	chinese_final_scorer_t* cfs = chinese_final_scorer_new(pb,board);
	c->data = cfs;
	c->type = T_SCORER;
	return c;
}
