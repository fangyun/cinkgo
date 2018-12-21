#include "config.h"

#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>
using namespace std;
using namespace Utils;

#include "GTP.h"
#include "Utils.h"

static void license_blurb() {
	printf("Cinkgo %s  Copyright (C) 2018  Fang Yun and contributors\n"
			"This program comes with ABSOLUTELY NO WARRANTY.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; see the COPYING file for details.\n\n",
			PROGRAM_VERSION);
}

static void parse_commandline(int argc, char** argv) {
	namespace po = boost::program_options;
	po::options_description gen_desc("Program options");
	gen_desc.add_options()("help,h", "Show commandline options.")("port,p",
			po::value<int>()->default_value(0),
			"Remote listening port, 0=disabled")("bias-delay",
			po::value<int>()->default_value(800), "Bias delay")("boardsize,b",
			po::value<int>()->default_value(19), "Board size")("book",
			"Enable opening book")("cgtc", "TODO")("grace", "TODO")("gestation",
			po::value<int>()->default_value(4), "TODO")("komi,k",
			po::value<double>()->default_value(7.5), "Komi")("lgrf2",
			"Enable LGRF2 algorithm")("liveshape", "Enable live shape")(
			"logfile", po::value<string>(), "Log file directory")("memory,m",
			po::value<int>()->default_value(1024), "Memory size")("msec",
			po::value<int>()->default_value(1000), "Millisecond per move")(
			"noponder", "Disabled ponder")("rave", "Enable RAVE")("shape",
			"Enable shape")("shape-bias", po::value<int>()->default_value(20),
			"Shape bias")("shape-minstones", po::value<int>()->default_value(5),
			"Shape pattern size")("shape-scaling-factor",
			po::value<float>()->default_value(0.95F, "0.95"),
			"Shape scaling factor")("threads,t",
			po::value<int>()->default_value(2), "Thread number")(
			"timemanage", po::value<string>()->default_value("uniform"),
			"[uniform|exiting|simple]\nSet time management ");
	// These won't be shown, we use them to catch incorrect usage of the command line.
	po::options_description h_desc("Hidden options");
	h_desc.add_options()("arguments", po::value<vector<string>>());
	po::options_description visible;
	visible.add(gen_desc);
	po::options_description all;
	all.add(visible).add(h_desc);
	po::positional_options_description p_desc;
	p_desc.add("arguments", -1);
	po::variables_map vm;
	try {
		po::store(
				po::command_line_parser(argc, argv).options(all).positional(
						p_desc).run(), vm);
		po::notify(vm);
	} catch (const po::error& e) {
		printf("ERROR: %s\n", e.what());
		license_blurb();
		cout << visible << endl;
		exit(EXIT_FAILURE);
	}

	// Handle commandline options
	if (vm.count("help") || vm.count("arguments")) {
		auto ev = EXIT_SUCCESS;
		// The user specified an argument. We don't accept any, so explain our usage.
		if (vm.count("arguments")) {
			for (auto& arg : vm["arguments"].as<vector<string>>()) {
				cout << "Unrecognized argument: " << arg << endl;
			}
			ev = EXIT_FAILURE;
		}
		license_blurb();
		cout << visible << endl;
		exit(ev);
	}
	if (vm.count("quiet")) {
		cfg_quiet = true;
	}
	if (vm.count("logfile")) {
		cfg_logfile = vm["logfile"].as<string>();
		myprintf("Logging to %s.\n", cfg_logfile.c_str());
		cfg_logfile_handle = fopen(cfg_logfile.c_str(), "a");
	}
    if (vm.count("gtp")) {
        cfg_gtp_mode = true;
    }
    if (!vm["threads"].defaulted()) {
        auto num_threads = vm["threads"].as<int>();
        if (num_threads > cfg_max_threads) {
            myprintf("Clamping threads to maximum = %d\n", cfg_max_threads);
            num_threads = cfg_max_threads;
        }
        cfg_num_threads = num_threads;
    }
    myprintf("Using %d thread(s).\n", cfg_num_threads);
    if (vm.count("noponder")) {
        cfg_allow_pondering = false;
    }
    if (vm.count("playouts")) {
        cfg_max_playouts = vm["playouts"].as<int>();
        if (!vm.count("noponder")) {
            printf("Nonsensical options: Playouts are restricted but "
                   "thinking on the opponent's time is still allowed. "
                   "Add --noponder if you want a weakened engine.\n");
            exit(EXIT_FAILURE);
        }

        // 0 may be specified to mean "no limit"
        if (cfg_max_playouts == 0) {
            cfg_max_playouts = UCTSearch::UNLIMITED_PLAYOUTS;
        }
    }
    if (vm.count("timemanage")) {
        auto tm = vm["timemanage"].as<std::string>();
        if (tm == "uniform") {
            cfg_timemanage = TimeManagement::UNIFORM;
        } else if (tm == "exiting") {
            cfg_timemanage = TimeManagement::EXITING;
        } else if (tm == "simple") {
            cfg_timemanage = TimeManagement::SIMPLE;
        } else {
            printf("Invalid timemanage value.\n");
            exit(EXIT_FAILURE);
        }
    }

	auto out = stringstream { };
	for (auto i = 1; i < argc; i++) {
		out << " " << argv[i];
	}
	cfg_options_str = out.str();
}

int main(int argc, char **argv) {
	parse_commandline(argc, argv);
	return 0;
}
