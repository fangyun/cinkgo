#include "history_observer.h"
#include "../util.h"

history_observer_t* history_observer_new(engine_builder_t* pb){
	history_observer_t* ho=malloc(sizeof(history_observer_t));
	ho->board=board_new(pb);
	return ho;
}

comparable_t* comparable_history_observer_new(engine_builder_t* pb){
	comparable_t* c = malloc(sizeof(comparable_t));
	history_observer_t* ho = history_observer_new(pb);
	c->data = ho;
	c->type = T_HISTORY_OBSERVER;
	return c;
}
