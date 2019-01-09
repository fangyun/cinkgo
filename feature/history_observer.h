#ifndef CINKGO_FEATURE_HISTORY_OBSERVER_H_
#define CINKGO_FEATURE_HISTORY_OBSERVER_H_

#include "../board.h"

typedef struct{
	board_t* board;
}history_observer_t;

history_observer_t* history_observer_new();

#endif /* CINKGO_FEATURE_HISTORY_OBSERVER_H_ */
