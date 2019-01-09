#ifndef CINKGO_FEATURE_STONE_COUNT_OBSERVER_H_
#define CINKGO_FEATURE_STONE_COUNT_OBSERVER_H_

#include "../board.h"
#include "../score/chinese_playout_scorer.h"

typedef struct {

} stone_count_observer_t;

stone_count_observer_t* stone_count_observer_new(board_t* board, chinese_playout_scorer_t* scorer);

#endif /* CINKGO_FEATURE_STONE_COUNT_OBSERVER_H_ */
