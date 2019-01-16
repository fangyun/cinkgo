#include "history_observer.h"
#include "../util.h"

history_observer_t* history_observer_new(board_t* board){
	history_observer_t* ho=malloc(sizeof(history_observer_t));
	ho->board=board;
	return ho;
}
