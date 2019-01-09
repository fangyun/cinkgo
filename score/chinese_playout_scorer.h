#ifndef CINKGO_SCORE_CHINESE_PLAYOUT_SCORER_H_
#define CINKGO_SCORE_CHINESE_PLAYOUT_SCORER_H_

#include "../board.h"

typedef struct{
	board_t* board;
	double komi;
}chinese_playout_scorer_t;

chinese_playout_scorer_t* chinese_playout_scorer_new();

#endif /* CINKGO_SCORE_CHINESE_PLAYOUT_SCORER_H_ */
