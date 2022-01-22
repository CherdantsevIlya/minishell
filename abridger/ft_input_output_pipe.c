/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_output_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:56:15 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 23:03:33 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_saved_fd(t_data *data)
{
	data->save_in = dup(0);
	data->save_out = dup(1);
}

int	ft_try_input(t_data *data, t_cmd *curr)
{
	int		check;

	check = 0;
	if (curr && check == 0) // curr можно убрать, только до этого проверить на curr
	{
		if (curr->red_flag == 2)
		{
			check = 1;
			if (!curr->red_list)
				return (put_err_message("syntax error near \
					unexpected token `newline'"));
			else
			{
				data->fd_red[0] = open(curr->red_list->name, O_RDONLY); // ? add loop if more than 1 file
				if (data->fd_red[0] == -1)
					return (ft_error(1, data, "Wrong file name: ")); // errno
			}
		}
	}
	if (check == 0)
		data->fd_red[0] = dup(data->save_in);
	dup2(data->fd_red[0], 0); // копировать надо только если есть пайп или будет форк?
	close(data->fd_red[0]);
	return (0);
}

int	ft_try_output(t_data *data, t_cmd *curr)
{
	int		check; // check можно убрать, усди проверим на curr

	check = 0;
	if (curr && check == 0) // curr можно убрать, только до этого проверить на curr
	{
		if (curr->red_flag == 1)
		{
			check = 1;
			if (!curr->red_list)
				return (put_err_message("syntax error near \
					unexpected token `newline'"));
			else
			{
				data->fd_red[1] = open(curr->red_list->name, O_WRONLY | O_CREAT | O_TRUNC, 0666); // ? add loop if more than 1 file
				if (data->fd_red[1] == -1)
					return (ft_error(1, data, "Error file: ")); // errno
			}
		}
	}
	if (check == 0)
		data->fd_red[1] = dup(data->save_out);
	return (0);
}

void	ft_check_pipe(t_data *data, t_cmd *curr)
{
	if (curr->pipe_flag == 1)
	{
		pipe(data->fd_pipe);
		data->fd_red[1] = data->fd_pipe[1];
		data->fd_red[0] = data->fd_pipe[0];
		dup2(data->fd_red[1], 1); // перенести перед пайпом? и копировать только если будет пайп или форк?
		close(data->fd_red[1]);
	}
	else
	{
		dup2(data->fd_red[1], 1); // копировать надо только если есть пайп или будет форк?
		close(data->fd_red[1]);
	}
}

void	ft_close_saved_fd(t_data *data)
{
	dup2(data->save_in, 0);
	dup2(data->save_out, 1);
	close(data->save_in);
	close(data->save_out);
}
