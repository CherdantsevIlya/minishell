/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:45:00 by abridger          #+#    #+#             */
/*   Updated: 2022/01/20 22:34:04 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <string.h>

typedef int	(*t_builtin)(t_data *data);
enum	e_command {echo, cd, pwd, export, unset, exit, env};


typedef struct s_env
{
	// char			*line; // вся строка переменной окружения
	char			*key; // ключ переменной окружения (до "равно")
	char			*sep; // разделитель ключа и значения (знак "равно", если есть)
	char			*value; // значение переменной окружения (после "равно")
	struct s_env	*next;
}					t_env;

typedef struct s_red  // структура с листами имен файлов для редиректа
{
	char			*name; // имя файла
	struct s_red	*prev;
	struct s_red	*next;
}					t_red;

typedef struct s_cmd // куда сохранять имя файла, если подается? в одном листе данные для выполнения одной команды?
{
	char			**cmd_args; // распарсенная строка из ридлайн (до точки с запятой, т.е. одна команда с аргументами), cmd_args[0] - команда?
	int				nb_cmd; // номер команды, если подана команда, на которую надо написать свою функцию, если nb=8, например, то команда исполяется execve
	t_red			*red_list; // если есть редирект, то записывать в листы имена файлов для редиректа
	int				red_flag; // если есть редирект, подумать над флагами, например 1, если > outfile; 2 если < infile, 0 - нет редиректов в команде
	int				pipe_flag; // если есть пайп, подумать над флагами 0 = нет пайпа, 1 = есть пайп
	struct s_cmd	*prev;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_data
{
	t_env			*envrmnt; // указатель на листы с переменными окружения
	t_cmd			*shell_cmd; // указатель на листы с командами и аргументами
	int				count; // количество команд по указателю на листы с командами и аргументами
	char			**array_path; // PATH значения, для исполнения execve, возможно лучше вынести в отдельную функцию и не сохранять в стр-ре, а вызывать, если потребуется
	int				pid; // для форка, чтобы в дочернем процессе запустить execve
	int				fd_red[2]; // дескрипторы для редиректа
	int				fd_pipe[2]; // дескрипторы пайпа;
	int				save_in; // для сохранения дескриптора 0
	int				save_out; // для сохранения дескриптора 1
}					t_data;

int			ft_strlen(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_split(char const *s, char c);

t_env		*ft_lstnew(const char *line);
t_env		*ft_lstlast(t_env *lst);
void		ft_lstadd_back(t_env **lst, t_env *new);
int			ft_len_key(char *str);
int			ft_len_value(char *str);
t_env		*parse_envrmnt(t_env *lst, char **envp);
void		ft_lst_clear(t_env **lst);

/* функции для создания массива переменных окружения
ft_lstsize_env - считает сколько переменных содержит "="
ft_lstsize_all - считает сколько всего переменных окружения (сколько заполненных листов)
ft_malloc_array_err(char **array, t_data *data, int check) - выделяет память и проверяет, выделилась ли
**create_array_env - создает массив переменных (где есть "=")
**create_array_all - создает массив со всеми переменными окружения
*/

int			ft_lstsize_env(t_data *data);
int			ft_lstsize_all(t_data *data);
int			ft_malloc_array_err(char ***array, t_data *data, int check);
char		**create_array_env(t_data *data, char **array);
char		**create_array_all(t_data *data, char **array);

int			ft_init_data(t_data *data, char **envp);
void		ft_array_clear(char **array);
void		ft_data_clear(t_data *data); // переписать, не работает
int			ft_error(int errnum, t_data *data, char *str); // проверить c errno
int			put_err_message(char *str);
int			action(t_data *data, char **envp);
char		**create_array_path(char **envp);
int			create_fork(t_data *data, char **envp, char *str_path);
int			ft_exec_in_child(t_data *data, char **envp);
int			ft_read_exec(t_data *data, char **envp);

/* функции для исполнения команд
ft_init_saved_fd - инициализирует fd, которые надо сохранить
ft_try_input - открывает файловый дескриптор на чтение, проверяет есть ли < редирект и имя файла за нми, если есть, то откроет файл на чтение, либо выдаст ошибку
ft_try_output - открывает файловый дескриптор на запись, проверяет есть ли > редирект и имя файла за нми, если есть, то откроет файл на запись, либо выдаст ошибку
ft_check_pipe - если есть пайп, откроет пайп
ft_close_saved_fd - закрывает дескрипторы
ft_execute - выполнит одну команду
ft_execution_cycle - выполнение в цикле по командам
*/
void		ft_init_saved_fd(t_data *data);
int			ft_try_input(t_data *data, t_cmd *curr);
int			ft_try_output(t_data *data, t_cmd *curr);
void		ft_check_pipe(t_data *data, t_cmd *curr);
void		ft_close_saved_fd(t_data *data);
t_builtin	*create_array_function(void);
void		ft_execute(t_data *data, t_cmd *curr);
void		ft_execution_cycle(t_data *data);
int		ft_exec_echo(t_data *data, t_cmd *curr);
int		ft_exec_cd(t_data *data, t_cmd *curr);
int		ft_exec_pwd(t_data *data, t_cmd *curr);
int		ft_exec_export(t_data *data, t_cmd *curr);
int		ft_exec_unset(t_data *data, t_cmd *curr);
int		ft_exec_exit(t_data *data, t_cmd *curr);
int		ft_exec_env(t_data *data, t_cmd *curr);





void		ft_test_readline(void); // delete
void		ft_print_lsts(t_data *data); // delete для проверки печати переменных окружения из листов
void		ft_print_array(t_data *data); // delete для проверки печати переменных окружения из массива

#endif
