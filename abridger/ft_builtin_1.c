/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:43:39 by abridger          #+#    #+#             */
/*   Updated: 2022/01/20 23:15:38 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*create_array_function(void)
{
	t_builtin	*array_func;

	array_func = NULL;
	array_func = (t_builtin *)malloc(sizeof(7));
	(array_func)[echo] = &ft_exec_echo;
	(array_func)[cd] = &ft_exec_cd;
	(array_func)[pwd] = &ft_exec_pwd;
	(array_func)[export] = &ft_exec_export;
	(array_func)[unset] = &ft_exec_unset;
	(array_func)[exit] = &ft_exec_exit;
	(array_func)[env] = &ft_exec_env;
	return (array_func);
}

int	ft_exec_echo(t_data *data, t_cmd *curr)
{

}

int	ft_exec_cd(t_data *data, t_cmd *curr)
{
	t_env	*tmp;
	// char	*str1;
	// char	*str2;
	char	*buf;
	char	*str;

	tmp = data->shell_cmd;
	buf = NULL;
	str = getcwd(NULL, sizeof(buf));
	if (!ft_strcmp(curr->cmd_args[0], "cd"))
	{
		while (tmp)
		{
			if (chdir(curr->cmd_args[1]) < 0)
				return (ft_error(1, data, "DIR error: "));
			str = getcwd(NULL, sizeof(buf));
			if (0 == ft_strcmp(tmp->key, "PWD")) // если нет PWD, надо ли создать?
			{
				// if (0 == ft_strncmp(curr->cmd_args[1], "../", 3)) // путь относительный
				// 	str1 = ft_substr(curr->cmd_args[1], 2, ft_strlen(curr->cmd_args[1]) - 2);
				// else if (0 == ft_strncmp(curr->cmd_args[1], "./", 2))// путь относительный
				// 	str1 = ft_substr(curr->cmd_args[1], 1, ft_strlen(curr->cmd_args[1]) - 1);
				// else
				// 	str1 = ft_strjoin("/", curr->cmd_args[1]);// путь относительный, добавить для абсолютного пути
				// str2 = ft_strjoin(tmp->value, str1);
				free(tmp->value);
				// free(str1);
				// tmp->value = ft_strdup(str2);
				// free(str2);
				tmp->value = ft_strdup(str); // если получать из функции getcwd
				free(str);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	ft_exec_pwd(t_data *data, t_cmd *curr)
{
	t_env	*tmp;

	tmp = data->shell_cmd;
	if (!ft_strcmp(curr->cmd_args[0], "pwd"))
	{
		while (tmp)
		{
			if (0 == ft_strcmp(tmp->key, "PWD")) // если нет PWD, надо ли печатать ошибку?
			{
				write(STDIN_FILENO, tmp->value, ft_strlen(tmp->value));
				write(STDIN_FILENO, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

// int	ft_exec_pwd(t_data *data, t_cmd *curr)
// {
// 	char	*str;
// 	char	*buf;

// 	(void) data;
// 	buf = NULL;
// 	str = getcwd(NULL, sizeof(buf));
// 	if (!ft_strcmp(curr->cmd_args[0], "pwd"))
// 	{
// 		write(STDIN_FILENO, str, ft_strlen(str));
// 		write(STDIN_FILENO, "\n", 1);
// 		free(str);
// 	}
// retutn (0);
// }

int	ft_exec_export(t_data *data, t_cmd *curr)
{
	int		size;
	int		i;
	char	**array;

	size = ft_lstsize_all(data);
	i = 0;
	array = create_array_all(data, NULL); // добавить сортировку
	if (data->envrmnt != NULL && !ft_strcmp(curr->cmd_args[0], "export"))
	{
		while (i < size)
		{
			write(STDIN_FILENO, "declare -x ", ft_strlen("declare -x "));
			write(STDIN_FILENO, array[i], ft_strlen(array[i]));
			write(STDIN_FILENO, "\n", 1);
			i++;
		}
	}
	ft_array_clear(array);
	return (0);
}
