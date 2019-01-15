#ifndef CINKGO_POINT_H_
#define CINKGO_POINT_H_

#include "stone.h"
typedef int coord_t;

typedef struct {
	stone_t stone;
	coord_t coord;
} point_t;

#endif /* CINKGO_POINT_H_ */
