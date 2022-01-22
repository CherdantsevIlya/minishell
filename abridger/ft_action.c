/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 19:50:28 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	action(t_data *data, char **envp)
{
	data = (t_data *)malloc(sizeof(t_data));
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

void	ft_execute(t_data *data, t_cmd *curr)
{
	t_builtin	*func;

	if (curr->nb_cmd < 6 && curr->nb_cmd >= 0)
	{
		func = create_array_function();
		(func)[curr->nb_cmd](data, curr);
		free(func);
	}
	// else
	// {
	// 	ft_exec_in_child(data, envp); // переписать
	// }
}

void	ft_execution_cycle(t_data *data)
{
	int		i;
	t_cmd	*command;
	int		status;

	ft_init_saved_fd(data);
	command = data->shell_cmd; // проверить есть ли команды
	i = 0;
	while (i < data->count) // while (command)
	{
		if (!ft_try_input(data, command) && !ft_try_output(data, command))
		{
			ft_check_pipe(data, command);
			ft_execute(data, command);
			ft_close_saved_fd(data);
			if (command->nb_cmd > 5)
				waitpid(-1, &status, 0);
			i++;
			command = command->next;
		}
	}
}
