#include "../includes/minishell.h"

void free_all(t_shell *msh)
{
	t_info *tmp;
	int i;

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
		// мб тут что-то будет
		tmp = msh->info;
		msh->info = msh->info->next;
		free(tmp);
	}
	if (msh->str)
		free(msh->str);
	msh->have_a_pipe = 0;
}
