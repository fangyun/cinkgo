#define DEBUG
#define G_LOG_DOMAIN "cinkgo"
#include <getopt.h>
#include <stdlib.h>
#include "cinkgo.h"
#include "util.h"
#include "version.h"
#include "debug.h"
#include "comparable.h"
#include "gtp.h"

int debug_level = 3;

comparable_new_t comparable_new[TYPE_MAX] = { comparable_board_new, comparable_history_observer_new, comparable_chinese_final_scorer_new };

static struct option longopts[] = {
		{ "biasdelay", required_argument, 0, OPT_BIASDELAY },
		{ "nobook", no_argument, 0, OPT_NOBOOK },
		{ "komi", required_argument, 0, OPT_KOMI },
		{ "nolgrf2", no_argument, 0, OPT_NOLGRF2 },
		{ "memory",	required_argument, 0, OPT_MEMORY },
		{ "msec", required_argument, 0, OPT_MSEC },
		{ "ponder", no_argument, 0, OPT_PONDER },
		{ "norave", no_argument, 0, OPT_NORAVE },
		{ "shape-bias", required_argument, 0, OPT_SHAPE_BIAS },
		{ "shape-pattern-size", required_argument, 0, OPT_SHAPE_PATTERN_SIZE },
		{ "shape-scaling-factor", required_argument, 0, OPT_SHAPE_SCALING_FACTOR },
		{ "threads", required_argument, 0, OPT_THREADS },
		{ "debug-level", required_argument, 0, 'd' },
		{ "log-file", required_argument, 0, 'o' },
		{ "time-management", required_argument, 0, 't' },
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
		{ 0, 0, 0, 0 } };

cinkgo_t* cinkgo_new() {
	cinkgo_t* c = calloc(1, sizeof(cinkgo_t));
	return c;
}

static void usage() {
	fprintf(stderr, "Usage: cinkgo [OPTIONS]\n\n");
	fprintf(stderr, "Options: \n"
			"  -h, --help                        show usage \n"
			"  -d, --debug-level LEVEL           set debug level \n"
			"  -g, --gtp-port [HOST:]GTP_PORT    read gtp commands from network instead of stdin. \n"
			"                                    listen on given port if HOST not given, otherwise \n"
			"                                    connect to remote host. \n"
			"  -o  --log-file FILE               log to FILE instead of stderr \n"
			"  -t, --time-management TIME_MGMT   set time management.Valid values: exiting,uniform,simple \n"
			"  -v, --version                     show version \n"
			"      --nobook                      no use opening book \n"
			"      --biasdelay DELAY             bias delay \n"
			"      --nobook                      disable opening book \n"
			"      --komi KOMI                   set komi value \n"
			"      --nolgrf2                     disable LGRF2 \n"
			"      --memory SIZE                 set memory size \n"
			"      --msec MILLISECOND            millisecond per move \n"
			"      --ponder                      enable ponder \n"
			"      --norave                      disable RAVE \n"
			"      --shape-bias BIAS             set shape bias \n"
			"      --shape-pattern-size SIZE     set shape pattern size \n"
			"      --shape-scaling-factor FACTOR set shape scaling factor \n"
			" \n");
}

static void show_version(FILE *s) {
	fprintf(s, "Cinkgo version %s\n", CINKGO_VERSION);
	if (!DEBUGL(2))
		return;

	fprintf(s, "git %s\n", CINKGO_VERGIT);

	/* Build info */
	fprintf(s, "%s\n\n", CINKGO_VERBUILD);
}

static void build_player(int argc, char* argv[], cinkgo_t* cgo) {
	player_builder_t* player_builder = player_builder_new();
	int opt;
	int option_index;
	/* Leading ':' -> we handle error messages. */
	while ((opt = getopt_long(argc, argv, ":hvd:o:t:", longopts, &option_index)) != -1) {
		switch (opt) {
		case OPT_BIASDELAY:
			player_builder->bias_delay = atoi(optarg);
			break;
		case OPT_BOARDSIZE:
			player_builder->board_size = atoi(optarg);
			break;
		case OPT_NOBOOK:
			player_builder->book = false;
			break;
		case OPT_KOMI:
			player_builder->komi = atof(optarg);
			break;
		case OPT_NOLGRF2:
			player_builder->lgrf2 = false;
			break;
		case OPT_MEMORY:
			player_builder->memory = atoi(optarg);
			break;
		case OPT_MSEC:
			player_builder->msec = atoi(optarg);
			break;
		case OPT_PONDER:
			player_builder->ponder = true;
			break;
		case OPT_NORAVE:
			player_builder->rave = false;
			break;
		case OPT_SHAPE_BIAS:
			player_builder->shape_bias = atoi(optarg);
			break;
		case OPT_SHAPE_PATTERN_SIZE:
			player_builder->shape_pattern_size = atoi(optarg);
			break;
		case OPT_SHAPE_SCALING_FACTOR:
			player_builder->shape_scaling_factor = atof(optarg);
			break;
		case OPT_THREADS:
			player_builder->threads = atoi(optarg);
			break;
		case 'd':
			debug_level = log_level(optarg);
			break;
		case 'o':
			cgo->log = fopen(optarg, "w");
			if (!cgo->log)
				fail(optarg);
			fclose(cgo->log);
			if (!freopen(optarg, "w", stderr))
				fail("freopen()");
			setlinebuf(stderr);
			break;
		case 'h':
			usage();
			exit(0);
		case 't':
			player_builder->manager_type = optarg;
			break;
		case 'v':
			show_version(stdout);
			exit(0);
		case ':':
			die("%s: Missing argument\n"
					"Try 'cinkgo --help' for more information.\n", argv[optind - 1]);
			break;
		default: /* '?' */
			die("Invalid argument: %s\n"
					"Try 'cinkgo --help' for more information.\n", argv[optind - 1]);
		}
	}
	cgo->player_builder = player_builder;
	copyable_struct_t* cs = build_use_with_bias(player_builder);
	cgo->board = (board_t*)(copyable_struct_get(cs, T_BOARD)->data);
	cgo->player = player_build(player_builder, cs);
}

static void init_command_line_args(int argc, char *argv[], cinkgo_t* cinkgo) {
	GString* cla = g_string_new("");
	for (int i = 0; i < argc; i++) {
		cla = g_string_append(g_string_append(cla, argv[i]), " ");
	}
	cinkgo->command_line_args = cla->str;
}

void cinkgo_done(){
}

int main(int argc, char *argv[]) {
	cinkgo_t* cgo = cinkgo_new();
	build_player(argc, argv, cgo);
	init_command_line_args(argc, argv, cgo);

	char buf[4096];
	do {
		if (DEBUGL(LOG_LEVEL_DEBUG)) {
			g_debug("IN: %s", buf);
		}
		parse_code_t c = gtp_parse(cgo->player, cgo->board, buf);
		if (c == P_PLAYER_RESET) {
			player_done(cgo->player);
			build_player(argc, argv, cgo);
		}
	} while (fgets(buf, 4096, stdin));
	free(cgo);
	return 0;
}
