#include "shell.h"

/**
* _custom_memset - fills memory with a constant byte
* @mem: the pointer to the memory area
* @value: the byte to fill @mem with
* @size: the amount of bytes to be filled
* Return: (mem) a pointer to the memory area mem
*/
char *_custom_memset(char *mem, char value, unsigned int size)
{
unsigned int y;

for (y = 0; y < size; y++)
mem[y] = value;
return (mem);
}

/**
* free_string_array - frees an array of strings
* @str_array: array of strings
*/
void free_string_array(char **str_array)
{
char **current_str = str_array;

if (!str_array)
return;

while (*str_array)
free(*str_array++);
free(current_str);
}

/**
* _custom_realloc - reallocates a block of memory
* @ptr: pointer to previously allocated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to the reallocated block.
*/
void *_custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *new_ptr;

if (!ptr)
return (malloc(new_size));
if (!new_size)
{
free(ptr);
return (NULL);
}
if (new_size == old_size)
return (ptr);

new_ptr = malloc(new_size);
if (!new_ptr)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
new_ptr[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (new_ptr);
}
