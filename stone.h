#ifndef CINKGO_STONE_H_
#define CINKGO_STONE_H_

typedef enum {
	S_NONE, S_BLACK, S_WHITE, S_OFFBOARD, S_MAX
} stone_t;

static char stone2char(stone_t s);
static stone_t char2stone(char s);
char *stone2str(stone_t s);
stone_t str2stone(char *str);

static inline char stone2char(stone_t s) {
	return ".XO#"[s];
}

static inline stone_t char2stone(char s) {
	switch (s) {
	case '.':
		return S_NONE;
	case 'X':
		return S_BLACK;
	case 'O':
		return S_WHITE;
	case '#':
		return S_OFFBOARD;
	}
	return S_NONE; // XXX
}

#endif /* CINKGO_STONE_H_ */
