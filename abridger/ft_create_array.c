/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/01/27 20:26:35 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_shell *data)
{
	int		length;
	t_env	*lst;

	lst = data->env;
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

int	ft_lstsize_all(t_shell *data)
{
	int		length;
	t_env	*lst;

	lst = data->env;
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

int	ft_malloc_array_err(char ***array, t_shell *data, int check)
{
	int		length;

	if (check == 1)
		length = ft_lstsize_env(data);
	else
		length = ft_lstsize_all(data);
	*array = (char **)malloc(sizeof(char *) * length);
	if (!array)
		return (ft_error(data, ft_one_colon("malloc")));
	return (0);
}

char	**create_array_env(t_shell *data, char **array)
{
	char	*tmp;
	t_env	*lst;
	int		i;

	i = 0;
	lst = data->env;
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

char	**create_array_all(t_shell *data, char **array)
{
	char	*tmp;
	char	*str;
	t_env	*lst;
	int		i;

	i = 0;
	lst = data->env;
	if (ft_malloc_array_err(&array, data, 2) == 0)
	{
		while (i++ < ft_lstsize_all(data))
		{
			str = ft_add_quotes(lst->value);
			if (0 == ft_strcmp(lst->sep, "="))
				tmp = ft_strjoin(lst->key, "=");
			else
				tmp = ft_strdup(lst->key);
			if (lst->value)
				array[i] = ft_strjoin(tmp, str);
			else
				array[i] = ft_strdup(tmp);
			ft_twostr_clear(&tmp, &str);
			lst = lst->next;
		}
	}
	return (array);
}
