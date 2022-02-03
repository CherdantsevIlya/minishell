/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:31:17 by abridger          #+#    #+#             */
/*   Updated: 2022/01/28 20:28:18 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wrong_path(t_shell *data)
{
	t_env	*curr;

	curr = data->env;
	while (curr)
	{
		if (!ft_strcmp2(curr->key, "PATH"))
			return (0);
		curr = curr->next;
	}
	return (ft_error(data, ft_one_colon("env")));
}

int	ft_exec_env(t_shell *data, t_info *curr)
{
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_env(data);
	if (curr->nb_cmd == 6)
	{
		if (data->env != NULL && !ft_wrong_path(data) && curr->is_pipe == 0)
		{
			create_array_env(&data);
			while (i < size)
			{
				write(1, data->array[i], ft_strlen(data->array[i]));
				write(1, "\n", 1);
				i++;
			}
			ft_array_clear(data->array);
		}
	}
	return (0);
}
