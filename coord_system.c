#include "coord_system.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

const int NO_POINT = 0;
const int PASS = -1;
const int RESIGN = -2;
const char* PASS_STR = "PASS";
const char* RESIGN_STR = "RESIGN";
static char alphabet[] = "abcdefghjklmnopqrstuvwxyz";

coord_system_t* coord_system_new(player_builder_t* pb) {
	coord_system_t* c = malloc(sizeof(coord_system_t));
	c->width = pb->board_size;
	return c;
}

const char * coord2bstr(char *buf, coord_t c, int boardsize) {
	if (is_pass(c)) {
		return PASS_STR;
	} else if (is_resign(c)) {
		return RESIGN_STR;
	} else {
		/* Some GTP servers are broken and won't grok lowercase coords */
		snprintf(buf, 4, "%c%u", toupper(alphabet[coord_x(c, boardsize) - 1]), coord_y(c, boardsize));
		return buf;
	}
}

/* Return coordinate in dynamically allocated buffer. */
const char * coord2str(coord_t c, int boardsize) {
	char buf[256];
	return strdup(coord2bstr(buf, c, boardsize));
}

/* Return coordinate in statically allocated buffer, with some backlog for
 * multiple independent invocations. Useful for debugging. */
const char * coord2sstr(coord_t c, int boardsize) {
	static char *b;
	static char bl[10][4];
	static int bi;
	b = bl[bi];
	bi = (bi + 1) % 10;
	return coord2bstr(b, c, boardsize);
}

/** 行r列c的short值形式. */
coord_t coord(int r, int c, int boardsize) {
	return (r + 1) * (boardsize + 1) + (c + 1);
}

/**
 * 返回使用标签描述的short值形式，例如可能的值有 "A5", "b3", or "PASS".
 */
coord_t str2coord(char *str, int boardsize) {
	if (!strcasecmp(str, PASS_STR))
		return PASS;
	if (!strcasecmp(str, RESIGN_STR))
		return RESIGN;

	int r = atoi(str + 1);
	r = boardsize - r;
	int c;
	char letter = tolower(str[0]);
	if (letter <= 'h') {
		c = letter - 'a';
	} else {
		c = letter - 'b';
	}
	return coord(r, c, boardsize);
}

int coord_x(coord_t c, int boardsize) {
	return c % (boardsize + 1) - 1;
}
int coord_y(coord_t c, int boardsize) {
	return c / (boardsize + 1) - 1;
}
