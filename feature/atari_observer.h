#ifndef CINKGO_FEATURE_ATARI_OBSERVER_H_
#define CINKGO_FEATURE_ATARI_OBSERVER_H_

#include "../board.h"

typedef struct {
	board_t* board;
} atari_observer_t;

atari_observer_t* atari_observer_new(board_t* board);

#endif /* CINKGO_FEATURE_ATARI_OBSERVER_H_ */
