#ifndef CINKGO_MCTS_COPYABLE_STRUCT_H_
#define CINKGO_MCTS_COPYABLE_STRUCT_H_

#include <glib.h>
#include "../comparable.h"
#include "../player_builder.h"

typedef struct {
	GList* contents;
} copyable_struct_t;

copyable_struct_t* copyable_struct_new();
copyable_struct_t* copyable_struct_copy(copyable_struct_t* stuff);
copyable_struct_t* build_basic_parts(player_builder_t* eb);
copyable_struct_t* build_use_with_bias(player_builder_t* eb);
comparable_t* copyable_struct_get(copyable_struct_t* cs, type_t type);

#endif /* CINKGO_MCTS_COPYABLE_STRUCT_H_ */
