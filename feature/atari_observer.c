#include "atari_observer.h"
#include <stdlib.h>

atari_observer_t* atari_observer_new(board_t* board) {
	atari_observer_t* ao = malloc(sizeof(atari_observer_t));
	ao->board = board;
	return ao;
}
