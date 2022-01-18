#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct	s_shell
{
	t_env	*env;
	char	*str;
	int		exit_status;
}			t_shell;

#endif
