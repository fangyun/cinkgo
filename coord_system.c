#include "coord_system.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

const int NO_POINT = 0;
const int PASS = -1;
const int RESIGN = -2;
const char* PASS_STR = "PASS";
const char* RESIGN_STR = "resign";
static char atoz[] = "abcdefghjklmnopqrstuvwxyz";

coord_system_t* coord_system_new(player_builder_t* pb) {
	coord_system_t* c = malloc(sizeof(coord_system_t));
	c->width = pb->board_size;
	return c;
}

comparable_t* comparable_coord_new(player_builder_t* pb) {
	comparable_t* c = malloc(sizeof(comparable_t));
	coord_system_t* co = coord_system_new(pb);
	c->data = co;
	c->type = T_COORD;
	return c;
}

char * coord2bstr(char *buf, coord_t c, board_t *board) {
	if (is_pass(c)) {
		return PASS_STR;
	} else if (is_resign(c)) {
		return RESIGN_STR;
	} else {
		/* Some GTP servers are broken and won't grok lowercase coords */
		snprintf(buf, 4, "%c%u", toupper(atoz[coord_x(c, board) - 1]), coord_y(c, board));
		return buf;
	}
}

/* Return coordinate in dynamically allocated buffer. */
char * coord2str(coord_t c, board_t *board) {
	char buf[256];
	return strdup(coord2bstr(buf, c, board));
}

/* Return coordinate in statically allocated buffer, with some backlog for
 * multiple independent invocations. Useful for debugging. */
char * coord2sstr(coord_t c, board_t *board) {
	static char *b;
	static char bl[10][4];
	static int bi;
	b = bl[bi];
	bi = (bi + 1) % 10;
	return coord2bstr(b, c, board);
}

coord_t str2coord(char *str, int size) {
	if (!strcasecmp(str, PASS_STR))
		return PASS;
	if (!strcasecmp(str, RESIGN_STR))
		return RESIGN;

	char xc = tolower(str[0]);
	return xc - 'a' - (xc > 'i') + 1 + atoi(str + 1) * size;
}

/* Must match rotations in pthashes_init() */
coord_t rotate_coord(board_t *b, coord_t c, int rot) {
	assert(c != PASS);
	int size = real_board_size(b);
	int x = coord_x(c, b);
	int y = coord_y(c, b);

	if (rot & 1)
		y = size - y + 1;
	if (rot & 2)
		x = size - x + 1;
	if (rot & 4) {
		int tmp = x;
		x = size - y + 1;
		y = tmp;
	}
	return coord_xy(b, x, y);
}
