#ifndef CINKGO_MCTS_COPYABLE_STRUCT_H_
#define CINKGO_MCTS_COPYABLE_STRUCT_H_

#define _GNU_SOURCE 1

#include <glib.h>

typedef struct {
	GList* contents;
} copyable_struct_t;

copyable_struct_t* copyable_struct_new();
static copyable_struct_t* basic_parts(int width, double komi);

#endif /* CINKGO_MCTS_COPYABLE_STRUCT_H_ */
