#ifndef CINKGO_THIRDPARTY_HASH_H_
#define CINKGO_THIRDPARTY_HASH_H_

typedef struct {
	int i;
} hash_t;

int randome_next_int(hash_t* random, int up_bound);

#endif /* CINKGO_THIRDPARTY_HASH_H_ */
