/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:01:41 by abridger          #+#    #+#             */
/*   Updated: 2022/01/13 21:37:41 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_data(t_data *data, char **envp)
{
	t_env	*lst;

	lst = NULL;
	if (data)
	{
		data->envrmnt = parse_envrmnt(lst, envp);
		data->shell_cmd = NULL;
		return (0);
	}
	return (0);
}
