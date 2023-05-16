#include <stdlib.h>
#include "io.h"
#include "err.h"

void
Abort(void)
{
	pfmt(io_err, "aborting\n");
	flush(io_err);
	Exit("aborting");
}

void
Panic(char *s, int n)
{
	pfmt(io_err, "rc: ");
	pfmt(io_err, s, n);
	pchr(io_err, '\n');
	flush(io_err);
	Abort();
}

void
Exit (char *start)
{
	exit(1);
}
