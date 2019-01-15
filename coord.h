#ifndef CINKGO_COORD_H_
#define CINKGO_COORD_H_

#include "comparable.h"
#include "player_builder.h"

typedef struct {
	int width;
} coord_t;

coord_t* coord_new(player_builder_t* pb);
comparable_t* comparable_coord_new(player_builder_t* pb);

#endif /* CINKGO_COORD_H_ */
