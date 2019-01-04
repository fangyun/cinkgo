#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#include "board.h"
#include "debug.h"
#include "move.h"
#include "timeinfo.h"
#include "gtp.h"
#include "joseki.h"
#include "engine.h"
#include "dcnn.h"
#include "tactics/util.h"
#include "engines/josekiscan.h"

static bool joseki_enabled = true;
static bool joseki_required = false;
void disable_joseki() {
	joseki_enabled = false;
}
void require_joseki() {
	joseki_required = true;
}

void joseki_done() {
	if (!joseki_dict)
		return;

	josekipat_t *prev = NULL;
	forall_joseki_patterns(joseki_dict)
	{
		free(prev);
		prev = p;
	}
	forall_3x3_joseki_patterns(joseki_dict)
	{
		free(prev);
		prev = p;
	}
	forall_ignored_joseki_patterns(joseki_dict)
	{
		free(prev);
		prev = p;
	}
	free(prev);
	free(joseki_dict);
	joseki_dict = NULL;
}
