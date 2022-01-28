/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:04:25 by abridger          #+#    #+#             */
/*   Updated: 2022/01/28 22:40:50 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_find_first(t_shell *data)
{
	t_env	*tmp_min;
	t_env	*tmp_next;
	t_env	*env;
	int		diff;
	int		check;

	env = data->env;
	tmp_min = env;
	tmp_next = env->next;
	check = 0;
	while (env)
	{
		diff = ft_strcmp(tmp_min->key, tmp_next->key);
		if (diff > 0)
			tmp_min = tmp_next;
		if (check == 0)
			env = env->next->next;
		check = 1;
		if (check == 1)
			env = env->next;
		tmp_next = env;
	}
	return (tmp_min);
}

t_env	*ft_sort_env(t_shell *data)
{
	t_env	*min;
	t_env	*next_min;
	t_env	*curr;
	int		count;

	min = ft_find_first(data);
	min->first = min;
	min->is_sorted = 1;
	count = 1;
	curr = min;
	next_min = NULL;
	while (count == ft_lstsize_all(data)) // можно написать функцию, которая будет проверять, все ли листы отсортированы
	{
		next_min = ft_find_next(data); // написать
		curr->next_sorted = next_min;
		curr = next_min;
		count++;
	}
	return (min);
}

// переписать печать export из отсортированных листов
