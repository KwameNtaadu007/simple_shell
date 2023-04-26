#include "main.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @signal_num: Signal handler
 */
void get_sigint(int signal_num)
{
	(void)signal_num;
	write(STDOUT_FILENO, "\n ):$ ", 5);
}

