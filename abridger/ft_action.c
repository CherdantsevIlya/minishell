/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/01/24 19:13:39 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	action(t_shell *data, char **envp)
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

void	ft_execute(t_shell *data, t_info *curr)
{
	t_builtin	*func;

	if (curr->nb_cmd < 6 && curr->nb_cmd >= 0)
	{
		func = create_array_function(); // перенести в родительский
		(func)[curr->nb_cmd](data, curr);
		free(func);
	}
	// else
	// {
	// 	ft_exec_in_child(data, envp); // переписать
	// }
}

// void	ft_execution_cycle(t_shell *data)
// {
// 	int		i;
// 	t_info	*command;
// 	int		status;

// 	ft_init_saved_fd(data);
// 	command = data->info; // проверить есть ли команды
// 	i = 0;
// 	while (i < data->count) // while (command)
// 	{
// 		if (!ft_try_input(data, command) && !ft_try_output(data, command))
// 		{
// 			ft_check_pipe(data, command);
// 			ft_execute(data, command);
// 			ft_close_saved_fd(data);
// 			if (command->nb_cmd > 5)
// 				waitpid(-1, &status, 0);
// 			i++;
// 			command = command->next;
// 		}
// 	}
// }

int	ft_lstsize(t_info *lst)
{
	int	length;

	if (!lst)
		return (0);
	length = 1;
	while (lst->next)
	{
		length++;
		lst = lst->next;
	}
	lst = lst->head;
	return (length);
}

void	ft_execution_cycle(t_shell *data)
{
	t_info	*curr;

	curr = data->info;
	data->count = ft_lstsize(curr);
	while (curr)
	{
		ft_simple_exec(data);
		ft_redirect_dup(data);
		ft_pipe_init(data);
		if (curr->nb_cmd < 7 && curr->nb_cmd > 0 && !curr->is_pipe)
			ft_exec_builtin(data, curr);
		else
		{
			data->pid = fork(); // check -1
			if (data->pid == 0)
				ft_exec_in_child(data, curr);
		}
		curr = curr->next;
	}
}
