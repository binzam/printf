#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag
 * @wid: A width.
 * @prec: A precision.
 * @len: A length.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char ch;
unsigned int cxrs = 0;

(void)prec;
(void)len;

ch = va_arg(args, int);

cxrs += print_width(output, cxrs, flags, wid);
cxrs += _memcpy(output, &ch, 1);
cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}

/**
 * convert_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag
 * @wid: A width.
 * @prec: A precision.
 * @len: A length.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char percent = '%';
unsigned int cxrs = 0;

(void)args;
(void)prec;
(void)len;

cxrs += print_width(output, cxrs, flags, wid);
cxrs += _memcpy(output, &percent, 1);
cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag
 * @wid: A width.
 * @prec: A precision.
 * @len: A length.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char *null = "(nil)";
unsigned long int address;
unsigned int cxrs = 0;

(void)len;

address = va_arg(args, unsigned long int);
if (address == '\0')
return (_memcpy(output, null, 5));

flags |= 32;
cxrs += convert_ubase(output, address, "0123456789abcdef",
flags, wid, prec);
cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}
