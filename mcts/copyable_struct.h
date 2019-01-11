#ifndef CINKGO_MCTS_COPYABLE_STRUCT_H_
#define CINKGO_MCTS_COPYABLE_STRUCT_H_

#include <glib.h>

typedef struct {
	GList* contents;
} copyable_struct_t;

#define copyable_struct_get(list, pointer) {\
	guint length = g_list_length(list); \
	for (guint i = 0; i < length; i++) { \
		if (__builtin_types_compatible_p(typeof(g_list_nth_data(list, i)), typeof(pointer))) { \
			pointer = g_list_nth_data(list, i); \
		} \
	}\
}

copyable_struct_t* copyable_struct_new();
copyable_struct_t* copyable_struct_copy(copyable_struct_t* stuff);
copyable_struct_t* build_basic_parts(int width, double komi);
copyable_struct_t* build_use_with_bias(int width, double komi);

#endif /* CINKGO_MCTS_COPYABLE_STRUCT_H_ */
