#include "transposition_table.h"
#include <stdlib.h>

transposition_table_t* transposition_table_new(int memory, simple_search_node_t* search_node, coord_system_t* c) {
	transposition_table_t* tt = malloc(sizeof(transposition_table_t));
	return tt;
}
