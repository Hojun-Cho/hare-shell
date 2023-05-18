#include <errno.h>
#include <sys/types.h>
#include "err.h"
#include "fmt.h"

#define PATH_MAX 512

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
	FILE *f = fopen(fname, "r");
	if (f == 0)
		Panic("%s: %d\n", fname, errno);

	while (!feof(f))
	{
		char buf[PATH_MAX + 100], perm[5], dev[6], mapname[PATH_MAX];
		unsigned long begin, end, size, inode, foo;
		int n;
		
		if (fgets(buf, sizeof(buf), f) == 0)
			break;
		mapname[0] = '\0';
		sscanf(buf, "%lx-%lx %4s %lx %5s %ld %s", &begin, &end, perm,
			&foo, dev, &inode, mapname);
		size = end - begin;
		total += size;
		if (perm[3] == 'p')
		{
			if (perm[1] == 'w')
				writable += size;
		}
		else if (perm[3] =='s')
			shared += size;
		else 
			Panic("unable to parse permission string: %s\n", perm);
		n = sprintf(buf, "%08lx (%ld KB)", begin, (end - begin)/1024);
		fwrite(buf, sizeof(char), n, stdout);	
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
