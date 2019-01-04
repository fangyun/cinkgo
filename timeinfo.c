#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define DEBUG

#include "debug.h"
#include "tactics/util.h"
#include "ownermap.h"
#include "timeinfo.h"

struct time_info ti_fuseki = { .period = TT_NULL };

bool time_parse(struct time_info *ti, char *s) {
	char *end = s;
	switch (s[0]) {
	case '_':
		ti->period = TT_TOTAL;
		s++;
		break;
	default:
		ti->period = TT_MOVE;
		break;
	}
	switch (s[0]) {
	case '=':
		ti->dim = TD_GAMES;
		ti->len.games = strtol(++s, &end, 10);
		ti->len.games_max = 0;
		if (*end == ':') {
			ti->len.games_max = strtol(end + 1, &end, 10);
			if (ti->len.games_max < ti->len.games)
				return false;
		}
		if (ti->len.games < GJ_MINGAMES)
			fprintf(stderr, "Error: minimum %i playouts.\n", GJ_MINGAMES);
		if (ti->len.games < GJ_MINGAMES)
			return false;
		if (*end)
			return false;
		break;
	default:
		ti->dim = TD_WALLTIME;
		ti->len.t.timer_start = 0;
		if (ti->period == TT_TOTAL) {
			ti->len.t.main_time = strtof(s, &end);
			ti->len.t.byoyomi_time = 0.0;
			ti->len.t.byoyomi_time_max = 0.0;
			ti->len.t.byoyomi_periods = 0;
			ti->len.t.byoyomi_stones = 0;
			ti->len.t.byoyomi_stones_max = 0;
		} else {
			assert(ti->period == TT_MOVE);
			ti->len.t.main_time = 0.0;
			ti->len.t.byoyomi_time = strtof(s, &end);
			ti->len.t.byoyomi_time_max = ti->len.t.byoyomi_time;
			ti->len.t.byoyomi_periods = 1;
			ti->len.t.byoyomi_stones = 1;
			ti->len.t.byoyomi_stones_max = 1;
		}
		if (*end)
			return false;
		break;
	}
	return true;
}
