#include "../includes/minishell.h"

void free_all(t_shell *msh)
{
	t_info *tmp;
	int i;

	if (msh->env != NULL)
		msh->env = msh->env->first;
	while (msh->env)
	{
		ft_str_clear(&msh->env->key);
		ft_str_clear(&msh->env->sep);
		ft_str_clear(&msh->env->value);
		msh->env = msh->env->next;
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
}
