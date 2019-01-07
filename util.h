#ifndef UTIL_H_
#define UTIL_H_

/* Warning + terminate process */
void die(const char *format, ...) __attribute__ ((noreturn));

#define calloc2(nmemb, size) checked_calloc((nmemb), (size), __FILE__, __LINE__, __func__)
#endif /* UTIL_H_ */
