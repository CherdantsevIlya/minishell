#include "../includes/minishell.h"

void ctrl_c(int signal)
{
	signal = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "   \n", 4);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void ctrl_d(void)
{
	write(1, "exit\n", 5);
	rl_redisplay();
	exit(0);
}

