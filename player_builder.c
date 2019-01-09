#define DEBUG
#include <stdio.h>
#include "player.h"
#include "player_builder.h"
#include "util.h"
#include "debug.h"

player_builder_t* player_builder_init(){
	player_builder_t* pb = calloc2(1,sizeof(player_builder_t));
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
	pb->build=player_builder_build;
	return pb;
}

player_t* player_builder_build(){
	if(DEBUGL(1)){
		fprintf(stderr,"开始构建棋手");
	}
	player_t* p = calloc2(1,sizeof(player_t));
	return p;
}
