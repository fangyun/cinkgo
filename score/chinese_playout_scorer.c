#include "chinese_playout_scorer.h"

chinese_playout_scorer_t* chinese_playout_scorer_new(board_t* b, double komi) {
	chinese_playout_scorer_t* cps = calloc2(1, sizeof(chinese_playout_scorer_t));
	cps->board=b;
	cps->komi=komi;
	return cps;
}
