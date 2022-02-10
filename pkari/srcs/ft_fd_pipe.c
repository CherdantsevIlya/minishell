/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 22:16:15 by abridger          #+#    #+#             */
/*   Updated: 2022/02/10 23:30:54 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_init(t_shell *data, t_info *curr)
{
	(void) data;
	if (curr->token == TOKEN_PIPE)
		pipe(curr->fd_pipe);
}

void	ft_pipe_close(t_shell *data, t_info *curr)
{
	t_info	*tmp;
	
	tmp = NULL;
	if (data->count > 1)
	{
		tmp = curr;
		while (tmp && tmp->token == TOKEN_PIPE)
		{
			close(tmp->fd_pipe[0]);
			close(tmp->fd_pipe[1]);
			tmp = tmp->next;
		}
	}
	
}

void	ft_pipe_dup(t_shell *data, t_info *curr)
{
	if (data->count > 1 && !curr->prev)
	{
		close(curr->fd_pipe[0]);
		dup2(curr->fd_pipe[1], 1);
		//close(curr->fd_pipe[1]);
	}
	if (data->count > 1 && curr->prev && curr->token == TOKEN_PIPE)
	{
		close(curr->prev->fd_pipe[1]);
		dup2(curr->prev->fd_pipe[0], 0);
		close(curr->fd_pipe[0]);
		dup2(curr->fd_pipe[1], 1);
		//close(curr->fd_pipe[1]);
	}
	if (data->count > 1 && curr->prev && curr->token != TOKEN_PIPE)
	{
		close(curr->prev->fd_pipe[1]);
		dup2(curr->prev->fd_pipe[0], 0);
		//close(curr->prev->fd_pipe[0]);
	}
}

void	ft_dup_add(t_shell *data, t_info *curr)
{
	if (data->count > 1 && curr->prev && curr->token != TOKEN_PIPE)
	{
		if (curr->fd_output_file == -2)
		{
			dup2(data->save_out, 1);
			//close(data->save_out); // висит, если раскомментить
		}
	}
	if (data->count > 1 && !curr->prev)
	{
		if (curr->fd_input_file == -2)
		{
			dup2(data->save_in, 0);
			//close(data->save_in); // висит, если раскомментить
		}
	}
}
