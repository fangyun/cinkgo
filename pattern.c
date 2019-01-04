#define DEBUG
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "debug.h"
#include "pattern.h"
#include "patternsp.h"
#include "patternprob.h"
#include "tactics/ladder.h"
#include "tactics/selfatari.h"
#include "tactics/1lib.h"
#include "tactics/2lib.h"
#include "tactics/util.h"
#include "playout.h"
#include "playout/moggy.h"
#include "ownermap.h"
#include "mq.h"

static bool patterns_enabled = true;
static bool patterns_required = false;
void disable_patterns()     {  patterns_enabled = false;  }
void require_patterns()     {  patterns_required = true;  }
