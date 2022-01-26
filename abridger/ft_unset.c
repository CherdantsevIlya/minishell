/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:46:58 by abridger          #+#    #+#             */
/*   Updated: 2022/01/26 23:27:58 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err_unset(t_shell *data, char *str)
{
	int		i;
	char	*part_str;
	char	*err;

	i = 0;
	part_str = NULL;
	err = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == 61)
		{
			data->exit_status = 127;
			part_str = ft_strjoin("unset: `", str);
			err = ft_strjoin(part_str, "': not a valid identifier");
			ft_str_clear(&part_str);
			write(STDERR_FILENO, err, ft_strlen(err));
			write(STDERR_FILENO, "\n", 1);
			ft_str_clear(&err);
			return (1); // bash: unset: `SHLVL=2': not a valid identifier
		}
		i++;
	}
	return (0);
}

void	ft_del_lst(char *str, t_shell *data)
{
	t_env	*tmp;
	t_env	*envrmnt;
	t_env	*previous;

	tmp = NULL;
	previous = NULL;
	envrmnt = data->env;
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
			envrmnt->prev = previous;
		}
	}
}

int	ft_exec_unset(t_shell *data, t_info *curr)
{
	int		i;
	int		height;

	i = 1;
	height = ft_height_array(curr->argv);
	if (curr->nb_cmd == 4 && height > 0)
	{
		while (curr->argv[i])
		{
			if (!ft_err_unset(data, curr->argv[i]))
				ft_del_lst(curr->argv[i], data);
			i++;
		}
	}
	return (0);
}
