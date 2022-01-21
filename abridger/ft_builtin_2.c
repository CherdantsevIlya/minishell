/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:23:47 by abridger          #+#    #+#             */
/*   Updated: 2022/01/21 20:48:33 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_export(t_data *data, t_cmd *curr)
{
	int		i;
	int		size;
	int		height;
	char	**array;

	i = 0;
	size = ft_lstsize_all(data);
	height = ft_height_array(curr->cmd_args);
	if (!ft_strcmp(curr->cmd_args[0], "export")) // or number
	{
		ft_add_variable(curr, data, height);
		if (data->envrmnt != NULL && height == 0)
		{
			array = create_array_all(data, NULL); // добавить сортировку
			while (i < size)
			{
				write(1, "declare -x ", ft_strlen("declare -x "));
				write(1, array[i], ft_strlen(array[i]));
				write(1, "\n", 1);
				i++;
			}
			ft_array_clear(array);
		}
	}
	return (0);
}

int	ft_exec_exit(t_data *data, t_cmd *curr)
{

}

int	ft_exec_env(t_data *data, t_cmd *curr)
{

}
