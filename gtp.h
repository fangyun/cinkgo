#ifndef CINKGO_GTP_H_
#define CINKGO_GTP_H_

#include "board.h"
#include "engine.h"

#define GTP_NO_REPLY (-2)
typedef enum {
	P_OK, P_NOREPLY, P_DONE_OK, P_DONE_ERROR, P_PLAYER_RESET, P_UNKNOWN_COMMAND,
} parse_code_t;

typedef struct {
	char *cmd;
	char *next;
	int id;
	int replied;
} gtp_t;

#define next_tok(to_) \
	to_ = gtp->next; \
	gtp->next = gtp->next + strcspn(gtp->next, " \t\r\n"); \
	if (*gtp->next) { \
		*gtp->next = 0; gtp->next++; \
		gtp->next += strspn(gtp->next, " \t\r\n"); \
	}

parse_code_t gtp_parse_full(engine_t* e, board_t *board, char *buf, int id);
parse_code_t gtp_parse(engine_t* e, board_t *board, char *buf);

#endif /* CINKGO_GTP_H_ */
