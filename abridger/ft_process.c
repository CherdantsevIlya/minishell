/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:09:03 by abridger          #+#    #+#             */
/*   Updated: 2022/01/27 22:41:57 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_array_path(char **env_array)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (str == NULL && env_array[i] != NULL)
	{
		str = ft_strnstr(env_array[i], "PATH", 4);
		i++;
	}
	return (ft_split(str, ':'));
}

int	ft_run_execve(t_shell *data, t_info *curr, char **env_array)
{
	char	*str_path;
	int		i;
	char	*tmp;
	int		check;
	char	**array_path;

	i = 0;
	check = 0;
	tmp = NULL;
	str_path = NULL;
	array_path = create_array_path(env_array);
	while (array_path[i] != NULL && check != 1)
	{
		tmp = ft_strjoin(array_path[i], "/");
		str_path = ft_strjoin(tmp, curr->argv[0]);
		free(tmp);
		if (access(str_path, 0) == 0)
			check = 1;
		i++;
	}
	ft_array_clear(array_path);
	if (check == 0)
		return (ft_no_path(data, curr, env_array));
	return (ft_execve(data, curr, env_array, str_path));
}

int	ft_no_path(t_shell *data, t_info *curr, char **env_array)
{
	ft_array_clear(env_array);
	return (ft_error(data, ft_one_colon(curr->argv[0])));
}

int	ft_execve(t_shell *data, t_info *curr, char **env_array, char *str_path)
{
	if (execve(str_path, curr->argv, env_array) == -1)
	{
		ft_array_clear(env_array);
		return (ft_error(data, ft_one_colon(curr->argv[0])));
	}
	return (0);
}
