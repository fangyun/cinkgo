#define DEBUG
#include <stdio.h>
#include "player.h"
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

player_t* player_builder_build(player_builder_t* pb) {
	info("开始构建棋手");
	copyable_struct_t* cs = build_use_with_bias(pb->board_size, pb->komi);
	player_t* p = player_new(pb->threads, cs);
	board_t* b = p->board;
	coord_t* c = b->coord;
	info("创建转换表");
	transposition_table_t* table = transposition_table_new(pb->memory, simple_search_node_new(c), c);
	return p;
}
