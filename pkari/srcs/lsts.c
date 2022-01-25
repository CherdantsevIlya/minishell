#include "../includes/minishell.h"

t_env *msh_lstnew(char *key, char *val)
{
	t_env *lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!(lst))
		return (NULL);
	lst->key = key;
	lst->val = val;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

t_env *msh_lstlast(t_env *env)
{
	t_env *tmp;

	if (!env)
		return (0);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void msh_lstadd_back(t_env **env, t_env *new)
{
	t_env *tmp;

	if (!(*env))
		*env = new;
	else
	{
		tmp = msh_lstlast(*env);
		new->prev = tmp;
		tmp->next = new;
	}
}
