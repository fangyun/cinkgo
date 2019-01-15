#include "chinese_final_scorer.h"
#include <stdlib.h>

chinese_final_scorer_t* chinese_final_scorer_new(board_t* board, float komi) {
	chinese_final_scorer_t* cps = malloc(sizeof(chinese_final_scorer_t));
	cps->board = board;
	cps->komi = komi;
	return cps;
}
