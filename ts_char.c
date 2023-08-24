#include "shell.h"

/**
 * is_chain - checks the current character in the buffer
 * @info: Parameter struct.
 * @buf: Character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;
	int chain_type = 0;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		chain_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		chain_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		chain_type = CMD_CHAIN;
	}

	if (chain_type != 0)
	{
		info->cmd_buf_type = chain_type;
		*p = k;
		return (1);
	}

	return (0);
}

/**
 * check_chain - Checks if chaining should continue based on the last status.
 * @info: Parameter struct.
 * @buf: Character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t n, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[n] = 0;
		k = len;
	}
	else if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[n] = 0;
		k = len;
	}

	*p = k;
}

/**
 * replace_alias - Replaces aliases in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (node)
		{
			free(info->argv[0]);
			p = _strchr(node->str, '=');
			if (p)
			{
				info->argv[0] = _strdup(p + 1);
				return (1);
			}
		}
	}

	return (0);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] == '$' && info->argv[n][1])
		{
			if (!_strcmp(info->argv[n], "$?"))
			{
				replace_string(&(info->argv[n]),
						_strdup(convert_number(info->status, 10, 0)));
			}
			else if (!_strcmp(info->argv[n], "$$"))
			{
				replace_string(&(info->argv[n]), _strdup(convert_number(getpid(), 10, 0)));
			}
			else
			{
				node = node_starts_with(info->env, &info->argv[n][1], '=');
				if (node)
				{
					replace_string(&(info->argv[n]), _strdup(_strchr(node->str, '=') + 1));
				}
				else
				{
					replace_string(&info->argv[n], _strdup(""));
				}
			}
		}
	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
