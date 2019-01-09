#ifndef PLAYER_BUILDER_H_
#define PLAYER_BUILDER_H_

#include <stdbool.h>
#include "player.h"

typedef player_t* (*build_t)();

typedef struct{
	int bias_delay;
	int board_size;
	bool book;
	float komi;
	bool lgrf2;
	int memory;
	int msec;
	bool ponder;
	bool rave;
	int shape_bias;
	int shape_pattern_size;
	float shape_scaling_factor;
	int threads;
	char* manager_type;
	build_t build;
} player_builder_t;

player_t* player_builder_build();
player_builder_t* player_builder_init();

#endif /* PLAYER_BUILDER_H_ */
