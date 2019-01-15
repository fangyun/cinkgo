#include "../utils/short_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../thirdparty/hash.h"
#include "../util.h"

void short_list_init(short_list_t* list, int capacity) {
	list->data = malloc(sizeof(short) * capacity);
	memset(list->data, 0, sizeof(short) * capacity);
	list->size = 0;
}

void short_list_add(short_list_t* list, short key) {
	list->data[list->size] = key;
	list->size++;
}

bool short_list_contains(short_list_t* list, short key) {
	for (int i = 0; i < list->size; i++) {
		if (list->data[i] == key) {
			return true;
		}
	}
	return false;
}

void short_list_add_if_not_present(short_list_t* list, short key) {
	if (!short_list_contains(list, key)) {
		short_list_add(list, key);
	}
}

int short_list_capacity(short_list_t* list) {
	return sizeof(list->data) / sizeof(short);
}

void short_list_clear(short_list_t* list) {
	short_list_init(list, 10);
}

void short_list_copy_from(short_list_t* this, short_list_t* that) {
	short_list_init(this, that->size);
	this->size = that->size;
	for (int i = 0; i < that->size; i++) {
		this->data[i] = that->data[i];
	}
}

short short_list_get(short_list_t* list, int i) {
	assert(i < list->size);
	return list->data[i];
}

short short_list_remove_last(short_list_t* list) {
	list->size--;
	return list->data[list->size];
}

short short_list_remove_random(short_list_t* list, hash_t* random) {
	int index = randome_next_int(random, list->size);
	short temp = list->data[index];
	list->size--;
	list->data[index] = list->data[list->size];
	return temp;
}

void short_list_set(short_list_t* list, int i, short key) {
	assert(i < list->size);
	list->data[i] = key;
}

char* short_list_to_string(short_list_t* list) {
	char* result = calloc2(list->size * sizeof(short), sizeof(char));
	if (list->size > 0) {
		sprintf(result, "%d", list->data[0]);
		for (int i = 1; i < list->size; i++) {
			strcat(result, " ");
			sprintf(result, "%d", list->data[i]);
		}
	}
	return strcat(strcat("(", result), ")");
}

