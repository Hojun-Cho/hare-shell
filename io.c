#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include "io.h"
#include "err.h"

long
Write(int fd, void *buf, long cnt)
{
	return write(fd, buf, cnt);
}

void
flush(io *f)
{
	int n;
	char *s;

	if (f->strp) {
		n = f->ebuf - f->strp;
		f->strp = realloc(f->strp, n+101);
		if (f->strp == 0)
			Panic("Can't realloc %d bytes in flush!", n+101);
		f->bufp = f->strp + n;
		f->ebuf = f->bufp + 100;
		for (s = f->bufp; s <= f->ebuf; s++) *s = '\0';	
	}
	else {
		n = f->bufp - f->buf;
		if (n && Write(f->fd, f->buf, n) < 0) {
			Write(3, "Write error\n", 12);
		}
		f->bufp = f->buf;
		f->ebuf = f->buf + NBUF;
	}
}

int
fullbuf(io *f, int c)
{
	flush(f);
	return *f->bufp++ = c;
}

void
pchr(io *b, int c)
{
	if (b->bufp == b->ebuf)
		fullbuf(b, c);
	else *b->bufp++ = c;
}

void
pstr(io *f, char *s)
{
	if (s == 0)
		s = "(null)";
	while (*s) pchr(f, *s++);
}

void
pdec(io *f, int n)
{
	if (n < 0) {
		if (n != INT_MIN) {
			pchr(f, '-');
			pdec(f, -n);
			return ;
		}
		n = -(INT_MIN + 1);
		pchr(f, '-');
		pdec(f, n / 10);
		pchr(f, n % 10 + '1');
		return ;
	}
	if (n > 9)
		pdec(f, n / 10);
	pchr(f, n % 10 + '0');
}

void
pfmt(io *f, char *fmt, ...)
{
	va_list ap;
	char err[ERRMAX];

	va_start(ap, fmt);
	for(;*fmt;fmt++)
		if(*fmt!='%')
			pchr(f, *fmt);
		else switch (*++fmt){
		case '\0':
			va_end(ap);
			return;
		case 'c':
			pchr(f, va_arg(ap, int));
			break;
		case 'd':
			pdec(f, va_arg(ap, int));
			break;
		case 's':
			pstr(f, va_arg(ap, char *));
			break;
		default:
			pchr(f, *fmt);
			break;
		}
	va_end(ap);
	flush(f);
}


