#ifndef PLAYER_BUILDER_H_
#define PLAYER_BUILDER_H_

#include <stdbool.h>

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
} player_builder_t;

player_t player_builder_build();

#endif /* PLAYER_BUILDER_H_ */
