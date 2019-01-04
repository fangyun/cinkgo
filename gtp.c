#define DEBUG
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "board.h"
#include "pachi.h"
#include "debug.h"
#include "engine.h"
#include "fbook.h"
#include "gtp.h"
#include "mq.h"
#include "uct/uct.h"
#include "version.h"
#include "timeinfo.h"
#include "gogui.h"
#include "t-predict/predict.h"
#include "t-unit/test.h"
#include "fifo.h"

/* XXX: THIS IS TOTALLY INSECURE!!!!
 * Even basic input checking is missing. */

enum parse_code gtp_parse(struct board *board, struct engine *engine, struct time_info *ti, char *buf) {
	return gtp_parse_full(board, engine, ti, buf, -1);
}
