#ifndef CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_
#define CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_
#include "../board.h"

typedef struct {
	board_t* board;
	double komi;
} chinese_final_scorer_t;

chinese_final_scorer_t* chinese_final_scorer_new(board_t* board, double komi);

#endif /* CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_ */
