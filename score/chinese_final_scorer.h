#ifndef CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_
#define CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_
#include "../board.h"

typedef struct {
	board_t* board;
	float komi;
} chinese_final_scorer_t;

chinese_final_scorer_t* chinese_final_scorer_new(player_builder_t* pb, board_t* board);
double final_score(chinese_final_scorer_t* scorer);

#endif /* CINKGO_FEATURE_CHINESE_FINAL_SCORER_H_ */
