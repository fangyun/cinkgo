#ifndef CINKGO_COORD_SYSTEM_H_
#define CINKGO_COORD_SYSTEM_H_

#include "point.h"
#include "player_builder.h"

extern const int NO_POINT;
extern const int PASS;
extern const int RESIGN;
extern const char* PASS_STR;
extern const char* RESIGN_STR;

#define is_pass(c)   (c == PASS)
#define is_resign(c) (c == RESIGN)
#define coord_xy(size, x, y) ((x) + (y) * (size))
#define coord_dx(c1, c2) (coord_x(c1) - coord_x(c2))
#define coord_dy(c1, c2) (coord_y(c1) - coord_y(c2))


typedef struct {
	int width;
} coord_system_t;


coord_system_t* coord_system_new(player_builder_t* pb);
const char * coord2bstr(char *buf, coord_t c, int boardsize);
const char * coord2str(coord_t c,int boardsize);
const char * coord2sstr(coord_t c,int boardsize);
coord_t coord(int r, int c, int boardsize);
coord_t str2coord(char *str, int boardsize);
int coord_x(coord_t c, int boardsize);
int coord_y(coord_t c, int boardsize);

#endif /* CINKGO_COORD_SYSTEM_H_ */
