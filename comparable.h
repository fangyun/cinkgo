#ifndef CINKGO_COMPARABLE_H_
#define CINKGO_COMPARABLE_H_

#include "player_builder.h"
#include "board.h"

typedef enum {
	T_BOARD, T_HISTORY_OBSERVER, T_SCORER, TYPE_MAX
} type_t;

typedef struct {
	type_t type;
	void* data;
} comparable_t;

typedef comparable_t* (*comparable_new_t)(player_builder_t* pb,board_t* board);
comparable_t* comparable_board_new(player_builder_t* pb, board_t* board);
comparable_t* comparable_history_observer_new(player_builder_t* pb, board_t* board);
comparable_t* comparable_chinese_final_scorer_new(player_builder_t* pb, board_t* board);

#endif /* CINKGO_COMPARABLE_H_ */
