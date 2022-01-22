/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:32:20 by abridger          #+#    #+#             */
/*   Updated: 2022/01/22 19:48:29 by abridger         ###   ########.fr       */
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

int	ft_error(int errnum, t_data *data, char *str) // errnum пока неверные в функциях
{
	char	*str_err;

	(void) data;
	str_err = strerror(errnum);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	write(STDERR_FILENO, "\n", 1);
	// ft_data_clear(data);
	ft_str_clear(&str); // иногда строка может быть замалочена
	ft_str_clear(&str_err);
	return (1);
}
