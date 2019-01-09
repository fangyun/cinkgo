#include <stdlib.h>
#include "stone_count_observer.h"

stone_count_observer_t* stone_count_observer_new(board_t* board, chinese_playout_scorer_t* scorer) {
	stone_count_observer_t* s = malloc(sizeof(stone_count_observer_t));
	return s;
}
