/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/01/27 22:53:08 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	action(t_shell *data, char **envp) // for testing
{
	data = (t_shell *)malloc(sizeof(t_shell));
	if (!data)
		return (ft_error(NULL, "Malloc: "));
	else
	{
		ft_init_data(data, envp);
		// ft_define_cmd(data); // after parser
		// ft_execution_cycle(data);
		// ft_read_exec(data, envp); // test
		// ft_test_readline(); // test
		// ft_print_array(data); // test
		ft_print_lsts(data); // test
		ft_data_clear(data);
	}
	return (0);
}

void	ft_define_cmd(t_shell *data)
{
	t_info	*curr;

	curr = NULL;
	if (data->info)
		curr = data->info;
	while (curr)
	{
		if (curr->argv && !ft_strcmp(curr->argv[0], "echo"))
			curr->nb_cmd = 0;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "cd"))
			curr->nb_cmd = 1;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "pwd"))
			curr->nb_cmd = 2;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "export"))
			curr->nb_cmd = 3;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "unset"))
			curr->nb_cmd = 4;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "exit"))
			curr->nb_cmd = 5;
		else if (curr->argv && !ft_strcmp(curr->argv[0], "env"))
			curr->nb_cmd = 6;
		else if (curr->argv)
			curr->nb_cmd = 7;
		curr = curr->next;
	}
}

int	ft_simple_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	char	**env_array;

	if (data->count == 1)
	{
		ft_redirect_dup(curr);
		ft_pipe_init(data, curr);
		if (curr->nb_cmd < 7 && curr->nb_cmd > 0 && !curr->is_pipe)
			return ((func)[curr->nb_cmd](data, curr));
		else
		{
			data->pid = fork();
			if (data->pid == -1)
				return (ft_error(data, ft_one_colon("fork")));
			else if (data->pid == 0)
			{
				env_array = create_array_env(data, NULL);
				return (ft_run_execve(data, curr, env_array));
			}
		}
	}
	return (0);
}

int	ft_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	char	**env_array;

	if (data->count > 1)
	{
		ft_redirect_dup(curr);
		ft_pipe_init(data, curr);
		data->pid = fork();
		if (data->pid == -1)
			return (ft_error(data, ft_one_colon("fork")));
		else if (data->pid == 0)
		{
			if (curr->nb_cmd < 7 && curr->nb_cmd > 0 && !curr->is_pipe)
				return ((func)[curr->nb_cmd](data, curr));
			else
			{
				env_array = create_array_env(data, NULL);
				ft_run_execve(data, curr, env_array);
			}
		}
	}
	return (0);
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
