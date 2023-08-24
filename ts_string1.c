#include "shell.h"

/**
 * _strcpy - Copies string
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: A pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
	int s = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[s])
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: The pointer to a duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	int length,s = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	else
	{(s == 0; s <= length; s++);
                ret[s] = str[s];
	}

	return (ret);
}

/**
 * _puts - Prints string to stdout
 * @str: String to print
 *
 * Return: None
 */
void _puts(const char *str)
{
	int s = 0;

	if (str == NULL)
		return;

	while (str[s])
	{
		_putchar(str[s]);
		s++;
	}
}

/**
 * _putchar - Writes a character to stdout
 * @c: Character to write
 *
 * Return: Success 1.Error, -1 is returned.
 */
int _putchar(char c)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(1, buf, s);
		s = 0;
	}

	if (c != BUF_FLUSH)
		buf[s++] = c;

	return (1);
}
