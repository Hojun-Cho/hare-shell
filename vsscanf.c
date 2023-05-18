#include <stddef.h>

struct StringScannerState {
	const unsigned char *s;
	size_t i;
};

static int
vsscanfcb(void *arg)
{
	int res;
	struct StringScanerState *state = arg;

	if ((res = state->s[state->i]))
	{
		state->i++;
	}
	else 
	{
		res = -1;
	}
	return res;
}

int
vsscanf(const char *str, const char *fmt, va_list va)
{
	struct StringScanerState state = {(const unsigned char *)str, 0};
	return vcsanf(vscanfcb, NULL, &state, fmt, va);
}
