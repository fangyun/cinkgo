#include "debug.h"
#include <string.h>

log_level_t log_level(char* str) {
	if (!strcasecmp(str, "fail")) {
		return LOG_LEVEL_FAIL;
	}
	if (!strcasecmp(str, "error")) {
		return LOG_LEVEL_ERROR;
	}
	if (!strcasecmp(str, "warn") || !strcasecmp(str, "warning")) {
		return LOG_LEVEL_WARNING;
	}
	if (!strcasecmp(str, "info")) {
		return LOG_LEVEL_INFO;
	}
	if (!strcasecmp(str, "debug")) {
		return LOG_LEVEL_DEBUG;
	}
	if (!strcasecmp(str, "trace")) {
		return LOG_LEVEL_TRACE;
	}
	return LOG_LEVEL_WARNING;
}

