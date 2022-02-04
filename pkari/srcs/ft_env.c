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
	t_env *tmp;

	tmp = data->env;
	if (curr->nb_cmd == 6)
	{
		if (data->env != NULL && !ft_wrong_path(data) && curr->token != 1)
		{
			while (tmp)
			{
				if (tmp->sep)
				{
					write(1, tmp->key, ft_strlen(tmp->key));
					write(1, tmp->sep, ft_strlen(tmp->sep));
					write(1, tmp->value, ft_strlen(tmp->value));
					write(1, "\n", 1);
				}
				tmp = tmp->next;
			}
		}
	}
	return (0);
}
