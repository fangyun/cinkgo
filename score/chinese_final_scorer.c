#include "chinese_final_scorer.h"
#include <stdlib.h>

chinese_final_scorer_t* chinese_final_scorer_new(engine_builder_t* pb) {
	chinese_final_scorer_t* cps = malloc(sizeof(chinese_final_scorer_t));
	cps->board = board_new(pb);
	cps->komi = pb->komi;
	return cps;
}

comparable_t* comparable_chinese_final_scorer_new(engine_builder_t* pb){
	comparable_t* c = malloc(sizeof(comparable_t));
	chinese_final_scorer_t* cfs = chinese_final_scorer_new(pb);
	c->data = cfs;
	c->type = T_HISTORY_OBSERVER;
	return c;
}
