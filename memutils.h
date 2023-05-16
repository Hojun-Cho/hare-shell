#ifndef MEM_UTILS
#define  MEM_UTILS

#define new(type)	((type *)emalloc(sizeof(type)))
typedef unsigned long ulong;

void *emalloc(long);
void efree(void *p);

#endif
