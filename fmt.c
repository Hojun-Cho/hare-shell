#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmt.h"

void
Panic(char *s, ...)
{
	va_list ap;

	va_start(ap, s);
	pfmt(stderr, s, ap);
	va_end(ap);
	fflush(stderr);
	exit(1);
}

void
pfmt(FILE *f, char *fmt, va_list ap)
{
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
	fflush(f);
}

void
print(FILE *f, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	pfmt(f, fmt, ap);
	va_end(ap);
}

void
pchr(FILE *f, char c)
{
	if (fwrite(&c, sizeof(char), 1, f) == 1)
		return ;
	Panic("Can't Write\n");	
}

void
pstr(FILE *f, char *s)
{
	size_t exp;

	exp = strlen(s);
	if (s == 0)
		s = "(null)";
	if ((exp != fwrite(s, sizeof(char), strlen(s), f)))
		Panic("Can't Write\n");
}

void
pdec(FILE *f, int n)
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


