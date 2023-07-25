#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
unsigned char flags, int wid);

/**
 * print_width - Stores leading spaces to a buffer for a width
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag
 * @wid: A width
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_width(buffer_t *output, unsigned int printed,
unsigned char flags, int wid)
{
unsigned int cxrs = 0;
char width = ' ';

if (NEG_FLAG == 0)
{
for (wid -= printed; wid > 0;)
cxrs += _memcpy(output, &width, 1);
}

return (cxrs);
}

/**
 * print_string_width - Stores leading spaces to a buffer for width
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag
 * @wid: width
 * @prec: precision
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_string_width(buffer_t *output,
unsigned char flags, int wid, int prec, int size)
{
unsigned int cxrs = 0;
char width = ' ';

if (NEG_FLAG == 0)
{
wid -= (prec == -1) ? size : prec;
for (; wid > 0; wid--)
cxrs += _memcpy(output, &width, 1);
}

return (cxrs);
}

/**
 * print_neg_width - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: Flag
 * @wid: A width
 *
 * Return: The number of bytes stored to the buffer.
 */
uinsigned int print_neg_width(buffer_t *output, unsigned int printed,
unsigned char flags, int wid)
{
unsigned int cxrs = 0;
char width = ' ';

if (NEG_FLAG == 1)
{
for (wid -= printed; wid > 0; wid--)
cxrs += _memcpy(output, &width, 1);
}

return (cxrs);
}
