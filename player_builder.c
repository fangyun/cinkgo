
#define DEBUG
#include <stdio.h>
#include "player_builder.h"
#include "util.h"
#include "debug.h"
#include "mcts/copyable_struct.h"
#include "mcts/simple_search_node.h"
#include "mcts/transposition_table.h"

player_builder_t* player_builder_new() {
	player_builder_t* pb = malloc(sizeof(player_builder_t));
	pb->bias_delay = 800;
	pb->komi = 7.5;
	pb->threads = 2;
	pb->memory = 1024;
	pb->msec = 1000;
	pb->board_size = 19;
	pb->ponder = false;
	pb->book = true;
	pb->manager_type = "uniform";
	pb->lgrf2 = true;
	pb->rave = true;
	pb->shape_scaling_factor = .95f;
	pb->shape_pattern_size = 5;
	pb->shape_bias = 20;
	return pb;
}
