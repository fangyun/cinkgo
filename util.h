#ifndef CINKGO_UTIL_H_
#define CINKGO_UTIL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define array_size(x) (sizeof(x)/sizeof(x[0]))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect((x), 0)

int str_prefix(char *prefix, char *str);
/* Warn user (popup on windows) */
void warning(const char *format, ...);

/* Warning + terminate process */
void die(const char *format, ...) __attribute__ ((noreturn));

/* Terminate after system call failure (similar to perror()) */
void fail(char *msg) __attribute__ ((noreturn));

static inline void *
checked_malloc(size_t size, char *filename, unsigned int line, const char *func) {
	void *p = malloc(size);
	if (!p)
		die("%s:%u: %s: OUT OF MEMORY malloc(%u)\n", filename, line, func, (unsigned) size);
	return p;
}

static inline void *
checked_calloc(size_t nmemb, size_t size, const char *filename, unsigned int line, const char *func) {
	void *p = calloc(nmemb, size);
	if (!p)
		die("%s:%u: %s: OUT OF MEMORY calloc(%u, %u)\n", filename, line, func, (unsigned) nmemb, (unsigned) size);
	return p;
}

#define malloc2(size)        checked_malloc((size), __FILE__, __LINE__, __func__)
#define calloc2(nmemb, size) checked_calloc((nmemb), (size), __FILE__, __LINE__, __func__)
#endif /* CINKGO_UTIL_H_ */
