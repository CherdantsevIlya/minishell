/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:46:58 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 22:50:55 by abridger         ###   ########.fr       */
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

void	ft_del_lst(char *str, t_data *data)
{
	t_env	*tmp;
	t_env	*envrmnt;
	t_env	*previous;

	tmp = NULL;
	previous = NULL;
	envrmnt = data->envrmnt;
	while (envrmnt)
	{
		if (!ft_strcmp(envrmnt->next->key, str))
		{
			tmp = envrmnt;
			previous = envrmnt->prev;
			ft_str_clear(&envrmnt->key);
			ft_str_clear(&envrmnt->sep);
			ft_str_clear(&envrmnt->value);
			envrmnt = envrmnt->next;
			free(tmp);
			if (envrmnt->prev)
				envrmnt->prev = previous;
		}
	}
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
