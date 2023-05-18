#ifndef RC_IO
# define RC_IO

#include <unistd.h>
#include <stdio.h>

#define NBUF	512
#define ERRMAX	10

void Panic(char *s, ...);
void pfmt(FILE *f, char *fmt, va_list ap);
void print(FILE *f, char *fmt, ...);
long Write(int fd, void *buf, long cnt);
FILE* openfd(int fd);
void pchr(FILE *b, char c);
void pstr(FILE *f, char *s);
void pdec(FILE *f, int n);

#endif
