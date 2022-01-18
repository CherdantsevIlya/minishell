/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/01/18 23:20:01 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_data *data)
{
	int		length;
	t_env	*lst;

	lst = data->envrmnt;
	if (!lst)
		return (0);
	length = 1;
	while (lst->next)
	{
		if (0 == ft_strcmp(lst->sep, "="))
			length++;
		lst = lst->next;
	}
	return (length);
}

int	ft_lstsize_all(t_data *data)
{
	int		length;
	t_env	*lst;

	lst = data->envrmnt;
	if (!lst)
		return (0);
	length = 1;
	while (lst->next)
	{
		length++;
		lst = lst->next;
	}
	return (length);
}

int	ft_malloc_array_err(char ***array, t_data *data, int check)
{
	int		length;

	if (check == 1)
		length = ft_lstsize_env(data);
	else
		length = ft_lstsize_all(data);
	*array = (char **)malloc(sizeof(char *) * length);
	if (!array)
		return (ft_error(1, data, "Malloc: "));
	return (0);
}

char	**create_array_env(t_data *data, char **array)
{
	char	*tmp;
	t_env	*lst;
	int		i;

	i = 0;
	lst = data->envrmnt;
	if (ft_malloc_array_err(&array, data, 1) == 0)
	{
		while (i < ft_lstsize_env(data))
		{
			if (0 == ft_strcmp(lst->sep, "="))
			{
				tmp = ft_strjoin(lst->key, "=");
				if (lst->value)
					array[i] = ft_strjoin(tmp, lst->value);
				else
					array[i] = ft_strdup(tmp);
				free(tmp);
			}
			lst = lst->next;
			i++;
		}
	}
	return (array);
}

char	**create_array_all(t_data *data, char **array)
{
	char	*tmp;
	t_env	*lst;
	int		i;

	i = 0;
	lst = data->envrmnt;
	if (ft_malloc_array_err(&array, data, 2) == 0)
	{
		while (i < ft_lstsize_all(data))
		{
			if (0 == ft_strcmp(lst->sep, "="))
				tmp = ft_strjoin(lst->key, "=");
			else
				tmp = ft_strdup(lst->key);
			if (lst->value)
				array[i] = ft_strjoin(tmp, lst->value);
			else
				array[i] = ft_strdup(tmp);
			free(tmp);
			lst = lst->next;
			i++;
		}
	}
	return (array);
}
