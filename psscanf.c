int
sscanf(const char *str, const char *fmt, ...)
{
	int rc;
	va_list va;

	va_start(va, fmt);
	rc = vsscanf(str, fmt, va);
	va_end(va);
	return rc;
}
