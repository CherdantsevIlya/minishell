/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:01:41 by abridger          #+#    #+#             */
/*   Updated: 2022/01/24 17:37:07 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_data(t_shell *data, char **envp)
{
	t_env	*lst;

	lst = NULL;
	if (data)
	{
		data->env = parse_envrmnt(lst, envp);
		data->info = NULL;
		return (0);
	}
	return (0);
}

int	ft_len_key(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != 61)
	{
		i++;
		len++;
	}
	return (len);
}

int	ft_len_value(char *str)
{
	int	len;
	int	len_key;
	int	i;

	len = ft_strlen(str);
	len_key = ft_len_key(str);
	i = 1 + len_key;
	if (len > len_key)
	{
		while (str[i] != '\0' && i < len)
		{
			i++;
		}
		return (i - 1 - len_key);
	}
	else
		return (0);
}
