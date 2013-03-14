#include <err.h>
#include "util.h"

void *emalloc (size_t size) {
	void *p;

	p = malloc (size);
	if (!p)
		err (1, "malloc");
	return p;
}
