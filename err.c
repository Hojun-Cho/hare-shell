#include <stdlib.h>
#include "io.h"
#include "err.h"

void
Abort(void)
{
	pfmt(err, "aborting\n");
	flush(err);
	Exit("aborting");
}

void
Panic(char *s, int n)
{
	pfmt(err, "rc: ");
	pfmt(err, s, n);
	pchr(err, '\n');
	flush(err);
	Abort();
}

void
Exit (char *start)
{
	exit(1);
}
