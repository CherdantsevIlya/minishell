/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:22:54 by abridger          #+#    #+#             */
/*   Updated: 2022/02/13 01:25:15 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_err_no_dir(t_shell *data, char *str)
{
	data->exit_status = 127;
	write(STDERR_FILENO, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
	return (1);
}
