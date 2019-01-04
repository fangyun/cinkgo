#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include "chat.h"

#ifndef HAVE_NO_REGEX_SUPPORT
#include <regex.h>

#define DEBUG

#include "debug.h"
#include "random.h"

/* Read the chat file, a sequence of lines of the form:
 * minwin;maxwin;from;regex;reply
 * Set minwin, maxwin to -1.0 2.0 for answers to chat other than winrate.
 * Set from as one space for replies to anyone.
 * Examples:
 *   -1.0;0.3; ;winrate;%.1f%% I'm losing
 *   -1.0;2.0;pasky;^when ;Today
 */
void chat_init(char *chat_file) {
	if (!chat_file)
		return;
	FILE *f = fopen(chat_file, "r");
	if (!f) {
		perror(chat_file);
		return;
	}
	chat_table = calloc2(MAX_CHAT_PATTERNS, sizeof(*chat_table));
	struct chat *entry = chat_table;
	while (fscanf(f, "%lf;%lf;%20[^;];%100[^;];%300[^\n]\n", &entry->minwin, &entry->maxwin, entry->from, entry->regex,
			entry->reply) == 5) {
		if (!strcmp(entry->from, " "))
			entry->from[0] = '\0';
		int err = regcomp(&entry->preg, entry->regex, REG_EXTENDED | REG_ICASE);
		if (err) {
			char msg[200];
			regerror(err, &entry->preg, msg, sizeof(msg));
			fprintf(stderr, "Error compiling %s: %s\n", entry->regex, msg);
		} else {
			entry++;
		}
	}
	if (!feof(f))
		fprintf(stderr, "syntax error around line %u in %s\n", (unsigned) (entry - chat_table), chat_file);
	fclose(f);
	if (DEBUGL(1))
		fprintf(stderr, "Loaded %u chat entries from %s\n", (unsigned) (entry - chat_table), chat_file);
}

void chat_done(void) {
	if (chat_table) {
		free(chat_table);
		chat_table = NULL;
	}
}
