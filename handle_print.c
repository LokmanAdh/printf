#include "main.h"
/**
 * handle_print - Prints each argument based on its format
 * @fmt: Format
 * @list: List of arguments to print
 * @ind: ind
 * @buffer: Buffer array
 * @flags: Get flags
 * @width: Get width
 * @precision: Get precision
 * @size: get size
 * Return: 1 or 2
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'d', print_int},
		{'i', print_int}, {'%', print_percent}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hex},
		{'X', print_HEX}, {'S', print_non_printable}, {'p', print_pointer},
		{'r', print_rev}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
