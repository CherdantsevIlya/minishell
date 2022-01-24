/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:45:11 by abridger          #+#    #+#             */
/*   Updated: 2022/01/24 18:04:09 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_strs_free(t_env *lst)
// {
// 	if (lst)
// 	{
// 		if (lst->line)
// 			free(lst->line);
// 		lst->line = NULL;
// 		if (lst->key)
// 			free(lst->key);
// 		lst->key = NULL;
// 		if (lst->value)
// 			free(lst->value);
// 		lst->value = NULL;
// 	}
// }

// void	ft_lst_clear(t_env *lst)
// {
// 	t_env	*tmp;
// 	t_env	*curr;

// 	tmp = NULL;
// 	curr = NULL;
// 	if (lst)
// 		curr = lst;
// 	while (curr)
// 	{
// 		tmp = curr;
// 		ft_strs_free(tmp);
// 		curr = curr->next;
// 		free(tmp);
// 	}
// 	lst = NULL;
// }

//
// void	ft_lst_clear(t_env *lst)
// {
// 	t_env	*tmp;
// 	// t_env	*curr;

// 	tmp = NULL;
// 	// curr = NULL;
// 	// if (lst)
// 	// 	curr = lst;
// 	while (lst)
// 	{
// 		tmp = lst;
// 		if (tmp->line)
// 		{
// 			printf("free(tmp->line)"); // delete
// 			free(tmp->line);
// 		}
// 		tmp->line = NULL;
// 		if (tmp->key)
// 		{
// 			printf("free(tmp->key)"); // delete
// 			free(tmp->key);
// 		}
// 		tmp->key = NULL;
// 		if (tmp->value)
// 		{
// 			printf("free(tmp->value)"); // delete
// 			free(tmp->value);
// 		}
// 		tmp->value = NULL;
// 		// ft_strs_free(tmp);
// 		lst = lst->next;
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	lst = NULL;
// }

void	ft_lst_clear(t_env **lst)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = NULL;
	curr = NULL;
	if (*lst)
	{
		curr = *lst;
		printf("curr = *lst\n"); // delete
	}
	while (curr)
	{
		printf("data->envrmnt\n"); // delete
		tmp = curr;
		if (tmp)
			printf("tmp\n"); // delete
		if (tmp->sep)
		{
			printf("free(tmp->sep)\n"); // delete
			free(tmp->sep);
		}
		tmp->sep = NULL;
		if (tmp->key)
		{
			printf("free(tmp->key)\n"); // delete
			free(tmp->key);
		}
		tmp->key = NULL;
		if (tmp->value)
		{
			printf("free(tmp->value)\n"); // delete
			free(tmp->value);
		}
		tmp->value = NULL;
		curr = curr->next;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}

void	ft_array_clear(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

void	ft_data_clear(t_shell *data)
{
	t_env	*tmp;

	tmp = NULL;
	if (data)
	{
		printf("data\n"); // delete
		if (data->env != NULL)
		{
			tmp = data->env;
			ft_lst_clear(&tmp);
			// while (data->envrmnt)
			// {
				// printf("data->envrmnt\n");
				// free(data->envrmnt->line);
				// free(data->envrmnt->key);
				// free(data->envrmnt->value);
				// data->envrmnt = data->envrmnt->next;
			// }
		}
		else
			printf("no data->envrmnt\n"); // delete
		if (data->array_path != NULL)
			ft_array_clear(data->array_path);
		// free(data);
	}
	else
		printf("no data\n"); // delete
	data = NULL;
}

void	ft_str_clear(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	ft_twostr_clear(char **str1, char **str2)
{
	if (*str1)
		free(*str1);
	*str1 = NULL;
	if (*str2)
		free(*str2);
	*str2 = NULL;
}
