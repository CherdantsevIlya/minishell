/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:16:15 by abridger          #+#    #+#             */
/*   Updated: 2022/02/06 23:51:33 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_init(t_shell *data, t_info *curr)
{
	if (curr->token == TOKEN_PIPE)
		pipe(data->fd_pipe);
}

void	ft_pipe_close(t_shell *data, t_info *curr)
{
	if (curr->token != 1 && data->count > 1)
	{
		close(data->fd_pipe[0]);
		close(data->fd_pipe[1]);
	}
}

void	ft_pipe_dup(t_shell *data, t_info *curr)
{
	if (data->count > 1 && curr->prev && !curr->prev->input_file)
	{
		dup2(data->fd_pipe[0], 0);
		close(data->fd_pipe[0]);
	}
	if (data->count > 1 && curr->prev && !curr->prev->output_file)
	{
		dup2(data->fd_pipe[1], 1);
		close(data->fd_pipe[1]);
	}
	if (curr->token != 1 && data->count > 1)
	{
		close(data->fd_pipe[0]);
		close(data->fd_pipe[1]);
	}
}

/*
void	ft_pipe_dup_c(t_shell *data, t_info *curr)
{
	if (data->count > 1 && curr->prev && curr->prev->token == TOKEN_PIPE)
	{
		dup2(data->fd_pipe[0], 0);
		close(data->fd_pipe[0]);
	}
	if (data->count > 1 && curr->token == TOKEN_PIPE)
	{
		dup2(data->fd_pipe[1], 1);
		close(data->fd_pipe[1]);
	}
	if (curr->token != 1 && data->count > 1)
	{
		close(data->fd_pipe[0]);
		close(data->fd_pipe[1]);
	}
}
*/
