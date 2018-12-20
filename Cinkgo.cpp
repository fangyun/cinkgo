#include <iostream>
#include <boost/program_options.hpp>
using namespace std;

std::string cfg_options_str;

static void parse_commandline(int argc, char** argv) {
	namespace po = boost::program_options;
	po::options_description gen_desc("Generic options");
	gen_desc.add_options()("help,h", "Show commandline options.")("port,p",
			po::value<int>()->default_value(0), "Remote listening port, 0=disabled")("bias-delay",
			po::value<int>()->default_value(800), "Bias delay")("boardsize,b",
			po::value<int>()->default_value(19), "Board size")("book",
			"Enable opening book")("cgtc", "TODO")("grace", "TODO")("gestation",
			po::value<int>()->default_value(4), "TODO")("komi,k",
			po::value<double>()->default_value(7.5), "Komi")("lgrf2",
			"Enable LGRF2 algorithm")("liveshape", "Enable live shape")(
			"log-file", po::value<std::string>(), "Log file directory")(
			"memory,m", po::value<int>()->default_value(1024), "Memory size")(
			"msec", po::value<int>()->default_value(1000),
			"Millisecond per move")("ponder", "Enable ponder")("rave",
			"Enable RAVE")("shape", "Enable shape")("shape-bias",
			po::value<int>()->default_value(20), "Shape bias")(
			"shape-minstones", po::value<int>()->default_value(5),
			"Shape pattern size")("shape-scaling-factor",
			po::value<float>()->default_value(0.95F), "Shape scaling factor")(
			"threads,t", po::value<int>()->default_value(2), "Thread number")(
			"time-management",
			po::value<std::string>()->default_value("uniform"),
			"[uniform|exiting|simple]\nSet time management ");
	// These won't be shown, we use them to catch incorrect usage of the
	// command line.
	po::options_description h_desc("Hidden options");
	h_desc.add_options()("arguments", po::value<std::vector<std::string>>());
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
		std::cout << visible << std::endl;
		exit(EXIT_FAILURE);
	}

    // Handle commandline options
    if (vm.count("help") || vm.count("arguments")) {
        auto ev = EXIT_SUCCESS;
        // The user specified an argument. We don't accept any, so explain
        // our usage.
        if (vm.count("arguments")) {
            for (auto& arg : vm["arguments"].as<std::vector<std::string>>()) {
                std::cout << "Unrecognized argument: " << arg << std::endl;
            }
            ev = EXIT_FAILURE;
        }
        std::cout << visible << std::endl;
        exit(ev);
    }

    auto out = std::stringstream{};
    for (auto i = 1; i < argc; i++) {
        out << " " << argv[i];
    }
    cfg_options_str = out.str();
}

int main(int argc, char **argv) {
	parse_commandline(argc, argv);
	return 0;
}
