#include "shell.h"

/**
 * sig_hdlr - signal handler for SIGINT
 * @sig: the signal number
 */
void sig_hdlr(int sig)
{
	char *new_prmpt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_hdlr);
	write(STDIN_FILENO, new_prmpt, 3);
}
