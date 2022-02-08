/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:16:15 by abridger          #+#    #+#             */
/*   Updated: 2022/02/08 03:08:38 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_init(t_shell *data, t_info *curr)
{
	(void) data;
	if (curr->token == TOKEN_PIPE)
		pipe(curr->fd_pipe);
}

//void	ft_pipe_close(t_shell *data, t_info *curr)
//{
//	if (curr->token != 1 && data->count > 1)
//	{
//		close(curr->prev->fd_pipe[0]);
//		close(curr->prev->fd_pipe[1]);
//	}
//}

void	ft_pipe_dup(t_shell *data, t_info *curr)
{
	if (data->count > 1 && !curr->prev)
	{
		//close(curr->fd_pipe[0]);
		//if (!curr->output_file)
		dup2(curr->fd_pipe[1], 1);
		close(curr->fd_pipe[1]);
	}
	if (data->count > 1 && curr->prev && curr->token == TOKEN_PIPE)
	{
		//close(curr->prev->fd_pipe[1]);
		//if (!curr->input_file)
		dup2(curr->prev->fd_pipe[0], 0);
		close(curr->fd_pipe[0]);
		//if (!curr->output_file)
		dup2(curr->fd_pipe[1], 1);
		close(curr->fd_pipe[1]);
	}
	if (data->count > 1 && curr->prev && curr->token != TOKEN_PIPE)
	{
		//close(curr->prev->fd_pipe[1]);
		//if (!curr->prev->input_file)
		dup2(curr->prev->fd_pipe[0], 0);
	}
}
