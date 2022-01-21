#include "minishell.h"

t_info *add_new_info(void)
{
	t_info *tmp;

	tmp = (t_info *)malloc(sizeof(t_info));
	if (!tmp)
		return (NULL);
	tmp->token = 0;
	tmp->argc = 0;
	tmp->argv = NULL;
	tmp->output_file = NULL;
	tmp->fd_output_file = 0;
	tmp->input_file = NULL;
	tmp->fd_input_file = 0;
	tmp->error = 0;
	tmp->prev = tmp;
	tmp->next = NULL;
	return (tmp);
}

void add_info(t_shell *msh)
{
	t_info *new;
	t_info *last;

	if (msh->info == NULL)
		msh->info = add_new_info();
	else
	{
		prev = msh->info->prev;
		new = add_new_info();
		msh->info->next = new;
		msh->info = msh->info->next;
		msh->info->prev = prev;
	}
}

static int minishell_parser(t_shell *msh, int *i)
{
	if (msh->str[*i] == '\'')
		return (single_quotes(msh, i));
	else if (msh->str[*i] == '\"')
		return (double_quotes(msh, i));
	else if (msh->str[*i] == '$')
		return (dollar(msh, i));
	else if (msh->str[*i] == ' ' || msh->str[*i] == '\t' || msh->str[*i] == 0)
		return (token_space(msh, i));
	else if (msh->str[*i] == '|')
		return (token_pipe(msh, i));
	else if (msh->str[*i] == '>')
	{
		if (msh->str[*i + 1] == '>')
			return(token_redirects(msh, i, TOKEN_REDIRECT_OUTPUT2));
		return (token_redirects(msh, i, TOKEN_REDIRECT_OUTPUT1));
	}
	else if (msh->str[*i] == '<')
	{
		if (msh->str[*i + 1] == '<')
			return(token_redirects(msh, i, TOKEN_HEREDOC));
		return (token_redirects(msh, i, TOKEN_REDIRECT_INPUT));
	}
	return (0);
}

static int minishell_pre_parser(t_shell *msh)
{
	int i;
	char *new;

	i = 0;
	new = NULL;
	while (msh->str[i] == ' ' || msh->str[i] == '\t')
		i++;
	if (msh->str[i] == '|')
	{
		if (msh->str[i] == msh->str[i + 1])
			return (ERROR());
		return (ERROR());
	}
	if (msh->str)
		new = ft_strdup(msh->str + i);
	free(msh->str);
	msh->str = new;
	return (0);
}

int parser(t_shell *msh)
{
	int i;

	i = 0;
	if (minishell_pre_parser(msh))
		return (0);
	add_info(msh);
	while (msh->str)
	{
		if (minishell_parser(msh, &i))
			return (0);
		i++;
	}
	return (1);
}
