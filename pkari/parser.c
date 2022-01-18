#include "minishell.h"

static int is_token(t_shell *msh, int *i)
{
	if (msh->str[*i] == '|')
		return (gfhdf);
	else if (msh->str[*i] == '>')
	{
		if (msh->str[*i + 1] == '>')
			return(dfdhdfg);
		return (ddghdh);
	}
	else if (msh->str[*i] == '<')
	{
		if (msh->str[*i + 1] == '<')
			return(dfdhdfg);
		return (ddghdh);
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
		gfh;
	else if (is_token(msh, i))
		return (1);
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
//	add_list(); информация про токен и не только
	while (msh->str)
	{
		if (minishell_parser(msh, &i))
			return (0);
		i++;
	}
	return (1);
}
