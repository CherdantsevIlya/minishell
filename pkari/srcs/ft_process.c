/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:09:03 by abridger          #+#    #+#             */
/*   Updated: 2022/01/28 20:29:52 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_array_path(t_shell *data)
{
	char	*str;
	int		i;
	char	**env_array;

	i = 0;
	str = NULL;
	env_array = data->array;
	while (str == NULL && env_array[i] != NULL)
	{
		str = ft_strnstr2(env_array[i], "PATH", 4);
		i++;
	}
	return (ft_split2(str, ':'));
}

//int	ft_run_execve(t_shell *data, t_info *curr)
//{
//	char	*str_path;
//	int		i;
//	char	*tmp;
//	int		check;
//	char	**array_path;
//
//	i = 0;
//	check = 0;
//	tmp = NULL;
//	str_path = NULL;
//	array_path = create_array_path(data);
//	while (array_path[i] != NULL && check != 1)
//	{
//		tmp = ft_strjoin2(array_path[i], "/");
//		str_path = ft_strjoin2(tmp, curr->argv[0]);
//		free(tmp);
//		if (access(str_path, 0) == 0)
//			check = 1;
//		i++;
//	}
//	ft_array_clear(array_path);
//	if (check == 0)
//		return (ft_no_path(data, curr));
//	return (ft_execve(data, curr, str_path));
//}

int	ft_no_path(t_shell *data, t_info *curr)
{
	ft_array_clear(data->array);
	return (ft_error(data, ft_one_colon(curr->argv[0])));
}

int	ft_execve(t_shell *data, t_info *curr, char *str_path)
{
	if (execve(str_path, curr->argv, data->array) == -1)
	{
		ft_array_clear(data->array);
		return (ft_error(data, ft_one_colon(curr->argv[0])));
	}
	return (0);
}
