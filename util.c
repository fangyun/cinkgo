#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "cinkgo.h"
#include "util.h"

void die(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vwarning(format, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void fail(char *msg) {
	warning("%s: %s\n", msg, strerror(errno));
	exit(42);
}