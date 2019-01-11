#include "time_descender.h"
#include <stdlib.h>

time_descender_t* time_descender_new() {
	time_descender_t* td = malloc(sizeof(time_descender_t));
	return td;
}
