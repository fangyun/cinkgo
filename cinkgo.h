#ifndef CINKGO_H_
#define CINKGO_H_
#include <stdio.h>
#include <glib.h>
#include "player.h"
#include "player_builder.h"

#define OPT_BIASDELAY   256
#define OPT_BOARDSIZE   257
#define OPT_NOBOOK      258
#define OPT_KOMI 259
#define OPT_NOLGRF2 260
#define OPT_MEMORY      261
#define OPT_MSEC    262
#define OPT_PONDER        263
#define OPT_NORAVE      264
#define OPT_SHAPE_BIAS 265
#define OPT_SHAPE_PATTERN_SIZE 266
#define OPT_SHAPE_SCALING_FACTOR 267
#define OPT_THREADS 268

typedef struct {
	int command_id;
	char* command_line_args;
	GList* known_commands;
	FILE* log;
	player_t* player;
	player_builder_t* player_builder;
	board_t* board;
} cinkgo_t;

cinkgo_t* cinkgo_new();
void cinkgo_done();

extern comparable_new_t comparable_new[TYPE_MAX];

#endif /* CINKGO_H_ */
