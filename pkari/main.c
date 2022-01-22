#include "minishell.h"

void shlvl(t_shell *msh)
{
	t_env *tmp;
	int shlvl;

	tmp = msh->env;
	while (1)
	{
		if (!tmp)
		{
			msh_lstadd_back(&tmp, msh_lstnew(ft_strdup("SHLVL"),ft_strdup
			("1")));
			break ;
		}
		else if (!(ft_strcmp("SHLVL", tmp->key)))
		{
			shlvl = ft_atoi(tmp->val);
			if (tmp->val != NULL)
				free(tmp->val);
			if (shlvl < 0)
				tmp->val = ft_strdup("1");
			else
				tmp->val = ft_itoa(shlvl + 1);
			break ;
		}
		tmp = tmp->next;
	}
}

char *get_dollar_env(t_env *env, char *str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (tmp->val);
		tmp = tmp->next;
	}
	return ("");
}

void create_env(t_shell *msh, char **env)
{
	char **tmp;
	int i;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		msh_lstadd_back(&msh->env, msh_lstnew(tmp[0], tmp[1]));
		free(tmp);
		i++;
	}
}

void init_shell(t_shell *msh)
{
	msh->env = NULL;
	msh->exit_status = 0;
	msh->have_a_pipe = 0;
}

int main(int argc, char **argv, char **env)
{
	t_shell msh;

	init_shell(&msh);
	create_env(&msh, env);
	shlvl(&msh);
	while (1)
	{
		msh.str = readline("\x1b[34mminishell$\x1b[0m ");
		add_history(msh.str);
		if (parser(&msh)) // parser part (pkari)
			execute_next(); // builtin part (abridger)
		free_all(&msh);
	}
}

