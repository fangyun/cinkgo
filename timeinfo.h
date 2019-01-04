#ifndef TIMEINFO_H_
#define TIMEINFO_H_

#include <stdbool.h>

#include "board.h"

/* Time settings to use during fuseki */
extern struct time_info ti_fuseki;

struct time_info {
	/* For how long we can spend the time? */
	enum time_period {
		TT_NULL, // No time limit. Other structure elements are undef.
		TT_MOVE, // Time for the next move.
		TT_TOTAL, // Time for the rest of the game. Never seen by engine.
	} period;
	/* How are we counting the time? */
	enum time_dimension {
		TD_GAMES, // Fixed number of simulations to perform.
		TD_WALLTIME, // Wall time to spend performing simulations.
	} dim;
	/* The actual time count. */
	struct {
		int games;     // TD_GAMES
		int games_max; // TD_GAMES
		struct {   // TD_WALLTIME
			/* Main thinking time. 0 if we are already completely
			 * in byoyomi. */
			double main_time;

			/* Byoyomi time. This time must be remembered to avoid
			 * rushing at the end of the main period. If no byoyomi,
			 * set to 0. Otherwise, both periods and stones are
			 * larger than zero, and initially we have _periods
			 * periods of length _time and have to play _stones
			 * stones in each. If we play in canadian byoyomi,
			 * _time will shrink until we play all stones of the
			 * current period; _max always keeps period length
			 * for reference. */
			/* (In normal time settings, one of _periods or _stones
			 * is 1.) */
			double byoyomi_time;
			int byoyomi_periods;
			int byoyomi_stones;
			double byoyomi_time_max;
			int byoyomi_stones_max;
			bool canadian; // time_left field meaning changes

			/* Absolute time at which our timer started for current move,
			 * 0 if not yet known. The engine always sees > 0. */
			double timer_start;
		} t;
	} len;
	/* If true, this time info is independent from GTP time_left updates,
	 * which will be ignored. This is the case if the time settings were
	 * forced on the command line. */
	bool ignore_gtp;
};

#endif /* TIMEINFO_H_ */
