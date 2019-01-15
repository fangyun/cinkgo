#include <ctype.h>
#include "stone.h"

char * stone2str(stone_t s) {
	switch (s) {
	case S_BLACK:
		return "black";
	case S_WHITE:
		return "white";
	default:
		return "none";
	}
}

stone_t str2stone(char *str) {
	switch (tolower(*str)) {
	case 'b':
		return S_BLACK;
	case 'w':
		return S_WHITE;
	default:
		return S_NONE;
	}
}
