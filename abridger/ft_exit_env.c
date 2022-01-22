/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:23:47 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 23:14:49 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_exit(t_data *data, t_cmd *curr)
{
	(void) data;
	if (!ft_strcmp(curr->cmd_args[0], "exit"))
	{
		write(1, curr->cmd_args[0], ft_strlen(curr->cmd_args[0]));
		exit(0); //?
	}
	return (0);
}

int	ft_exec_env(t_data *data, t_cmd *curr)
{
	int		i;
	int		size;
	char	**array;

	i = 0;
	size = ft_lstsize_env(data);
	if (!ft_strcmp(curr->cmd_args[0], "envp")) // or number
	{
		if (data->envrmnt != NULL)
		{
			array = create_array_env(data, NULL);
			while (i < size)
			{
				write(1, array[i], ft_strlen(array[i]));
				write(1, "\n", 1);
				i++;
			}
			ft_array_clear(array);
		}
	}
	return (0);
}
