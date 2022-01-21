/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:46:58 by abridger          #+#    #+#             */
/*   Updated: 2022/01/21 22:38:34 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err_unset(t_data *data, char *str)
{
	int		i;
	char	*err;

	i = 0;
	err = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == 61)
		{
			err = ft_strjoin("unset: ", str);
			return (ft_error(1, data, err)); // bash: unset: `SHLVL=2': not a valid identifier
		}
		i++;
	}
	return (0);
}

void	ft_del_lst(char *str, t_data *data)// неверно, переделать на двусвязный список
{
	// t_env	*tmp;
	// t_env	*envrmnt;

	// tmp = NULL;
	// envrmnt = data->envrmnt;
	// while (envrmnt->next)
	// {
	// 	if (!ft_strcmp(envrmnt->next->key, str))
	// 	{
	// 		tmp = envrmnt->next;
	// 		ft_str_clear(envrmnt->key);
	// 		ft_str_clear(envrmnt->sep);
	// 		ft_str_clear(envrmnt->value);
	// 		free(envrmnt);
	// 		envrmnt = tmp;
	// 	}
	// }
}

int	ft_exec_unset(t_data *data, t_cmd *curr)
{
	int		i;
	int		height;

	i = 1;
	height = ft_height_array(curr->cmd_args);
	if (!ft_strcmp(curr->cmd_args[0], "unset") && height > 0)
	{
		while (curr->cmd_args[i])
		{
			if (!ft_err_unset(data, curr->cmd_args[i]))
				ft_del_lst(curr->cmd_args[i], data);
			i++;
		}
	}
	return (0);
}
