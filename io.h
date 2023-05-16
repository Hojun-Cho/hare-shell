#ifndef RC_IO
# define RC_IO

#include <unistd.h>

#define NBUF	512
#define ERRMAX	10

typedef struct{
	int fd;
	char *bufp, *ebuf, *strp, buf[NBUF];
}io;

extern io *io_err;

long Write(int fd, void *buf, long cnt);
int fullbuf(io *f, int c);
void flush(io *f);

void pfmt(io *f, char *fmt, ...);
void pchr(io *b, int c);
void pstr(io *f, char *s);
void pdec(io *f, int n);

#endif
