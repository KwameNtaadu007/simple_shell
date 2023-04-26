#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @crdata: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(core_data *crdata)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, crdata);
	dir = crdata->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, crdata);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	string_reverse(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			string_reverse(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, crdata);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", crdata);
	}
	crdata->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @crdata: data relevant (directories)
 * Return: no return
 */
void cd_to(core_data *crdata)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = crdata->args[1];
	if (chdir(dir) == -1)
	{
		catch_error(crdata, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, crdata);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, crdata);

	free(cp_pwd);
	free(cp_dir);

	crdata->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @crdata: data relevant (environ)
 * Return: no return
 */
void cd_previous(core_data *crdata)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", crdata->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, crdata);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, crdata);
	else
		set_env("PWD", cp_oldpwd, crdata);

	p_pwd = _getenv("PWD", crdata->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	crdata->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @crdata: data relevant (environ)
 * Return: no return
 */
void cd_to_home(core_data *crdata)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", crdata->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, crdata);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		catch_error(crdata, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, crdata);
	set_env("PWD", home, crdata);
	free(p_pwd);
	crdata->status = 0;
}

