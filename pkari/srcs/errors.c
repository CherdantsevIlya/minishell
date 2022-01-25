#include "../includes/minishell.h"

int syntax_error(t_shell *msh, char *str, int len)
{
	if (str[0] == 0)
	{
		write(2, "minishell: syntax error near unexpected token `newline'",55);
		write(2, "\n", 1);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, str, len);
		write(2, "'\n", 2);
	}
	msh->exit_status = 258;
	return (1);
}

void errno_error(t_shell *msh)
{
	perror("minishell");
	msh->exit_status = 1;
	msh->info->error = 1;
	msh->info->token = 0;
}

