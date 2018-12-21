/*
 * Utils.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: yunfang
 */
#include <cstdarg>
#include <mutex>

#include "Utils.h"
#include "GTP.h"

static std::mutex IOmutex;
static void myprintf_base(const char *fmt, va_list ap) {
    va_list ap2;
    va_copy(ap2, ap);

    vfprintf(stderr, fmt, ap);

    if (cfg_logfile_handle) {
        std::lock_guard<std::mutex> lock(IOmutex);
        vfprintf(cfg_logfile_handle, fmt, ap2);
    }
    va_end(ap2);
}

void Utils::myprintf(const char *fmt, ...) {
    if (cfg_quiet) {
        return;
    }

    va_list ap;
    va_start(ap, fmt);
    myprintf_base(fmt, ap);
    va_end(ap);
}

