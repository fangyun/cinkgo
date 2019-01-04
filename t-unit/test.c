#define DEBUG
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "board.h"
#include "debug.h"
#include "tactics/selfatari.h"
#include "tactics/dragon.h"
#include "tactics/ladder.h"
#include "tactics/1lib.h"
#include "tactics/seki.h"
#include "util.h"
#include "random.h"
#include "playout.h"
#include "timeinfo.h"
#include "playout/moggy.h"
#include "engines/replay.h"
#include "ownermap.h"

int unit_test(char *filename) {
	tunit_over_gtp = 0;

	FILE *f = fopen(filename, "r");
	if (!f)
		fail(filename);

	int total = 0, passed = 0;
	int total_opt = 0, passed_opt = 0;

	struct board *b = board_new(19 + 2, NULL);
	b->komi = 7.5;
	char buf[256];
	char *line = buf;

	while (fgets(line, sizeof(buf), f)) {
		chomp(line);
		remove_comments(line);

		optional = 0;
		switch (line[0]) {
		case '%':
			strncpy(title, line, sizeof(title) - 1);
			title[sizeof(title) - 1] = 0;
			if (DEBUGL(1))
				fprintf(stderr, "\n%s\n", line);
			continue;
		case '!':
			optional = 1;
			line++;
			line += strspn(line, " ");
			break;
		case 0:
			continue;
		}

		if (!strncmp(line, "boardsize ", 10)) {
			board_load(b, f, atoi(line + 10));
			continue;
		}
		if (!strncmp(line, "ko ", 3)) {
			set_ko(b, line + 3);
			continue;
		}

		if (optional) {
			total_opt++;
			passed_opt += unit_test_cmd(b, line);
		} else {
			total++;
			passed += unit_test_cmd(b, line);
		}
	}

	fclose(f);

	printf("\n\n");
	printf("----------- [  %3i/%-3i mandatory tests passed (%i%%)  ] -----------\n", passed, total,
			passed * 100 / total);
	if (total_opt)
		printf("               %3i/%-3i  optional tests passed (%i%%)               \n\n", passed_opt, total_opt,
				passed_opt * 100 / total_opt);

	int ret = 0;
	if (total == passed)
		printf("\nAll tests PASSED");
	else {
		printf("\nSome tests FAILED");
		ret = EXIT_FAILURE;
	}
	if (passed_opt != total_opt)
		printf(", %d optional test(s) IGNORED", total_opt - passed_opt);
	printf("\n");
	return ret;
}
