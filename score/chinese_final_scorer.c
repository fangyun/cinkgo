#include "chinese_final_scorer.h"
#include <stdlib.h>

chinese_final_scorer_t* chinese_final_scorer_new(player_builder_t* pb, board_t* board) {
	chinese_final_scorer_t* cps = malloc(sizeof(chinese_final_scorer_t));
	cps->board = board;
	cps->komi = pb->komi;
	return cps;
}

double final_score(chinese_final_scorer_t* scorer){
//TODO
	return 0;
}
