#include "main.h"

int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
unsigned char, int, int, unsigned char);
/**
 * handle_precision - Matches a precision modifier with
 * its corresponding value.
 * @args: va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter.
 *
 * Return: IF matched - its value,
 * If modifier is empty - zero,
 * or negative - 0.Otherwise - -1.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
int value = 0;

if (*modifier != '.')
return (-1);

modifier++;
(*index)++;

if ((*modifier <= '0' || *modifier > '9') &&
*modifier != '*')
{
if (*modifier == '0')
(*index)++;
return (0);
}

while ((*modifier >= '0' && *modifier <= '9') ||
(*modifier == '*'))
{
(*index)++;

if (*modifier == '*')
{
value = va_arg(args, int);
if (value <= 0)
return (0);
return (value);
}

value *= 10;
value += (*modifier - '0');
modifier++;
}

return (value);
}

/**
 * handle_specifiers - Matches
 * a conversion specifier
 * with conversion function.
 * @specifier: A pointer to a potential
 * conversion specifier.
 *
 * Return: pointer to the function
 * or NULL
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
unsigned char, int, int, unsigned char)
{
int i;
converter_t converters[] = {
{'c', convert_c},
{'s', convert_s},
{'d', convert_di},
{'i', convert_di},
{'%', convert_percent},
{'b', convert_b},
{'u', convert_u},
{'o', convert_o},
{'x', convert_x},
{'X', convert_X},
{'S', convert_S},
{'p', convert_p},
{'r', convert_r},
{'R', convert_R},
{0, NULL}};

for (i = 0; converters[i].func; i++)
{
if (converters[i].specifier == *specifier)
return (converters[i].func);
}

return (NULL);
}
