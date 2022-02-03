/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/01/29 23:45:27 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (0 == ft_strcmp2(lst->sep, "="))
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
		if (0 == ft_strcmp2(lst->sep, "="))
		{
			tmp = ft_strjoin2(lst->key, "=");
			if (lst->value)
				(*data)->array[line] = ft_strjoin2(tmp, lst->value);
			else
				(*data)->array[line] = ft_strdup(tmp);
			free(tmp);
			line++;
		}
		lst = lst->next;
	}
}

void	ft_array_clear(char **array)
{
	int		i;

	i = 0;
//	while (array && array[i])
//		free(array[i++]);
	if (!array)
		return ;
	while (array)
	{
		if (array[i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
}
