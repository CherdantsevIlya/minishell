/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:32:20 by abridger          #+#    #+#             */
/*   Updated: 2022/01/26 17:52:57 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_err_message(char *str)
{
	// write(STDERR_FILENO, "Error: ", 7); // не подходит для одной функции
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_error(int errnum, t_shell *data, char *str) // errnum пока неверные в функциях
{
	char	*str_err;

	data->exit_status = errnum;
	str_err = strerror(errnum);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	write(STDERR_FILENO, "\n", 1);
	ft_str_clear(&str);
	ft_str_clear(&str_err);
	ft_data_clear(data);
	return (1);
}

char	*ft_two_colon(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = NULL;
	str2 = NULL;
	str3 = NULL;
	if (s1)
		str1 = ft_strjoin(s1, ": ");
	if (s2)
		str2 = ft_strjoin(s2, ": ");
	else
		return (str1);
	if (s1 && s2)
	{
		str3 = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
	}
	return (str3);
}

char	*ft_one_colon(char *s1)
{
	char	*str1;

	str1 = NULL;
	if (s1)
		str1 = ft_strjoin(s1, ": ");
	return (str1);
}
