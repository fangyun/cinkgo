#ifndef CINKGO_H_
#define CINKGO_H_

#include "player_builder.h"

typedef struct{
	int command_id;
	char* command_line_args;
	char* known_commands;
	FILE* in;
	FILE* out;
	FILE* log;
	struct player_t player;
	player_builder_t player_builder;
} cinkgo_t;

cinkgo_t cinkgo_init();

#endif /* CINKGO_H_ */
