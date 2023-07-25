#include "main.h"

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - helper function for _printf
 * @args: A va_list of arguments
 * @output: A buffer_t struct
 */
void cleanup(va_list args, buffer_t *output)
{
va_end(args);

write(1, output->start, output->len);
free_buffer(output);
}

/**
 * run_printf - Reads through the format string
 *
 * @format: Character string to print
 * @output: A buffer_t struct containing a buffer
 * @args: A va_list of arguments
 *
 * Return: The number of characters stored to output.
*/
int run_printf(const char *format, va_list args, buffer_t *output)
{
	int i, width, prec, cxrs = 0;
	char tmp;

	unsigned char flags, len;
unsigned int (*f)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + i + 1, &tmp);
			width = handle_width(args, format + i + tmp + 1, &tmp);
			prec = handle_precision(args, format + i + tmp + 1, &tmp);
			len = handle_length(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f)
			{
				i += tmp + 1;
				cxrs += f(args, output, flags, width, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				cxrs = -1;
				break;
			}
		}
		cxrs += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (cxrs);
}

/**
 * _printf - Outputs a formated string
 *
 * @format: character string
 * Return: number of characters to be printed
*/
int _printf(const char *format, ...)
{
buffer_t *output;
va_list args;
int cxrs;

if (!format)
return (-1);
output = init_buffer();
if (!output)
return (-1);

va_start(args, format);

cxrs = run_printf(format, args, output);

return (cxrs);
}
