#include "minishell.h"

void redirect_input(t_shell *msh, int *i)
{
	if (msh->info->error == 0)
	{
		if (msh->info->input_file != NULL)
		{
			close(msh->info->fd_input_file);
			free(msh->info->input_file);
			msh->info->input_file = NULL;
		}
		msh->info->input_file = ft_strdup(msh->str, 0 , *i);
		if (msh->info->input_file == NULL)
			ERROR();
		msh->info->fd_input_file = open(msh->info->input_file, O_RDONLY, 0644);
		if (msh->info->fd_input_file == -1)
			ERROR();
	}
}

void redirect_output(t_shell *msh, int *i)
{
	if (msh->info->error == 0)
	{
		if (msh->info->output_file != NULL)
		{
			close(msh->info->fd_output_file);
			free(msh->info->output_file);
			msh->info->output_file = NULL;
		}
		msh->info->output_file = ft_strdup(msh->str, 0 , *i);
		if (msh->info->output_file == NULL)
			ERROR();
		if (msh->info->token == TOKEN_REDIRECT_OUTPUT1)
			msh->info->fd_output_file = open(msh->info->output_file, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
		else
			msh->info->fd_output_file = open(msh->info->output_file, O_WRONLY
			| O_CREAT | O_APPEND, 0644);
		if (msh->info->fd_output_file == -1)
			ERROR();
	}
}

void redirect_heredoc(t_shell *msh, int *i)
{

}