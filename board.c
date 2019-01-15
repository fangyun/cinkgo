#include "board.h"
#include "util.h"
#include "comparable.h"
#include "coord_system.h"

board_statics_t board_statics = { .size = 0 };

board_t* board_new(engine_builder_t* pb) {
	board_t* b = malloc(sizeof(board_t));
	b->width = pb->board_size;
	return b;
}

comparable_t* comparable_board_new(engine_builder_t* pb) {
	comparable_t* c = malloc(sizeof(comparable_t));
	board_t* b = board_new(pb);
	c->data = b;
	c->type = T_BOARD;
	return c;
}

void board_clear(board_t* board){

}

void board_handicap(board_t* board, stone_t stone, FILE* file){

}

int board_play(board_t* board, point_t* p){
	return 0;
}

void board_print(board_t* board, FILE* file){

}

int board_size(board_t* board){
	return board->width;
}

int real_board_size(board_t* board){
	return board->width;
}
