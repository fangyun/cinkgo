#include "board.h"
#include "util.h"

board_t* board_new(int width) {
	board_t* b = malloc(sizeof(board_t));
	b->width = width;
	return b;
}
