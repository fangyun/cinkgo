#define DEBUG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "debug.h"
#include "util.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define BSIZE 4096

void open_log_port(char *port) {
	pthread_t thread;
	static struct port_info log_info = { .socket = -1 };
	log_info.port = port;
	open_log_connection(&log_info);

	/* From now on, log_info may only be modified by the single
	 * log_thread so static allocation is ok and there is no race. */
	pthread_create(&thread, NULL, log_thread, (void *) &log_info);
}

/* Open the gtp connection on the given port, redirect stdin & stdout to it. */
void open_gtp_connection(int *socket, char *port) {
	static struct port_info gtp_info = { .socket = -1 };
	gtp_info.port = port;
	int gtp_conn = open_connection(&gtp_info);
	for (int d = STDIN; d <= STDOUT; d++) {
		if (dup2(gtp_conn, d) < 0)
			fail("dup2");
	}
	if (DEBUGL(0))
		fprintf(stderr, "gtp connection opened\n");
}
