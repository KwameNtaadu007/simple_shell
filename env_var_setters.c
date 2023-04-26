#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @crdata: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, core_data *crdata)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; crdata->_environ[i]; i++)
	{
		var_env = _strdup(crdata->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(crdata->_environ[i]);
			crdata->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	crdata->_environ = _reallocdp(crdata->_environ, i, sizeof(char *) * (i + 2));
	crdata->_environ[i] = copy_info(name, value);
	crdata->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @crdata: data relevant (env name and env value)
 * Return: 1 on success.
 */
int _setenv(core_data *crdata)
{

	if (crdata->args[1] == NULL || crdata->args[2] == NULL)
	{
		catch_error(crdata, -1);
		return (1);
	}

	set_env(crdata->args[1], crdata->args[2], crdata);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 * @crdata: data relevant (env name)
 * Return: 1 on success.
 */
int _unsetenv(core_data *crdata)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (crdata->args[1] == NULL)
	{
		catch_error(crdata, -1);
		return (1);
	}
	k = -1;
	for (i = 0; crdata->_environ[i]; i++)
	{
		var_env = _strdup(crdata->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, crdata->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		catch_error(crdata, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; crdata->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = crdata->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(crdata->_environ[k]);
	free(crdata->_environ);
	crdata->_environ = realloc_environ;
	return (1);
}
