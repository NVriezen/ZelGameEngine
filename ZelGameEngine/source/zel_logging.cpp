#include <zel_logging.h>
#include <stdio.h>
#include <stdarg.h>

//TODO: consider making this a macro again, so we can remove it in release builds
void zel_print(const char* format, ...)
{
	va_list start;
	va_start(start, format);
	vprintf(format, start);
	va_end(start);
}