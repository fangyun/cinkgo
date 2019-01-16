#ifndef CINKGO_COMPARABLE_H_
#define CINKGO_COMPARABLE_H_

#include "player_builder.h"

typedef enum {
	T_BOARD, T_COORD, T_HISTORY_OBSERVER, T_SCORER, TYPE_MAX
} type_t;

typedef struct {
	type_t type;
	void* data;
} comparable_t;

typedef comparable_t* (*comparable_new_t)(player_builder_t* pb);

#endif /* CINKGO_COMPARABLE_H_ */
