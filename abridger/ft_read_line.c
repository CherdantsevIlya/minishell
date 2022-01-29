/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:03:08 by abridger          #+#    #+#             */
/*   Updated: 2022/01/29 23:48:37 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_data(t_shell *data, char **envp)
{
	t_env	*lst;

	lst = NULL;
	if (data)
	{
		data->env = parse_envrmnt(lst, envp); // использовать только эту функцию для записи envp в листы
		data->info = NULL;
		data->str = NULL;
		data->array = NULL;
		data->check = 0;
		return (0);
	}
	return (0);
}

int	action(t_shell *data, char **envp) // for testing
{
	data = (t_shell *)malloc(sizeof(t_shell));
	if (!data)
		return (ft_error(NULL, "Malloc: "));
	else
	{
		ft_init_data(data, envp);
		// ft_define_cmd(data); // after parser
		// ft_execution_cycle(data);
		// ft_print_array(data); // test
		ft_print_lsts(data); // test
		ft_data_clear(data);
	}
	return (0);
}

void	ft_test_readline(void) // test
{
	char	*input;
	int		size;
	int		i;
	char	*buf;

	buf = NULL;
	i = 0;
	while (i < 5)
	{
		input = readline("Minishell$ : ");
		size = ft_strlen(input);
		if (!strcmp(input, "pwd"))
			printf("%s", getcwd(NULL, sizeof(buf)));
		else
		{
			add_history(input);
			printf("%s", input);
			printf("\n");
			printf("%d", size);
		}
		printf("\n");
		++i;
		if (input)
			free(input);
	}
}

void	ft_print_lsts(t_shell *data) //test
{
	t_env	*tmp;

	tmp = ft_sort_env(data);
	if (tmp != NULL)
	{
		printf("\nPRINT LISTS\n");
		while (tmp)
		{
			printf("%s", tmp->key);
			if (tmp->sep)
				printf("%s", tmp->sep);
			if (tmp->value)
				printf("%s\n", tmp->value);
			tmp = tmp->next_sorted;
		}
	}
	else
		printf("test");
}

void	ft_print_array(t_shell *data) //test
{
	int		size;
	int		i;

	size = ft_lstsize_env(data);
	i = 0;
	create_array_env(&data);
	printf("\n\n\nPRINT ARRAY\n");
	printf("SIZE lst in print array %d\n", size);
	printf("HEIGHT array in print array %d\n", ft_height_array(data->array));
	if (data->env != NULL)
	{
		while (i < size)
		{
			printf("Array[%d] %s\n", i, data->array[i]);
			i++;
		}
	}
	ft_array_clear(data->array);
}
