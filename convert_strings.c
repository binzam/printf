#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_s - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_s(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char *str, *null = "(null)";
int size;
unsigned int cxrs = 0;

(void)flags;
(void)len;

str = va_arg(args, char *);
if (str == NULL)
return (_memcpy(output, null, 6));

for (size = 0; *(str + size);)
size++;

cxrs += print_string_width(output, flags, wid, prec, size);

prec = (prec == -1) ? size : prec;
while (*str != '\0' && prec > 0)
{
cxrs += _memcpy(output, str, 1);
prec--;
str++;
}

cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}

/**
 * convert_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag
 * @wid: A width
 * @prec: A precision
 * @len: A length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int convert_S(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char *str, *null = "(null)", *hex = "\\x", zero = '0';
int size, index;
unsigned int cxrs = 0;

(void)len;
str = va_arg(args, char *);
if (str == NULL)
return (_memcpy(output, null, 6));

for (size = 0; str[size];)
size++;

cxrs += print_string_width(output, flags, wid, prec, size);

prec = (prec == -1) ? size : prec;
for (index = 0; *(str + index) != '\0' && index < prec; index++)
{
if (*(str + index) < 32 || *(str + index) >= 127)
{
cxrs += _memcpy(output, hex, 2);
if (*(str + index) < 16)
cxrs += _memcpy(output, &zero, 1);
cxrs += convert_ubase(output, *(str + index),
"0123456789ABCDEF", flags, 0, 0);
continue;
}
cxrs += _memcpy(output, (str + index), 1);
}

cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}
/**
 * convert_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag
 * @wid: A width
 * @prec: A precision
 * @len: A length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_r(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char *str, *null = "(null)";
int size, end, i;
unsigned int cxrs = 0;

(void)flags;
(void)len;

str = va_arg(args, char *);
if (str == NULL)
return (_memcpy(output, null, 6));

for (size = 0; *(str + size);)
size++;

cxrs += print_string_width(output, flags, wid, prec, size);

end = size - 1;
prec = (prec == -1) ? size : prec;
for (i = 0; end >= 0 && i < prec; i++)
{
cxrs += _memcpy(output, (str + end), 1);
end--;
}

cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}

/**
 * convert_R - Converts a string to ROT13
 * @args: A va_list pointing to the string to be converted.
 * @flags: Flag
 * @wid: A width
 * @prec: A precision
 * @len: A length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_R(va_list args, buffer_t *output,
unsigned char flags, int wid, int prec, unsigned char len)
{
char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
char *str, *null = "(null)";
int i, j, size;
unsigned int cxrs = 0;

(void)flags;
(void)len;

str = va_arg(args, char *);
if (str == NULL)
return (_memcpy(output, null, 6));

for (size = 0; *(str + size);)
size++;

cxrs += print_string_width(output, flags, wid, prec, size);

prec = (prec == -1) ? size : prec;
for (i = 0; *(str + i) != '\0' && i < prec; i++)
{
for (j = 0; j < 52; j++)
{
if (*(str + i) == *(alpha + j))
{
cxrs += _memcpy(output, (rot13 + j), 1);
break;
}
}
if (j == 52)
cxrs += _memcpy(output, (str + i), 1);
}

cxrs += print_neg_width(output, cxrs, flags, wid);

return (cxrs);
}
