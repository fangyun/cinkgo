#include "coord.h"
#include <stdlib.h>

coord_t* coord_new(player_builder_t* pb) {
	coord_t* c = malloc(sizeof(coord_t));
	c->width = pb->board_size;
	return c;
}

comparable_t* comparable_coord_new(player_builder_t* pb) {
	comparable_t* c = malloc(sizeof(comparable_t));
	coord_t* co = coord_new(pb);
	c->data = co;
	c->type = COORD;
	return c;
}
