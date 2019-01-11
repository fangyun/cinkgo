#ifndef CINKGO_BOARD_H_
#define CINKGO_BOARD_H_

#include "coord.h"

typedef struct{
	int width;
	coord_t* coord;
}board_t;

board_t* board_new();

#endif /* CINKGO_BOARD_H_ */
