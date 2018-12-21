/*
 * GTP.h
 *
 *  Created on: Dec 21, 2018
 *      Author: yunfang
 */

#ifndef GTP_H_
#define GTP_H_

#include <cstdio>
#include <string>

#include "UCTSearch.h"

extern bool cfg_gtp_mode;
extern bool cfg_allow_pondering;
extern bool cfg_quiet;
extern int cfg_num_threads;
extern size_t cfg_max_memory;
extern TimeManagement::enabled_t cfg_timemanage;
extern std::string cfg_logfile;
extern FILE* cfg_logfile_handle;
extern std::string cfg_options_str;
extern int cfg_max_threads;
extern int cfg_max_playouts;

static constexpr size_t MiB = 1024LL * 1024LL;

class GTP {
public:
	static void setup_default_parameters();
private:
	static constexpr int GTP_VERSION = 2;
	static const std::string s_commands[];
};

#endif /* GTP_H_ */
