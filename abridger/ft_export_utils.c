/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:23:30 by abridger          #+#    #+#             */
/*   Updated: 2022/01/27 01:14:37 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_char(int c)
{
	if (c <= 38 && c >= 33)
		return (1);
	else if ((c <= 47 && c >= 42) || c == 58)
		return (1);
	else if (c == 63 || c == 64 || c == 123 || c == 124)
		return (1);
	else if (c == 91 || c == 93 || c == 94 || c == 126)
		return (1);
	else
		return (0);
}

int	ft_check_key(char *str)
{
	int	i;
	int	len_key;
	int	check;

	i = 0;
	check = 0;
	if (str)
	{
		len_key = ft_len_key(str);
		while (i <= len_key)
		{
			check = ft_check_char(str[i]);
			if (check == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_err_export(t_shell *data, char *str)
{
	char	*part_str;
	char	*err;

	part_str = NULL;
	err = NULL;
	data->exit_status = 1;
	part_str = ft_strjoin("export: `", str);
	err = ft_strjoin(part_str, "': not a valid identifier");
	ft_str_clear(&part_str);
	write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, "\n", 1);
	ft_str_clear(&err);
	return (1);
}

char	*ft_quotes(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = 34;
	str[1] = '\0';
	return (str);
}

char	*ft_add_quotes(char *str)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = NULL;
	str2 = NULL;
	str3 = ft_quotes();
	if (str)
	{
		str1 = ft_strjoin(str3, str);
		str2 = ft_strjoin(str1, str3);
		free(str1);
		free(str3);
	}
	return (str2);
}
