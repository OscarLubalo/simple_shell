#include "shell.h"

/**
* print_env - Print the current environment variables
* @info: Pointer to a structure containing potential arguments
* Return: Always 0
*/
int print_env(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
* get_env_value - Get the value of an environment variable
* @info: Pointer to a structure containing potential arguments
* @name: Name of the environment variable
* Return: The value of the environment variable or NULL if not found
*/
char *get_env_value(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* set_env_var - Initialize a new environment variable or modify an existing one
* @info: Pointer to a structure containing potential arguments
* Return: Always 0
*/
int set_env_var(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* unset_env_var - Remove an environment variable
* @info: Pointer to a structure containing potential arguments
* Return: Always 0
*/
int unset_env_var(info_t *info)
{
int t;

if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}
for (t = 1; t <= info->argc; t++)
_unsetenv(info, info->argv[t]);

return (0);
}

/**
* populate_env_list - Populate the environment linked list
* @info: Pointer to a structure containing potential arguments
* Return: Always 0
*/
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t t;

for (t = 0; environ[t]; t++)
add_node_end(&node, environ[t], 0);
info->env = node;
return (0);
}
