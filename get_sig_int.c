#include "mymain.h"

/**
 * get_sigint - Handles the crtl (plus +) c call in prompt...
 *
 * @sig: Signal handler.,,
 *
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$  ", 5);
}
