#include "shell.h"

/**
 * _eputs - Prints a string to the standard error stream (stderr).
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */

void _eputs(char *str)
{
int x = 0;

if (!str)
return;

while (str[x] != '\0')
{
_eputchar(str[x]);
x++;
}
}

/**
 * _eputchar - Writes a character to the standard error stream (stderr).
 * @c: The character to be written.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
static int x;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
{
write(2, buf, x);
x = 0;
}

if (c != BUF_FLUSH)
buf[x++] = c;

return (1);
}

/**
 * _putfd - Writes a character to a given file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
static int x;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
{
write(fd, buf, x);
x = 0;
}

if (c != BUF_FLUSH)
buf[x++] = c;

return (1);
}

/**
 * _putsfd - Prints a string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
int x = 0;

if (!str)
return (0);

while (*str)
{
x += _putfd(*str++, fd);
}

return (x);
}
