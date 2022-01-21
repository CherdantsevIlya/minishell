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

#define TOKEN_PIPE				1 // |
#define TOKEN_REDIRECT_INPUT	2 // < (fd 0)
#define TOKEN_REDIRECT_OUTPUT1	3 // > (fd 1) перезаписывает файл
#define TOKEN_REDIRECT_OUTPUT2	4 // >> (fd 1) дописывает в файл
#define TOKEN_HEREDOC			5 // <<


typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_info
{
	int				token;
	int				argc;
	char			**argv;
	char			*output_file;
	int				fd_output_file;
	char			*input_file;
	int				fd_input_file;
	int 			error;
	struct s_info	*prev;
	struct s_info	*next;
}					t_info;

typedef struct	s_shell
{
	t_info	*info;
	t_env	*env;
	char	*str;
	int		exit_status;
	int 	have_a_pipe;
}			t_shell;

//*** main.c ***//
void init_shell(t_shell *msh);
void create_env(t_shell *msh, char **env);
char *get_dollar_env(t_env *env, char *str);
void shlvl(t_shell *msh);

//*** parser.c ***//
int parser(t_shell *msh);
void add_info(t_shell *msh);
t_info *add_new_info(void);

//*** quotes.c ***//
int single_quotes(t_shell *msh, int *i);
int double_quotes(t_shell *msh, int *i);

//*** dollar.c ***//
int dollar(t_shell *msh, int *i);

//*** tokens.c ***//
int token_space(t_shell *msh, int *i);
int token_pipe(t_shell *msh, int *i);
int token_redirects(t_shell *msh, int *i, int token);

//*** redirects.c ***//
void redirect_input(t_shell *msh, int *i);
void redirect_output(t_shell *msh, int *i);
void redirect_heredoc(t_shell *msh, int *i);


#endif
