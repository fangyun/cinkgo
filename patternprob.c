#define DEBUG
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "debug.h"
#include "pattern.h"
#include "patternsp.h"
#include "patternprob.h"
#include "engine.h"

void prob_dict_done() {
	if (!prob_dict)
		return;

	for (unsigned int id = 0; id < spat_dict->nspatials; id++)
		free(prob_dict->table[id]);
	free(prob_dict->table);
	free(prob_dict);
	prob_dict = NULL;
}
