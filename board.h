#ifndef CINKGO_BOARD_H_
#define CINKGO_BOARD_H_

#include "comparable.h"
#include "engine_builder.h"
#include "stone.h"
#include "point.h"
#include <stdio.h>
#include "thirdparty/hash.h"
#include <inttypes.h>

#define BOARD_MAX_SIZE 19
#define BOARD_MAX_COORDS  ((BOARD_MAX_SIZE+2) * (BOARD_MAX_SIZE+2) )
#define BOARD_MAX_MOVES (BOARD_MAX_SIZE * BOARD_MAX_SIZE)
#define BOARD_MAX_GROUPS (BOARD_MAX_SIZE * BOARD_MAX_SIZE * 2 / 3)

typedef struct {
	int width;
	float komi;
	int handicap;
} board_t;

typedef struct {
	int size;

	/* Iterator offsets for foreach_neighbor*() */
	int nei8[8], dnei[4];

	/* Coordinates zobrist hashes (black and white) */
	hash_t h[2][BOARD_MAX_COORDS];

	/* Cached information on x-y coordinates so that we avoid division. */
	uint8_t coord[BOARD_MAX_COORDS][2];
} board_statics_t;

board_t* board_new(engine_builder_t* pb);
comparable_t* comparable_board_new(engine_builder_t* pb);
void board_clear(board_t* board);
void board_handicap(board_t* board, stone_t stone, FILE* file);
int board_play(board_t* board, point_t* p);
void board_print(board_t* board, FILE* file);
int board_size(board_t* board);
int real_board_size(board_t* board);
#endif /* CINKGO_BOARD_H_ */
