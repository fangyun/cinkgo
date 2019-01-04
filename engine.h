#ifndef ENGINE_H_
#define ENGINE_H_

#include "board.h"
#include "move.h"
#include "gtp.h"

/* This is engine data structure. A new engine instance is spawned
 * for each new game during the program lifetime. */
struct engine {
	char *name;
	char *comment;

	/* If set, do not reset the engine state on clear_board. */
	bool keep_on_clear;

	engine_notify_t notify;
	engine_board_print_t board_print;
	engine_notify_play_t notify_play;
	engine_chat_t chat;
	engine_undo_t undo;
	engine_result_t result;

	/* Generate a move. If pass_all_alive is true, <pass> shall be generated only
	 * if all stones on the board can be considered alive, without regard to "dead"
	 * considered stones. */
	engine_genmove_t genmove;

	/* Used by distributed engine */
	engine_genmoves_t genmoves;

	/* List best moves for current position. */
	engine_best_moves_t best_moves;

	/* Evaluate feasibility of player @color playing at all free moves. Will
	 * simulate each move from b->f[i] for time @ti, then set
	 * 1-max(opponent_win_likelihood) in vals[i]. */
	engine_evaluate_t evaluate;

	/* One dead group per queued move (coord_t is (ab)used as group_t). */
	engine_dead_group_list_t dead_group_list;

	/* Pause any background thinking being done, but do not tear down
	 * any data structures yet. */
	engine_stop_t stop;

	/* e->data and e will be free()d by caller afterwards. */
	engine_done_t done;

	/* Return current ownermap, if engine supports it. */
	engine_ownermap_t ownermap;

	/* GoGui hook */
	engine_livegfx_hook_t livegfx_hook;

	void *data;
};

static inline void engine_done(struct engine *e) {
	if (e->done)
		e->done(e);
	if (e->data)
		free(e->data);
	free(e);
}

typedef struct engine *(*engine_init_t)(char *arg, struct board *b);

#endif /* ENGINE_H_ */
