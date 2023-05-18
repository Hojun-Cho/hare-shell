int
vcsabf(int callback(void *), int unget(int , void *), void *arg,
	const char *fmt, va_list va)
{
	struct FreeMe
	{
		struct FreeMe *next;
		void *ptr;
	} *freeme = NULL;

}
	
