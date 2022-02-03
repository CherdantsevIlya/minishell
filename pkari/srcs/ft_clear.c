/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:45:11 by abridger          #+#    #+#             */
/*   Updated: 2022/01/29 23:45:39 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_info_clear(t_info **lst)
{
	t_info	*tmp;
	t_info	*curr;

	tmp = NULL;
	curr = NULL;
	if (*lst)
		curr = *lst;
	while (curr)
	{
		tmp = curr;
		ft_str_clear(&tmp->output_file);
		ft_str_clear(&tmp->input_file);
		ft_str_clear(&tmp->heredoc);
		ft_array_clear(tmp->argv);
		curr = curr->next;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}

void	ft_env_clear(t_env **lst)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = NULL;
	curr = NULL;
	if (*lst)
		curr = *lst;
	while (curr)
	{
		tmp = curr;
		ft_str_clear(&tmp->key);
		ft_str_clear(&tmp->sep);
		ft_str_clear(&tmp->value);
		curr = curr->next;
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}

void	ft_data_clear(t_shell *data)
{
	if (data)
	{
		if (data->env != NULL)
			ft_env_clear(&data->env);
		if (data->info != NULL)
			ft_info_clear(&data->info);
		ft_str_clear(&data->str);
		if (data->array)
			ft_array_clear(data->array);
		free(data);
	}
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
