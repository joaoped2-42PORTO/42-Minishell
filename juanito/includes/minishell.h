/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 14:50:24 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/syscall.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_tokenizer
{
	char				*cmd;
	char				**argm;
	char				*pipe_dir;
	struct s_tokenizer	*next;
}		t_comand;

typedef struct s_shell
{
	int			env_size;
	int			exit_status;
	char		*path;
	int			flag;
	t_comand	*token;
	char		**exp;
	char		**split;
	char		*input;
	char		**env;
	char		**argvs;
	int			index;
}		t_shell;

//cleaner | cleaner.c
int			get_env_size(char **str);
int			free_split(t_shell *args);
int			free_list(t_shell *args);
void		do_exit(t_shell *args);
void		do_small_exit(t_shell *args);

//commands | cd_utils.c
int			change_pwd(char **str1);
void		first_old_pwd(char **str1);
void		change_env_oldpwd(t_shell *args);

//commands | cd.c
void		ft_homedk(t_shell *args);
void		change_env_pwd(t_shell *args);
void		do_cd(t_shell *args);

//commands | echo_checker.c
int			checkforspacesinstring(t_shell *args, int i);

//commands | echo_utils.c
void		processdefault(t_shell *args);
int			print_option_n(t_shell *args);
int			check_index(t_shell *args, int *i);

//commands | echo.c
void		process_option_n(t_shell *args);
void		checkcontent(t_shell *args);
void		do_echo(t_shell *args);

//commands | export_utils.c
int			see_env_size(t_shell *args);
char		**dup_env(char **str, char **str1);
void		free_matrix(char **str);
int			see_split_size(t_shell *args);
void		exchange_memo(t_shell *args, char **env, char **exp, int *i, int *x);

//commands | export_utils2.c
int			do_loop_doubles(t_shell *args, int j);
int			check_doubles_vars(t_shell *args);

//commands | export.c
int			see_if_env(char	*str);
int			see_exp_size(t_shell *args);
void		do_mult_export(t_shell *args);

//commands | export2.c
int			check_input_exp(t_shell *args);
void		do_export(t_shell *args);
int			check_space_in_string(t_shell *args, int *y);
int			ft_isalnum_mini(int c);
int			check_env_value(t_shell *args, char *str);

//commands | pwd.c
int			see_pwd(char	**str);
void		check_pwd(t_shell *args);

//commands | unset_utils.c
int			variable_size(char	*str);

//commands | unset.c
void		exchange_memo_unset(t_shell *args, char **str, int *i);
void		unset(t_shell *args, char *str1);
void		do_unset(t_shell *args);

//handler | handler.c
char		*print_env_var(t_shell *args, char *str);
void		open_exec(t_shell *args);
void		open_exec_abs(t_shell *args);
char		*get_path(t_shell *args);
char		*get_acess(char	**str, t_shell *args);

//handler | handler2.c
int			do_non_builtins(t_shell *args);
void		print_env(t_shell *args);
void		print_export(t_shell *args);
int			cmdhandler(t_shell *args);

//handler | handler3.c
void		executepid(t_shell *args);
char		*getthepath(t_shell *args);
void		open_exec_helper(t_shell *args, char *str);

//handler | tokens.c
int			process_quote(t_shell *args, int *x, int *p);
void		process_dollar_or_char(t_shell *args, int *x, int *k, char **res);
void		process_input_condition(t_shell *args, int *x, int *k, char **res);
int			validate_input(t_shell *args);
void		process_string(t_shell *args, int *x, char **res, int *k);

//handler | tokens2.c
int			checkisalpha(t_shell *args, int *i);
void		append_char_to_res(char **res, char c);
void		process_whitespace(t_shell *args, int *x, char **res);
void		append_ptr2_to_res(char **res, char **ptr2, char **tmp);
void		process_single_quotes(t_shell *args, int *x, int *t, char **res);

//handler | tokens3.c
void		process_dollar_sign(t_shell *args, int *x, int *k, char **res);
void		process_input(t_shell *args, int *x, int *k, char **res);
char		*checkbars(t_shell *args);

//handler | utils.c
char		*ft_strcpy1(char *dest, const char *src);

//init_and_checker | checker_utils.c
int			loop_input(t_shell *args, int *i);
int			loop_input2(t_shell *args, int *i);
//init_and_checker | checker.c
int			see_closed_pipe(char *str, int *i);
int			see_dbquote_string(char *str, int *i);
int			see_quote_string(char *str, int *i);
int			see_quote_double_string(char *str, int *i);
int			loop_input(t_shell *args, int *i);
int			loop_input2(t_shell *args, int *i);
int			valid_input(t_shell *args);

//init_and_checker | init_utils.c
int			check_pipe_rede(char c, char s);
void		add_bottom(t_comand **stack, t_comand *new);
t_comand	*get_bottom_stack(t_comand *stack);
void		alloc_env_mem(char **str, char **str1, char **str2);
void		get_path_struct(t_shell *args);

//init_and_checker | init.c
t_comand	*init(t_shell *args, int *i);
t_comand	*init_token(t_shell *args);
void		init_values(t_shell *args, char	**env, int i);

//signals | signals.c
void		handler(int sig);
void		config_signals(void);

//main | main_utils.c
char		quote_value(char c, char quote);
int			ft_wordcount_meta(char *str, char c);
int			ft_wordlen(char *str, char c);
char		*get_word(char *s, char c, char **words);
char		**split_db_quotes(char *s, char c);

//main | main.c
int			check_valid_input(t_shell *args);
int			check_input(t_shell *args);
void		change_split(t_shell *args);

#endif
