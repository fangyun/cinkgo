#include "simple_search_node.h"
#include "../coord_system.h"
#include <stdlib.h>

simple_search_node_t* simple_search_node_new(coord_system_t* coord) {
	simple_search_node_t* ssn = malloc(sizeof(simple_search_node_t));
	return ssn;
}
