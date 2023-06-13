/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/13 12:54:28 by huolivei         ###   ########.fr       */
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
	char	*cmd;
	char	*argm;
	char	*pipe_dir;
	struct s_tokenizer	*next;
}		t_comand;

typedef struct s_shell
{
	int		env_size;
	int		exit_status;
	char	*path;
	int		flag;
	t_comand	*token;
	char	**exp;
	char	**split; //1a experiencia
	char	*input; //1a experiencia
	char	**env; //1a experiencia
	char	**argvs; //1a experiencia
	int		index;
}		t_shell;

//Utils Functions

//Commands
//void	check_files_in_path(char *str);
void	do_cd(t_shell *args);
void	check_pwd(t_shell *args);

//Handler
int		cmdhandler(t_shell *args);
int		do_builtins(t_shell *args);

//Signals

void	config_signals(void);


void	change_env_oldpwd(t_shell *args);
void	change_env_pwd(t_shell *args);
void	do_mult_export(t_shell *args);
void	print_export(t_shell *args);
void	do_export(t_shell *args);
void	single_export(t_shell *args, int *j, int *x, int *i);
int		see_env_size(t_shell *args);
int		variable_size(char	*str);
//void	do_unset(t_shell *args);
//void	do_unset_new(t_shell *args);
int		check_doubles_vars(t_shell *args);
void	do_exit(t_shell *args);
void	child_signals(void);
void	free_matrix(char **str);
void	exchange_memo(t_shell *args, char **env, char **exp, int *i, int *x);
void	do_unset(t_shell *args);
char	**dup_env(char **str, char **str1);
void	init_token(t_shell *args);
t_comand	*get_bottom_stack(t_comand *stack);
void		add_bottom(t_comand **stack, t_comand *new);
int			check_pipe_rede(char c, char s);
void		init_values(t_shell *args, char	**env, int i);
t_comand	*init(t_shell *args);
void		do_small_exit(t_shell *args);
void	alloc_env_mem(char **str, char **str1, char **str2);
void	get_path_struct(t_shell *args);
int	free_list(t_shell *args);
int	free_split(t_shell *args);
int	get_env_size(char **str);
int	valid_input(t_shell *args);
void	put_var_args(t_shell *args, int *y, int *x, int *i);
char	**split_db_quotes(char *s, char c);
void	change_split(t_shell *args);

//Joao tokens
int			checkisalpha(t_shell *args, int *i);
void		append_char_to_res(char **res, char c);
void		process_whitespace(t_shell *args, int *x, char **res);
void		append_ptr2_to_res(char **res, char **ptr2, char **tmp);
void		process_single_quotes(t_shell *args, int *x, int *t, char **res);
void		process_dollar_sign(t_shell *args, int *x, int *k, char **res);
int			process_quote(t_shell *args, int *x, int *p);
void		process_dollar_or_char(t_shell *args, int *x, int *k, char **res);
void		process_input_condition(t_shell *args, int *x, int *k, char **res);
int			validate_input(t_shell *args);
void		process_string(t_shell *args, int *x, char **res, int *k);
void		process_input(t_shell *args, int *x, int *k, char **res);
char		*checkbars(t_shell *args);
char	*print_env_var(t_shell *args, char *str);

#endif
