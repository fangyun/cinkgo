#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#include "board.h"
#include "debug.h"
#include "fbook.h"
#include "mq.h"
#include "random.h"

struct board *
board_new(int bsize, char *fbookfile) {
	struct board *b = malloc2(sizeof(struct board));
	board_init(b, bsize, fbookfile);
	return b;
}

bool board_set_rules(struct board *board, char *name) {
	if (!strcasecmp(name, "japanese"))
		board->rules = RULES_JAPANESE;
	else if (!strcasecmp(name, "chinese"))
		board->rules = RULES_CHINESE;
	else if (!strcasecmp(name, "aga"))
		board->rules = RULES_AGA;
	else if (!strcasecmp(name, "new_zealand"))
		board->rules = RULES_NEW_ZEALAND;
	else if (!strcasecmp(name, "siming") || !strcasecmp(name, "simplified_ing"))
		board->rules = RULES_SIMING;
	else
		return false;
	return true;
}
