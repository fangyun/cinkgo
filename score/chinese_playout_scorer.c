#include "chinese_playout_scorer.h"
#include <stdlib.h>

chinese_playout_scorer_t* chinese_playout_scorer_new(board_t* b, double komi) {
	chinese_playout_scorer_t* cps = malloc(sizeof(chinese_playout_scorer_t));
	cps->board=b;
	cps->komi=komi;
	return cps;
}
