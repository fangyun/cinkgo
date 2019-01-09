#ifndef CINKGO_FEATURE_ESCAPE_SUGGESTER_H_
#define CINKGO_FEATURE_ESCAPE_SUGGESTER_H_

#include "atari_observer.h"
#include "../board.h"

typedef struct {
	board_t* board;
	atari_observer_t* atari_observer;
	int bias;
} escape_suggester_t;

escape_suggester_t* escape_suggester_new(board_t* board, atari_observer_t* atari_observer, int bias);

#endif /* CINKGO_FEATURE_ESCAPE_SUGGESTER_H_ */
