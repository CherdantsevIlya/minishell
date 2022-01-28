/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/01/28 20:37:42 by abridger         ###   ########.fr       */
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

void	ft_init_array(t_shell **data, int check)
{
	int		length;

	if (check == 1)
		length = ft_lstsize_env(*data);
	else
		length = ft_lstsize_all(*data);
	(*data)->array = (char **)malloc(sizeof(char *) * length);
	(*data)->array[length] = NULL;
	if (!(*data)->array)
		exit(EXIT_FAILURE);
}

void	create_array_env(t_shell **data)
{
	char	*tmp;
	t_env	*lst;
	int		line;

	line = 0; // если 1, то запишет все строки кроме первой, она будет null
	lst = (*data)->env;
	ft_init_array(data, 1);
	while (lst) // (*data)->array[0] - null
	{
		if (0 == ft_strcmp(lst->sep, "="))
		{
			tmp = ft_strjoin(lst->key, "=");
			if (lst->value)
				(*data)->array[line] = ft_strjoin(tmp, lst->value);
			else
				(*data)->array[line] = ft_strdup(tmp);
			free(tmp);
			line++;
		}
		lst = lst->next;
	}
}

void	create_array_all(t_shell **data)
{
	char	*tmp;
	char	*str;
	t_env	*lst;
	int		line;

	line = 0;
	lst = (*data)->env;
	ft_init_array(data, 2);
	while (lst)
	{
		str = ft_add_quotes(lst->value);
		if (0 == ft_strcmp(lst->sep, "="))
			tmp = ft_strjoin(lst->key, "=");
		else
			tmp = ft_strdup(lst->key);
		if (lst->value)
			(*data)->array[line] = ft_strjoin(tmp, str);
		else
			(*data)->array[line] = ft_strdup(tmp);
		ft_twostr_clear(&tmp, &str);
		lst = lst->next;
		line++;
	}
}
