#include <stdlib.h>
#include "rc.h"
#include "io.h"

void*
emalloc(long n)
{
	char *p = (char *)malloc(n);
	if (p == 0)
		panic("Can't malloc %d bytes", n);
	memset(p, 0, n);
	return (p);
}

void
efree(void *p)
{
	if (p)
		free(p);
	else pfmt(io_err, "free 0\n");
}
