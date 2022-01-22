/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:43:39 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 20:00:51 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*create_array_function(void)
{
	t_builtin	*array_func;

	array_func = NULL;
	array_func = (t_builtin *)malloc(sizeof(7));
	(array_func)[0] = &ft_exec_echo;
	(array_func)[1] = &ft_exec_cd;
	(array_func)[2] = &ft_exec_pwd;
	(array_func)[3] = &ft_exec_export;
	(array_func)[4] = &ft_exec_unset;
	(array_func)[5] = &ft_exec_exit;
	(array_func)[6] = &ft_exec_env;
	return (array_func);
}

int	ft_exec_echo(t_data *data, t_cmd *curr)
{
	(void) data;
	if (!ft_strcmp(curr->cmd_args[0], "echo"))
	{
		if (!ft_strcmp(curr->cmd_args[1], "-n"))
		{
			write(1, curr->cmd_args[2], ft_strlen(curr->cmd_args[2]));
			write(1, "\n", 1);
		}
		else
			write(1, curr->cmd_args[1], ft_strlen(curr->cmd_args[1]));
	}
	return (0);
}

int	ft_exec_cd(t_data *data, t_cmd *curr)
{
	t_env	*tmp;
	char	*buf;
	char	*str;

	tmp = data->envrmnt;
	buf = NULL;
	if (!ft_strcmp(curr->cmd_args[0], "cd"))
	{
		if (chdir(curr->cmd_args[1]) < 0)
			return (ft_error(1, data, "DIR error: "));
		str = getcwd(NULL, sizeof(buf));
		while (tmp)
		{
			if (0 == ft_strcmp(tmp->key, "PWD"))
			{
				free(tmp->value);
				tmp->value = ft_strdup(str);
				free(str);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	ft_exec_pwd(t_data *data, t_cmd *curr)
{
	char	*str;
	char	*buf;

	(void) data;
	buf = NULL;
	str = getcwd(NULL, sizeof(buf));
	if (!ft_strcmp(curr->cmd_args[0], "pwd"))
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		ft_str_clear(&str);
	}
	return (0);
}
