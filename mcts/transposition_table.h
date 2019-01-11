#ifndef CINKGO_MCTS_TRANSPOSITION_TABLE_H_
#define CINKGO_MCTS_TRANSPOSITION_TABLE_H_

#include "simple_search_node.h"
#include "../coord.h"

typedef struct {
	coord_t* coord;
} transposition_table_t;

transposition_table_t* transposition_table_new(int memory, simple_search_node_t* search_node, coord_t* c);

#endif /* CINKGO_MCTS_TRANSPOSITION_TABLE_H_ */
