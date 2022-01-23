/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:23:47 by abridger          #+#    #+#             */
/*   Updated: 2022/01/23 19:51:35 by abridger         ###   ########.fr       */
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

int	ft_wrong_path(t_data *data, char *str, int errnum)
{
	t_env	*curr;

	curr = data->envrmnt;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PATH"))
			return (0);
		curr = curr->next;
	}
	return (ft_error(errnum, data, str));
}

int	ft_exec_env(t_data *data, t_cmd *curr)
{
	int		i;
	int		size;
	char	**array;

	i = 0;
	size = ft_lstsize_env(data);
	if (!ft_strcmp(curr->cmd_args[0], "env")) // or number
	{
		if (data->envrmnt != NULL && !ft_wrong_path(data, "env: ", 2)) // 2 - ENOENT- No such file or directory
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
