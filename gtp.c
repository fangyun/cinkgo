#include <ctype.h>
#include <stdio.h>
#include "gtp.h"
#include <stdbool.h>
#include <stdlib.h>
#include "point.h"
#include "version.h"
#include "stone.h"
#include "coord_system.h"
#include "board.h"
#include "cinkgo.h"
#include "debug.h"
#include "player.h"
#include "util.h"

typedef parse_code_t (*gtp_func_t)(player_t *player, board_t *board, gtp_t *gtp);

typedef struct
{
	char *cmd;
	gtp_func_t f;
} gtp_command_t;

static gtp_command_t commands[];

static char* known_commands() {
	static char buf[8192];
	char *str = buf;

	for (int i = 0; commands[i].cmd; i++) {
		char *cmd = commands[i].cmd;
		if (str_prefix("gogui", cmd))
			continue;
		str += sprintf(str, "%s\n", commands[i].cmd);
	}

	str += sprintf(str, "gogui-analyze_commands\n");
	str[-1] = 0; /* remove last \n */
	return buf;
}

bool gtp_is_valid(const char *cmd) {
	if (!cmd || !*cmd)
		return false;
	const char *s = strcasestr(known_commands(), cmd);
	if (!s)
		return false;
	if (s != known_commands() && s[-1] != '\n')
		return false;

	int len = strlen(cmd);
	return s[len] == '\0' || s[len] == '\n';
}

void gtp_prefix(char prefix, gtp_t *gtp) {
	if (gtp->replied)
		return;
	gtp->replied = true;

	if (gtp->id == GTP_NO_REPLY)
		return;
	if (gtp->id >= 0)
		printf("%c%d ", prefix, gtp->id);
	else
		printf("%c ", prefix);
}

void gtp_flush(void) {
	putchar('\n');
	fflush(stdout);
}

void gtp_output(char prefix, gtp_t *gtp, va_list params) {
	if (gtp->id == GTP_NO_REPLY)
		return;
	gtp_prefix(prefix, gtp);
	char *s;
	while ((s = va_arg(params, char *))) {
		fputs(s, stdout);
	}
	putchar('\n');
	gtp_flush();
}

void gtp_reply(gtp_t *gtp, ...) {
	va_list params;
	va_start(params, gtp);
	gtp_output('=', gtp, params);
	va_end(params);
}

void gtp_error(gtp_t *gtp, ...) {
	va_list params;
	va_start(params, gtp);
	gtp_output('?', gtp, params);
	va_end(params);
}

void gtp_final_score_str(board_t *board, player_t *player, char *reply, int len) {
//	struct move_queue q = { .moves = 0 };
//	if (engine->dead_group_list)
//		engine->dead_group_list(engine, board, &q);
//	floating_t score = board_official_score(board, &q);
	float score = 0;
	if (DEBUGL(1))
		fprintf(stderr, "counted score %.1f\n", score);
	if (score == 0)
		snprintf(reply, len, "0");
	else if (score > 0)
		snprintf(reply, len, "W+%.1f", score);
	else
		snprintf(reply, len, "B+%.1f", -score);
}

static parse_code_t cmd_protocol_version(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, "2", NULL);
	return P_OK;
}

static parse_code_t cmd_name(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, "Cinkgo ", NULL);
	return P_OK;
}

static parse_code_t cmd_echo(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, gtp->next, NULL);
	return P_OK;
}

static parse_code_t cmd_version(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, CINKGO_VERSION, ": ", " Have a nice game!", NULL);
	return P_OK;
}

static parse_code_t cmd_list_commands(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, known_commands(), NULL);
	return P_OK;
}

static parse_code_t cmd_known_command(player_t *player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	if (gtp_is_valid(arg)) {
		gtp_reply(gtp, "true", NULL);
	} else {
		gtp_reply(gtp, "false", NULL);
	}
	return P_OK;
}

static parse_code_t cmd_quit(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, NULL);
	cinkgo_done();
	exit(0);
}

static parse_code_t cmd_boardsize(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_error(gtp, "board size cannot be changed", NULL);
	return P_OK;
}

static parse_code_t cmd_clear_board(player_t *player, board_t *board, gtp_t *gtp) {
	board_clear(board);
	return P_PLAYER_RESET;
}

static parse_code_t cmd_kgs_game_over(player_t *player, board_t *board, gtp_t *gtp) {
	/* The game may not be really over, just adjourned.
	 * Do not clear the board to avoid illegal moves
	 * if the game is resumed immediately after. KGS
	 * may start directly with genmove on resumption. */
	if (DEBUGL(1)) {
		fprintf(stderr, "game is over\n");
		fflush(stderr);
	}
	/* Sleep before replying, so that kgs doesn't
	 * start another game immediately. */
//	sleep(GAME_OVER_SLEEP);
	return P_OK;
}

static parse_code_t cmd_komi(player_t *player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	sscanf(arg, "%f", &board->komi);
	return P_OK;
}

static parse_code_t cmd_play(player_t *player, board_t *board, gtp_t *gtp) {
	point_t p;
	char *arg;
	if(strcmp(gtp->cmd,"play")==0){
		next_tok(arg);
	}else{
		arg = gtp->cmd; //white,black
	}
	p.stone = str2stone(arg);
	next_tok(arg);
	p.coord = str2coord(arg, board->width);
	arg = gtp->next;
//	char *playerarg = arg;
	char *reply = NULL;

	if (DEBUGL(5))
		fprintf(stderr, "got move %d,%d,%d\n", p.stone, coord_x(p.coord, board), coord_y(p.coord, board));

	// This is where kgs starts the timer, not at genmove!
	//time_start_timer(&ti[stone_other(m.color)]);
//
//	if (engine->notify_play)
//		reply = engine->notify_play(engine, board, &m, enginearg);
	if (board_play(board, &p) < 0) {
		if (DEBUGL(0)) {
			fprintf(stderr, "! ILLEGAL MOVE %d,%d,%d\n", p.stone, coord_x(p.coord, board), coord_y(p.coord, board));
			board_print(board, stderr);
		}
		gtp_error(gtp, "illegal move", NULL);
	} else {
		gtp_reply(gtp, reply, NULL);
	}
	return P_OK;
}

static parse_code_t cmd_genmove(player_t* e, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	stone_t color = str2stone(arg);

	int idx = (e->book ? fbook_check(board) : NO_POINT);
	if (is_pass(idx))
		idx = e->genmove(e, board, color, !strcasecmp(gtp->cmd, "kgs-genmove_cleanup"));

	point_t p = { .coord = idx, .stone = color };
	if (board_play(board, &p) < 0) {
		fprintf(stderr, "Attempted to generate an illegal move: [%s, %s]\n", coord2sstr(p.coord, board),
				stone2str(p.stone));
		abort();
	}
	char *str = coord2sstr(p.coord, board);
	if (DEBUGL(4))
		fprintf(stderr, "playing move %s\n", str);
	gtp_reply(gtp, str, NULL);
	return P_OK;
}

static parse_code_t cmd_fixed_handicap(player_t *player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	int stones = atoi(arg);

	gtp_prefix('=', gtp);
	board_handicap(board, stones, gtp->id == GTP_NO_REPLY ? NULL : stdout);
	if (gtp->id == GTP_NO_REPLY)
		return P_OK;
	putchar('\n');
	gtp_flush();
	return P_OK;
}

static parse_code_t cmd_final_score(player_t *player, board_t *board, gtp_t *gtp) {
	char str[64];
	gtp_final_score_str(board, player, str, sizeof(str));
	gtp_reply(gtp, str, NULL);
	return P_OK;
}

static parse_code_t cmd_showboard(player_t *player, board_t *board, gtp_t *gtp) {
	board_print(board, stderr);
	return P_OK;
}

static parse_code_t cmd_time_left(player_t *player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	//stone_t color = str2stone(arg);
	next_tok(arg);
	int time = atoi(arg);
	next_tok(arg);
	int stones = atoi(arg);
	time_left(player, time, stones);
	return P_OK;
}

static parse_code_t cmd_final_status_list(player_t *player, board_t *board, gtp_t *gtp) {
	return P_OK;
}

static gtp_command_t commands[] ={
	{ "protocol_version",       cmd_protocol_version },
	{ "name",                   cmd_name },
	{ "echo",                   cmd_echo },
	{ "version",                cmd_version },
	{ "list_commands",          cmd_list_commands },
	{ "known_command",          cmd_known_command },
	{ "quit",                   cmd_quit },
	{ "boardsize",              cmd_boardsize },
	{ "clear_board",            cmd_clear_board },
	{ "komi",                   cmd_komi },
	{ "play",                   cmd_play },
	{ "black",					cmd_play },
	{ "white",					cmd_play },
	{ "genmove",                cmd_genmove },
	{ "time_left",              cmd_time_left },
	{ "place_free_handicap",    cmd_fixed_handicap },
	{ "fixed_handicap",         cmd_fixed_handicap },
	{ "final_score",            cmd_final_score },
	{ "final_status_list",      cmd_final_status_list },
	{ "showboard",              cmd_showboard },   	/* ogs */
	{ "kgs-game_over",          cmd_kgs_game_over },
	{ "kgs-genmove_cleanup",    cmd_genmove },
	{ 0, 0 }
};

parse_code_t gtp_parse_full(player_t* e, board_t *board, char *buf, int id) {
	if (strchr(buf, '#')){
		*strchr(buf, '#') = 0;
	}

	gtp_t gtp_struct = { .next = buf, .id = id };
	gtp_t *gtp = &gtp_struct;
	next_tok(gtp->cmd);

	if (isdigit(*gtp->cmd)) {
		gtp->id = atoi(gtp->cmd);
		next_tok(gtp->cmd);
	}

	if (!*gtp->cmd){
		return P_OK;
	}

	if (gtp_is_valid(gtp->cmd)) {
		char *reply="";
		parse_code_t c = P_OK;//engine->notify(engine, board, gtp->id, gtp->cmd, gtp->next, &reply);
		if (c == P_NOREPLY) {
			gtp->id = GTP_NO_REPLY;
		} else if (c == P_DONE_OK) {
			gtp_reply(gtp, reply, NULL);
			return P_OK;
		} else if (c == P_DONE_ERROR) {
			gtp_error(gtp, reply, NULL);
			/* This is an internal error for the engine, but
			 * it is still OK from main's point of view. */
			return P_OK;
		} else if (c != P_OK) {
			return c;
		}
	}

	for (int i = 0; commands[i].cmd; i++)
		if (!strcasecmp(gtp->cmd, commands[i].cmd)) {
			parse_code_t ret = commands[i].f(e, board, gtp);
			/* For functions convenience: no reply means empty reply */
			if (!gtp->replied)
				gtp_reply(gtp, NULL);
			return ret;
		}

	gtp_error(gtp, "unknown command", NULL);
	return P_UNKNOWN_COMMAND;
}

parse_code_t gtp_parse(player_t* e, board_t *board, char *buf) {
	return gtp_parse_full(e, board, buf, -1);
}
