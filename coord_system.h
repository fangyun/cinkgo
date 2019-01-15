#ifndef CINKGO_COORD_SYSTEM_H_
#define CINKGO_COORD_SYSTEM_H_

#include "comparable.h"
#include "engine_builder.h"
#include "point.h"
#include "board.h"

extern const int NO_POINT;
extern const int PASS;
extern const int RESIGN;
extern const char* PASS_STR;
extern const char* RESIGN_STR;
extern board_statics_t board_statics;

#define is_pass(c)   (c == PASS)
#define is_resign(c) (c == RESIGN)
#define coord_xy(board, x, y) ((x) + (y) * board_size(board))
#define coord_x(c, b) (board_statics.coord[c][0])
#define coord_y(c, b) (board_statics.coord[c][1])
/* TODO: Smarter way to do this? */
#define coord_dx(c1, c2, b) (coord_x(c1, b) - coord_x(c2, b))
#define coord_dy(c1, c2, b) (coord_y(c1, b) - coord_y(c2, b))


typedef struct {
	int width;
} coord_system_t;


coord_system_t* coord_system_new(engine_builder_t* pb);
comparable_t* comparable_coord_new(engine_builder_t* pb);

#endif /* CINKGO_COORD_SYSTEM_H_ */