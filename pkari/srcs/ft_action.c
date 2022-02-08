/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:29:06 by abridger          #+#    #+#             */
/*   Updated: 2022/02/08 02:28:43 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 int	action(t_shell *data)
 {
	 ft_define_cmd(data);
	 ft_execution_cycle(data);
	 signal(SIGINT, ctrl_c);
	 return (0);
 }

void	ft_define_cmd(t_shell *data)
{
	t_info	*curr;

	curr = NULL;
	if (data->info)
		curr = data->info->head;
	while (curr)
	{
		if (curr->argv && !ft_strcmp2(curr->argv[0], "echo"))
			curr->nb_cmd = 0;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "cd"))
			curr->nb_cmd = 1;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "pwd"))
			curr->nb_cmd = 2;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "export"))
			curr->nb_cmd = 3;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "unset"))
			curr->nb_cmd = 4;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "exit"))
			curr->nb_cmd = 5;
		else if (curr->argv && !ft_strcmp2(curr->argv[0], "env"))
			curr->nb_cmd = 6;
		else if (curr->argv)
			curr->nb_cmd = 7;
		curr = curr->next;
	}
}

//**start new functions**//

static char *ft_get_path(t_env *env, char *key)
{
	 t_env *tmp;

	 tmp = env;
	 while (tmp)
	 {
		 if (!strcmp(key, tmp->key))
			 return (tmp->value);
		 tmp = tmp->next;
	 }
	return ("");
}

static char *get_prog_name(t_shell *data)
{
	 int i;
	 char **path;
	 char *tmp;
	 char *str;

	 i = 0;
	 str = data->info->argv[0];
	 path = ft_split(ft_get_path(data->env, "PATH"), ':');
	 while (path[i])
	 {
		 tmp = ft_strjoin2("/", data->info->argv[0]);
		 tmp = ft_strjoin(path[i], tmp);
		 if (access(tmp, 0) == 0)
			 str = tmp;
		 else
			 free(tmp);
		 i++;
	 }
	 free(path);
	 return (str);
}

static int ft_lstsize2(t_env *env)
{
	 int i;

	 i = 1;
	 while (env->next)
	 {
		 i++;
		 env = env->next;
	 }
	 return (i);
}

static char **get_arr_from_lst(t_shell *data)
{
	 t_env *tmp;
	 int i;
	 char *str;

	 tmp = data->env;
	 i = ft_lstsize2(tmp);
	 data->array = (char **)malloc(sizeof(char *) * (i + 1));
	 i = 0;
	 while (tmp)
	 {
		 str = ft_strjoin2(tmp->key, "=");
		 data->array[i] = ft_strjoin2(str, tmp->value);
		 free(str);
		 i++;
		 tmp = tmp->next;
	 }
	 data->array[i] = NULL;
	 return (data->array);
}

static void exit_status_handler(t_shell *data)
{
	int status;
	
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
	else
		data->exit_status = WEXITSTATUS(status);
}

//**end new functions**//

//int	ft_simple_execute(t_shell *data, t_info *curr, t_builtin *func)
//{
//	if (data->count == 1)
//	{
//		ft_redirect_dup(curr);
//		if (curr->nb_cmd >= 0 && curr->nb_cmd < 7)
//			return ((func)[curr->nb_cmd](data, curr)); // close files?
//		else
//		{
//			curr->pid = fork();
//			if (curr->pid == -1)
//				return (ft_error(data, ft_one_colon("fork")));
//			else if (curr->pid == 0)
//			{
//				if (execve(get_prog_name(data), data->info->argv,
//						   get_arr_from_lst(data)) == -1)
//					execve_error(data);
//				exit(data->exit_status);
//			}
//			//ft_close_files(curr);
//			//exit_status_handler(data);
//		}
//	}
//	return (0);
//}

int	ft_execute(t_shell *data, t_info *curr, t_builtin *func)
{
	if (data->count >= 1)
	{
		curr->pid = fork();
		if (curr->pid == -1)
			return (ft_error(data, ft_one_colon("fork")));
		else if (curr->pid == 0)
		{
			ft_pipe_dup(data, curr);
			ft_redirect_dup(curr);
			if (curr->nb_cmd < 7 && curr->nb_cmd >= 0)
				(func)[curr->nb_cmd](data, curr);
			else
			{
				if (execve(get_prog_name(data), data->info->argv,
						   get_arr_from_lst(data)) == -1)
					execve_error(data);
			}
			exit(data->exit_status);
		}
		//ft_pipe_close(data, curr);
		//ft_close_files(curr);
		exit_status_handler(data);
	}
	return (0);
}

void	ft_execution_cycle(t_shell *data)
{
	t_info		*curr;
	t_builtin	*func;
	
	curr = data->info->head;
	data->count = msh_lstsize(curr);
	func = create_array_function();
	ft_init_saved_fd(data);
	while (curr)
	{
		signal(SIGINT, ctrl_c2);
		ft_pipe_init(data, curr);
		//ft_simple_execute(data, curr, func);
		ft_execute(data, curr, func);
		curr = curr->next;
	}
	ft_close_saved_fd(data);
	free(func);
}
