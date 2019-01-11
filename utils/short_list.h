#ifndef CINKGO_UTIL_SHORT_LIST_H_
#define CINKGO_UTIL_SHORT_LIST_H_

#include <stdbool.h>

typedef struct {
	int size;
	short* data;
} short_list_t;

void short_list_init(short_list_t* list, int capacity);
void short_list_add(short_list_t* list, short key);
bool short_list_contains(short_list_t* list, short key);
void short_list_add_if_not_present(short_list_t* list, short key);
int short_list_capacity(short_list_t* list);

#endif /* CINKGO_UTIL_SHORT_LIST_H_ */
