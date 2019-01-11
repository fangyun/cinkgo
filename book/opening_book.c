#include "opening_book.h"
#include <stdlib.h>

opening_book_t* opening_book_new() {
	opening_book_t* ob = malloc(sizeof(opening_book_t));
	return ob;
}
