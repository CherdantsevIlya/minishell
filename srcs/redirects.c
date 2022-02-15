/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/14 17:53:43 by pkari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_input(t_shell *msh, int *i)
{
	msh->info->redirect_flag = 1;
	if (msh->info->error == 0)
	{
		if (msh->info->input_file != NULL)
		{
			close(msh->info->fd_input_file);
			free(msh->info->input_file);
			msh->info->input_file = NULL;
		}
		msh->info->input_file = ft_substr(msh->str, 0, *i);
		if (msh->info->input_file == NULL)
			errno_error(msh);
		msh->info->fd_input_file = open(msh->info->input_file, O_RDONLY, 0644);
		if (msh->info->fd_input_file == -1)
			errno_error(msh);
	}
	msh->info->token = 0;
}

void	redirect_output(t_shell *msh, int *i)
{
	if (msh->info->error == 0)
	{
		if (msh->info->output_file != NULL)
		{
			close(msh->info->fd_output_file);
			free(msh->info->output_file);
			msh->info->output_file = NULL;
		}
		msh->info->output_file = ft_substr(msh->str, 0, *i);
		if (msh->info->output_file == NULL)
			errno_error(msh);
		if (msh->info->token == TOKEN_REDIRECT_OUTPUT1)
			msh->info->fd_output_file = open(msh->info->output_file, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			msh->info->fd_output_file = open(msh->info->output_file, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		if (msh->info->fd_output_file == -1)
			errno_error(msh);
	}
	msh->info->token = 0;
}

static void	redirect_heredoc2(t_shell *msh)
{
	if (msh->info->heredoc != NULL)
	{
		close(msh->info->fd_heredoc_file);
		free(msh->info->heredoc);
		msh->info->heredoc = NULL;
	}
}

void	redirect_heredoc(t_shell *msh, int *i)
{
	char	*str;

	msh->info->redirect_flag = 2;
	redirect_heredoc2(msh);
	msh->info->heredoc = ft_substr(msh->str, 0, *i);
	if (msh->info->heredoc == NULL)
		errno_error(msh);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (!(ft_strcmp(msh->info->heredoc, str)))
		{
			free(str);
			break ;
		}
		msh->info->fd_heredoc_file = open(msh->info->heredoc, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		write(msh->info->fd_heredoc_file, str, ft_strlen(str));
		write(msh->info->fd_heredoc_file, "\n", 1);
		free(str);
	}
	msh->info->fd_heredoc_file = open(msh->info->heredoc, O_RDONLY, 0644);
	msh->info->token = 0;
}
