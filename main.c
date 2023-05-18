#include <errno.h>
#include <sys/types.h>
#include "err.h"
#include "fmt.h"

void
print_pid(pid_t pid)
{
	char buf[512];
	FILE *f;
	int i = 0, c;

	sprintf(buf, "/proc/%d/cmdline", (int)pid);
	f = fopen(buf, "r");
	if (f == 0)
		Panic("%s: %d\n", buf, errno);
	while ((c = getc(f)) && c != EOF )
		buf[i++] = c;
	while ((c = getc(f)) && c != EOF)
		buf[i++] = c;
	if (i == 0)
		return;
	buf[i] = '\0';
	print(stdout, "%d:  %s\n", (int)pid, buf);
	fflush(stdout);
	fclose(f);
}

int
atoi__(const char *str)
{
	int neg;
	int n;

	neg = -1;
	n = 0;
	if (('+' == *str || '-' == *str) && '-' == *str++)
			neg = 1;
	while ('0' <= *str && *str <= '9')
		n = n * 10 - (*str++ - '0');
	return (neg * n);
}

void
print_maps(pid_t pid)
{
	char fname[512];
	unsigned long writable = 0, total = 0, shared = 0;

	sprintf(fname, "/proc/%ld/maps", (long)pid);
	f = fopen(fname, "r");
	if (f == 0)
		Panic("%s: %d\n", buf, errno);

	while (!feof(f))
	{
		char buf[PATH_MA
	}
}

int
main(int argc, char **argv)
{
	if (argc < 2)
		Panic("usage: %s [pid|/proc/pid] ...\n", argv[0]);
	for (int i = 1; i < argc; i++)
	{
		pid_t pid = atoi__(argv[i]);
		print_pid(pid);
		print_maps(pid);
	}		
}
