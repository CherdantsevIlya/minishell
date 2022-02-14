/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:53:41 by pkari             #+#    #+#             */
/*   Updated: 2022/02/14 17:53:43 by pkari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_env2(t_shell *msh, char *tmp)
{
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		tmp = NULL;
	}
	free(msh->str);
	msh->str = tmp;
}

void	free_all(t_shell *msh)
{
	t_info	*tmp;
	t_env	*tmp2;
	int		i;

	tmp2 = msh->env;
	while (tmp2)
	{
		tmp2->is_sorted = 0;
		tmp2->next_sorted = NULL;
		tmp2->first = NULL;
		tmp2 = tmp2->next;
	}
	if (msh->info != NULL)
		msh->info = msh->info->head;
	while (msh->info)
	{
		i = 0;
		while (msh->info->argv && msh->info->argv[i])
			free(msh->info->argv[i++]);
		free(msh->info->argv);
		if (msh->info->output_file)
			free(msh->info->output_file);
		if (msh->info->input_file)
			free(msh->info->input_file);
		if (msh->info->heredoc)
			free(msh->info->heredoc);
		tmp = msh->info;
		msh->info = msh->info->next;
		free(tmp);
	}
	while (msh->array && msh->array[i])
		free(msh->array[i++]);
	if (msh->str)
		free(msh->str);
	msh->have_a_pipe = 0;
	msh->check = 0;
}
