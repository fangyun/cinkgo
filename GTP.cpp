/*
 * GTP.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: yunfang
 */
#include "config.h"

#include "GTP.h"
#include "SMP.h"

void GTP::setup_default_parameters() {
	cfg_gtp_mode = true;
	cfg_allow_pondering = true;
	cfg_max_threads = std::max(1, std::min(SMP::get_num_cpus(), MAX_CPUS));
	cfg_max_memory = UCTSearch::DEFAULT_MAX_MEMORY;
	cfg_max_playouts = UCTSearch::UNLIMITED_PLAYOUTS;
	cfg_timemanage = TimeManagement::UNIFORM;
	cfg_logfile_handle = nullptr;
	cfg_quiet = false;
}

const std::string GTP::s_commands[] = {
    "protocol_version",
    "name",
    "version",
    "quit",
    "known_command",
    "list_commands",
    "boardsize",
    "clear_board",
    "komi",
    "play",
    "genmove",
    "showboard",
    "undo",
    "final_score",
    "final_status_list",
    "time_settings",
    "time_left",
    "fixed_handicap",
    "place_free_handicap",
    "set_free_handicap",
    "loadsgf",
    "printsgf",
    "kgs-genmove_cleanup",
    "kgs-time_settings",
    "kgs-game_over",
    "heatmap",
    ""
};
