#include "escape_suggester.h"
#include <stdlib.h>

escape_suggester_t* escape_suggester_new(board_t* board, atari_observer_t* atari_observer, int bias) {
	escape_suggester_t* es = malloc(sizeof(escape_suggester_t));
	es->board = board;
	es->atari_observer = atari_observer;
	es->bias = bias;
	return es;
}
