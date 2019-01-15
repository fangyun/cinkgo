#ifndef CINKGO_ENGINE_BUILDER_H_
#define CINKGO_ENGINE_BUILDER_H_

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
} engine_builder_t;

engine_builder_t* engine_builder_new();

#endif /* CINKGO_ENGINE_BUILDER_H_ */
