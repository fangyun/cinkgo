#define DEBUG
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "debug.h"
#include "pattern.h"
#include "patternsp.h"

void spatial_dict_done() {
	if (!spat_dict)
		return;

	free(spat_dict->spatials);

	spatial_entry_t *next = NULL;
	for (unsigned int id = 0; id <= spatial_hash_mask; id++)
		for (spatial_entry_t *e = spat_dict->hashtable[id]; e; e = next) {
			next = e->next;
			free(e);
		}

	free(spat_dict);
	spat_dict = NULL;
}
