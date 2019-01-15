#ifndef CINKGO_BOARD_H_
#define CINKGO_BOARD_H_

#include "comparable.h"
#include "player_builder.h"
#include "coord.h"

typedef struct {
	int width;
	coord_t* coord;
} board_t;

board_t* board_new(player_builder_t* pb);
comparable_t* comparable_board_new(player_builder_t* pb);

#endif /* CINKGO_BOARD_H_ */
