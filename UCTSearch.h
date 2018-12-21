/*
 * UCTSearch.h
 *
 *  Created on: Dec 21, 2018
 *      Author: yunfang
 */

#ifndef UCTSEARCH_H_
#define UCTSEARCH_H_

#include <future>

namespace TimeManagement {
enum enabled_t {
	UNIFORM = 0, EXITING = 1, SIMPLE = 2
};
}
;

class UCTSearch {
public:
	/*
	 Default memory limit in bytes.
	 ~1.3GiB on 32-bits and about 5.2GiB on 64-bits.
	 */
	static constexpr size_t DEFAULT_MAX_MEMORY = (
			sizeof(void*) == 4 ? 1'325'000'000 : 5'200'000'000);
	/*
	 Value representing unlimited visits or playouts. Due to
	 concurrent updates while multithreading, we need some
	 headroom within the native type.
	 */
	static constexpr auto UNLIMITED_PLAYOUTS = std::numeric_limits<int>::max()
			/ 2;
};

#endif /* UCTSEARCH_H_ */
