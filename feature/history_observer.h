#ifndef CINKGO_FEATURE_HISTORY_OBSERVER_H_
#define CINKGO_FEATURE_HISTORY_OBSERVER_H_

#include "../board.h"
#include "../comparable.h"

typedef struct {
	board_t* board;
	type_t type;
} history_observer_t;

history_observer_t* history_observer_new(player_builder_t* pb);
comparable_t* comparable_history_observer_new(player_builder_t* pb);

#endif /* CINKGO_FEATURE_HISTORY_OBSERVER_H_ */
