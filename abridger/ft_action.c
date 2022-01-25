/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/01/25 21:50:12 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	action(t_shell *data, char **envp) // for testing envp delete
{
	data = (t_shell *)malloc(sizeof(t_shell));
	if (!data)
		return (ft_error(1, NULL, "Malloc: "));
	else
	{
		ft_init_data(data, envp);
		// ft_read_exec(data, envp);
		// ft_test_readline(); // test
		ft_print_array(data); // test
		ft_print_lsts(data); // test
		// ft_data_clear(data);
	}
	return (0);
}

void	ft_simple_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	char	**env_array;

	env_array = create_array_env(data, NULL); // all?
	ft_redirect_dup(curr);
	ft_pipe_init(data, curr);
	if (curr->nb_cmd < 7 && curr->nb_cmd > 0 && !curr->is_pipe)
		(func)[curr->nb_cmd](data, curr);
	else
	{
		data->pid = fork();
		if (data->pid == -1)
			return (ft_error(10, data, "Fork error"));
		else if (data->pid == 0)
			ft_exec_in_child(data, curr, env_array);
	}
	ft_array_clear(env_array);
}

void	ft_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	char	**env_array;

	env_array = create_array_env(data, NULL); // all?
	ft_redirect_dup(curr);
	ft_pipe_init(data, curr);
	data->pid = fork();
	if (data->pid == -1)
		return (ft_error(10, data, "Fork error"));
	else if (data->pid == 0)
	{
		if (curr->nb_cmd < 7 && curr->nb_cmd > 0 && !curr->is_pipe)
			(func)[curr->nb_cmd](data, curr);
		else
			ft_exec_in_child(data, curr, env_array);
	}
	ft_array_clear(env_array);
}

void	ft_execution_cycle(t_shell *data)
{
	t_info		*curr;
	t_builtin	*func;
	int			status;

	curr = data->info;
	data->count = ft_lstsize(curr);
	func = create_array_function();
	while (curr)
	{
		ft_simple_execute(data, curr, func);
		ft_execute(data, curr, func);
		curr = curr->next;
	}
	waitpid(-1, &status, 0);
	free(func);
}
