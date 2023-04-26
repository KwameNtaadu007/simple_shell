#include "main.h"

/**
 * ch_dir - changes current directory
 *
 * @crdata: data relevant
 * Return: 1 on success
 */
int ch_dir(core_data *crdata)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = crdata->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(crdata);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(crdata);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(crdata);
		return (1);
	}

	cd_to(crdata);

	return (1);
}

