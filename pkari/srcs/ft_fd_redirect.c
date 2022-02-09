/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:56:15 by abridger          #+#    #+#             */
/*   Updated: 2022/02/10 02:13:33 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_saved_fd(t_shell *data)
{
	data->save_in = dup(0);
	data->save_out = dup(1);
}

void	ft_close_saved_fd(t_shell *data)
{
	dup2(data->save_in, 0);
	dup2(data->save_out, 1);
	close(data->save_in);
	close(data->save_out);
}

void	ft_redirect_dup(t_info *curr)
{
	if (curr->fd_input_file != -2)
	{
		dup2(curr->fd_input_file, 0);
		close(curr->fd_input_file);
	}
	if (curr->fd_output_file != -2)
	{
		dup2(curr->fd_output_file, 1);
		close(curr->fd_output_file);
	}
}

void	ft_close_files1(t_info *curr)
{
	if (curr->prev && curr->prev->fd_input_file != -2)
		close(curr->prev->fd_input_file);
	if (curr->prev && curr->prev->fd_output_file != -2)
		close(curr->prev->fd_output_file);
	if (curr->fd_input_file != -2)
		close(curr->fd_input_file);
	if (curr->fd_output_file != -2)
		close(curr->fd_output_file);
}

void	ft_close_files2(t_info *curr)
{
	t_info *tmp;

	tmp = curr;
	while(tmp)
	{
		if (tmp->fd_input_file != -2)
			close(tmp->fd_input_file);
		if (tmp->fd_output_file != -2)
			close(tmp->fd_output_file);
		tmp = tmp->prev;
	}
}
