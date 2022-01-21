#include "minishell.h"

void token_handler(t_shell *msh, int *i)
{
	char **tmp;
	int i;

	if (msh->info->token == TOKEN_REDIRECT_INPUT)
		redirect_input(msh, i);
	else if (msh->info->token == TOKEN_REDIRECT_OUTPUT1
		|| msh->info->token == TOKEN_REDIRECT_OUTPUT2)
		redirect_output(msh, i);
	else if (msh->info->token == TOKEN_HEREDOC)
		redirect_heredoc(msh, i);
	else
	{
		// записать аргументы строки в массив и передать его в структуру t_info
	}
}

int token_redirects(t_shell *msh, int *i, int token)
{
	char *tmp;

	if (*i != 0)
		token_handler(msh, i);
	tmp = NULL;
	msh->info->token = token;
	if (token == TOKEN_HEREDOC || token == TOKEN_REDIRECT_OUTPUT2)
		(*i)++;
	while (msh->str[*i] != 0 &&(msh->str[*i + 1] == ' '
		|| msh->str[*i + 1] == '\t'))
		(*i)++;
	if (msh->str[*i + 1] == 0 || msh->str[*i + 1] == '|'
		|| msh->str[*i + 1] == '<' || msh->str[*i + 1] == '>')
		return (ERROR());
	if (msh->str[*i] != 0 && msh->str[*i + 1] != 0)
		tmp = ft_strdup(msh->str + *i + 1);
	(*i) = -1;
	free(msh->str);
	msh->str = tmp;
	return (0);
}

int token_pipe(t_shell *msh, int *i)
{
	char *tmp;

	if (*i != 0)
		token_handler(msh, i);
	tmp = NULL;
	msh->info->token = TOKEN_PIPE;
	add_info(msh);
	while (msh->str[*i] != 0 &&(msh->str[*i + 1] == ' '
		|| msh->str[*i + 1] == '\t'))
		(*i)++;
	if (msh->str[*i + 1] == 0 || msh->str[*i + 1] == '|'
		|| msh->str[*i + 1] == '<' || msh->str[*i + 1] == '>')
		return (ERROR());
	if (msh->str[*i] != 0 && msh->str[*i + 1] != 0)
		tmp = ft_strdup(msh->str + *i + 1);
	(*i) = -1;
	free(msh->str);
	msh->str = tmp;
	msh->have_a_pipe = 1;
	return (0);
}

int token_space(t_shell *msh, int *i)
{
	char *tmp;

	token_handler(msh, i);
	tmp = NULL;
	while (msh->str[*i] != 0 &&(msh->str[*i + 1] == ' '
		|| msh->str[*i + 1] == '\t'))
		(*i)++;
	if (msh->str[*i] != 0 && msh->str[*i + 1] != 0)
		tmp = ft_strdup(msh->str + *i + 1);
	(*i) = -1;
	free(msh->str);
	msh->str = tmp;
	return (0);
}

