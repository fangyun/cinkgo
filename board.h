#ifndef BOARD_H_
#define BOARD_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#include "util.h"
#include "stone.h"
#include "move.h"
#include "mq.h"

struct board {
	int size; /* Including S_OFFBOARD margin - see below. */
	int size2; /* size^2 */
	int bits2; /* ceiling(log2(size2)) */
	int captures[S_MAX];
	floating_t komi;
	int handicap;
	enum go_ruleset rules;
	char *fbookfile;
	struct fbook *fbook;

	int moves;
	struct move last_move;
	struct move last_move2; /* second-to-last move */
	FB_ONLY(struct move last_move3); /* just before last_move2, only set if last_move is pass */
	FB_ONLY(struct move last_move4); /* just before last_move3, only set if last_move & last_move2 are pass */
	/* Whether we tried to add a hash twice; board_play*() can
	 * set this, but it will still carry out the move as well! */
	FB_ONLY(bool superko_violation);

	/* The following two structures are goban maps and are indexed by
	 * coord.pos. The map is surrounded by a one-point margin from
	 * S_OFFBOARD stones in order to speed up some internal loops.
	 * Some of the foreach iterators below might include these points;
	 * you need to handle them yourselves, if you need to. */

	/* Stones played on the board */
	enum stone b[BOARD_MAX_COORDS];
	/* Group id the stones are part of; 0 == no group */
	group_t g[BOARD_MAX_COORDS];
	/* Positions of next stones in the stone group; 0 == last stone */
	coord_t p[BOARD_MAX_COORDS];
	/* Neighboring colors; numbers of neighbors of index color */
	struct neighbor_colors n[BOARD_MAX_COORDS];

#ifdef BOARD_PAT3
	/* 3x3 pattern code for each position; see pattern3.h for encoding
	 * specification. The information is only valid for empty points. */
	FB_ONLY(hash3_t pat3)[BOARD_MAX_COORDS];
#endif

	/* Group information - indexed by gid (which is coord of base group stone) */
	struct group gi[BOARD_MAX_COORDS];

	/* List of free positions */
	/* Note that free position here is any valid move; including single-point eyes!
	 * However, pass is not included. */
	FB_ONLY(coord_t f)[BOARD_MAX_COORDS];FB_ONLY(int flen);
	/* Map free positions coords to their list index, for quick lookup. */
	FB_ONLY(int fmap)[BOARD_MAX_COORDS];

#ifdef WANT_BOARD_C
	/* Queue of capturable groups */
	FB_ONLY(group_t c)[BOARD_MAX_GROUPS]; FB_ONLY(int clen);
#endif

	/* Symmetry information */
	FB_ONLY(struct board_symmetry symmetry);

	/* Last ko played on the board. */
	FB_ONLY(struct move last_ko);FB_ONLY(int last_ko_age);

	/* Basic ko check */
	struct move ko;

#ifdef BOARD_UNDO_CHECKS
	/* Guard against invalid quick_play() / quick_undo() uses */
	int quicked;
#endif

	/* Engine-specific state; persistent through board development,
	 * is reset only at clear_board. */
	void *es;

	/* Playout-specific state; persistent through board development,
	 * initialized by play_random_game() and free()'d at board destroy time */
	void *ps;

	/* --- PRIVATE DATA --- */

	/* For superko check: */

	/* Board "history" - hashes encountered. Size of the hash should be
	 * >> board_size^2. */
#define history_hash_bits 12
#define history_hash_mask ((1 << history_hash_bits) - 1)
#define history_hash_prev(i) ((i - 1) & history_hash_mask)
#define history_hash_next(i) ((i + 1) & history_hash_mask)
	FB_ONLY(hash_t history_hash)[1 << history_hash_bits];
	/* Hash of current board position. */
	FB_ONLY(hash_t hash);
};
#endif /* BOARD_H_ */
