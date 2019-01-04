#ifndef GTP_H_
#define GTP_H_

#define GTP_NO_REPLY (-2)

struct board;
struct engine;
struct time_info;

enum parse_code {
	P_OK, P_NOREPLY, P_DONE_OK, P_DONE_ERROR, P_ENGINE_RESET, P_UNKNOWN_COMMAND,
};

#endif /* GTP_H_ */
