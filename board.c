#include "board.h"
#include "util.h"
#include "coord.h"
#include "comparable.h"

board_t* board_new(player_builder_t* pb) {
	board_t* b = malloc(sizeof(board_t));
	b->width = pb->board_size;
	b->coord = coord_new(pb);
	return b;
}

comparable_t* comparable_board_new(player_builder_t* pb) {
	comparable_t* c = malloc(sizeof(comparable_t));
	board_t* b = board_new(pb);
	c->data = b;
	c->type = BOARD;
	return c;
}
