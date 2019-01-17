#define DEBUG
#define G_LOG_DOMAIN "gtp"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gtp.h"
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
	float score = final_score(player->scorer);
	if (DEBUGL(LOG_LEVEL_DEBUG))
		g_debug("counted score %.1f\n", score);
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

static parse_code_t cmd_undo(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_error(gtp, "不能悔棋", NULL);
	return P_OK;
}

static parse_code_t cmd_version(player_t *player, board_t *board, gtp_t *gtp) {
	gtp_reply(gtp, CINKGO_VERSION, ",", " Git commit: ", CINKGO_VERGIT, NULL);
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
	char *arg;
	next_tok(arg);
	int size = atoi(arg);
	if (size != 19) {
		gtp_error(gtp, "棋盘尺寸只支持19×19", NULL);
	}
	return P_OK;
}

static parse_code_t cmd_clear_board(player_t *player, board_t *board, gtp_t *gtp) {
	player_clear(player, board);
	return P_PLAYER_RESET;
}

static parse_code_t cmd_kgs_game_over(player_t *player, board_t *board, gtp_t *gtp) {
	/* The game may not be really over, just adjourned.
	 * Do not clear the board to avoid illegal moves
	 * if the game is resumed immediately after. KGS
	 * may start directly with genmove on resumption. */
	if (DEBUGL(LOG_LEVEL_INFO)) {
		g_info("对弈结束");
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
	if(DEBUGL(LOG_LEVEL_INFO)){
		g_info("rebuild player");
	}
	//playerBuilder = playerBuilder.komi(komi);
	//player = playerBuilder.build();
	if(DEBUGL(LOG_LEVEL_INFO)){
		g_info("rebuilt player");
	}
	return P_OK;
}

static parse_code_t cmd_play(player_t *player, board_t *board, gtp_t *gtp) {
	point_t p;
	char *arg;
	if(strcasecmp(gtp->cmd,"play")==0){
		next_tok(arg);
	}else{
		arg = gtp->cmd; //white,black
	}
	p.stone = str2stone(arg);
	next_tok(arg);
	p.coord = str2coord(arg, board->width);
	arg = gtp->next;
	char *reply = NULL;

	if (DEBUGL(LOG_LEVEL_DEBUG))
		g_debug("got move %d,%d,%d\n", p.stone, coord_x(p.coord, board->width), coord_y(p.coord, board->width));
	if (player_accept_move(player, board, &p) < 0) {
		if (DEBUGL(LOG_LEVEL_WARNING)) {
			g_warning("! ILLEGAL MOVE %d,%d,%d\n", p.stone, coord_x(p.coord, board->width), coord_y(p.coord, board->width));
			board_print(board, stderr);
		}
		gtp_error(gtp, "illegal move", NULL);
	} else {
		gtp_reply(gtp, reply, NULL);
	}
	return P_OK;
}

static parse_code_t cmd_genmove(player_t* player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	stone_t color = str2stone(arg);

	point_t* point = player_best_move(player, board, color);
	if (point->coord == RESIGN) {
		gtp_reply(gtp, RESIGN_STR, NULL);
		player_clear(player, board); // to stop threaded players
	} else {
		player_accept_move(player, board, point);
		const char *str = coord2sstr(point->coord, board->width);
		if (DEBUGL(LOG_LEVEL_DEBUG))
			g_debug("playing move %s\n", str);
		gtp_reply(gtp, str, NULL);
	}
	return P_OK;
}

static parse_code_t cmd_fixed_handicap(player_t *player, board_t *board, gtp_t *gtp) {
	char *arg;
	next_tok(arg);
	int handicapSize = atoi(arg);
	if (handicapSize >= 2 && handicapSize <= 9) {
		player_set_handicap(player);
		gtp_reply(gtp, NULL);
	}else{
		gtp_error(gtp, "无效的让子大小");
	}
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
	stone_t stone = str2stone(arg);
	next_tok(arg);
	int time = atoi(arg);
	time_left(player, time, stone);
	return P_OK;
}

static parse_code_t cmd_final_status_list(player_t *player, board_t *board, gtp_t *gtp) {
	char *status;
	next_tok(status);
	if (!strcmp(status,"dead")) {
		gtp_reply(gtp,"TODO", NULL);
	} else if (!strcmp(status,"alive")) {
		gtp_reply(gtp, "TODO",NULL);
	}
	return P_OK;
}

static gtp_command_t commands[] ={
	{ "protocol_version",       cmd_protocol_version },
	{ "name",                   cmd_name },
	{ "undo",                   cmd_undo },
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
	{ "fixed_handicap",         cmd_fixed_handicap },
	{ "final_score",            cmd_final_score },
	{ "final_status_list",      cmd_final_status_list },
	{ "showboard",              cmd_showboard },   	/* ogs */
	{ "kgs-game_over",          cmd_kgs_game_over },
	{ 0, 0 }
};

parse_code_t gtp_parse_full(player_t* player, board_t *board, char *buf, int id) {
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

	for (int i = 0; commands[i].cmd; i++){
		if (!strcasecmp(gtp->cmd, commands[i].cmd)) {
			parse_code_t ret = commands[i].f(player, board, gtp);
			if (!gtp->replied)
				gtp_reply(gtp, NULL);
			return ret;
		}
	}
	gtp_error(gtp, "未知命令", NULL);
	return P_UNKNOWN_COMMAND;
}

parse_code_t gtp_parse(player_t* e, board_t *board, char *buf) {
	return gtp_parse_full(e, board, buf, -1);
}
