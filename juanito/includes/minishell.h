/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 14:49:24 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/syscall.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_tokenizer
{
	char				*cmd;
	char				**argm;
	char				**redir;
	int					out_fd;
	int					in_fd;
	int					flag;
	struct s_tokenizer	*next;
}						t_comand;

typedef struct s_shell
{
	int					heredoc;
	int					env_size;
	int					exit_status;
	char				*path;
	t_comand			*token;
	char				**exp;
	char				**split;
	char				*input;
	char				**env;
	int					index;
	int					old_out;
	int					old_in;
	int					nr_red;
	int					in;
	int					out;
	int					list_size;
	int					issquote;
	int					isdquote;
	int					flag;
}						t_shell;

extern int	g_status;

//---------------------------SRC-------------------------------//

//----------Cleaner----------//

//-----cleaner-----//
int						get_env_size(char **str);
int						free_split(t_shell *args);
int						free_list(t_shell *args);
void					do_exit(t_shell *args);
void					do_small_exit(t_shell *args);

//-----cleaner2-----//
void					cleaneverything(t_shell *args);

//----------Commands----------//

//-----cd_utils-----//
int						change_pwd(char **str1);
void					first_old_pwd(char **str1);
void					change_env_oldpwd(t_shell *args);

//-----cd-----//
void					ft_homedk(t_shell *args);
void					change_env_pwd(t_shell *args);
void					change_exp_pwd(t_shell *args);
void					do_cd(t_shell *args);

//-----echo_checker-----//
int						checkforspacesinstring(t_shell *args, int i);

//-----echo_utils-----//
void					processdefault(t_shell *args);
int						checkforbig(t_shell *args);
int						check_index(t_shell *args, int *i);

//-----echo-----//
void					process_option_n(t_shell *args);
void					checkcontent(t_shell *args);
void					do_echo(t_shell *args);

//-----export_utils-----//
void					free_matrix(char **str);
int						see_split_size(t_shell *args);
void					exchange_memo_env(t_shell *args, char **env, int *i);
void					exchange_memo_exp(t_shell *args, char **exp, int *x);
void					export_counting(t_shell *args, int *x, int *i);

//-----export_utils2-----//
int						check_doubles_exp(t_shell *args, int y);
int						check_doubles_env(t_shell *args, int y);
int						see_env_size(t_shell *args);
char					**dup_env(char **str, char **str1);
int						see_chars(char *str);

//-----export_utils3-----//
int						suppforexportcounting(t_shell *args, int *y, int *z);

//-----export-----//
void					do_export(t_shell *args);
int						check_env_value(t_shell *args, char *str);
int						see_if_env(char *str);
int						see_exp_size(t_shell *args);
void					do_mult_export(t_shell *args);

//-----pwd-----//
int						see_pwd(char **str);
void					check_pwd(t_shell *args);

//-----unset_utils-----//
int						variable_size(char *str);
void					exchange_memo_unset_exp(t_shell *args, char **str,
							int *i);
void					exchange_memo_unset(t_shell *args, char **str, int *i);

//-----unset-----//
void					change_env_unset(t_shell *args, char **env, char *str1,
							int *y);
void					change_exp_unset(t_shell *args, char **exp, char *str1,
							int *x);
void					loop_unset(t_shell *args, char **exp, char **env,
							char *str1);
void					unset(t_shell *args, char *str1);
void					do_unset(t_shell *args);

//----------handler----------//

//-----handler_utils-----//
char					*print_env_var(t_shell *args, char *str);
void					open_exec_helper(t_shell *args, char *str);
void					open_exec(t_shell *args);
char					*get_path(t_shell *args);
char					*get_acess(char **str, t_comand *args);

//-----handler_utils2-----//
void					print_env(t_shell *args);
void					print_export(t_shell *args);
void					open_exec_abs(t_shell *args);
void					close_redirection(t_shell *args);
int						str_is_equal(char *str, char *str1);

//-----handler_utils3-----//
void					handle_input(t_shell *args, int *i);
void					handle_output(t_shell *args, int *i);
void					handle_append(t_shell *args, int *i);
void					handle_redir(t_shell *args);
void					start_heredoc(t_shell *args, int *i);

//-----handler_utils4-----//
void					handle_heredoc(t_shell *args, int *i);
void					execthenonbuiltin(t_shell *args, char *path);

//-----handler-----//
char					*nonbuiltinspath(t_shell *args,	char *path);
int						do_non_builtins(t_shell *args);
void					cmdhandler(t_shell *args);
int						ft_size(t_comand *lst);
void					executer(t_shell *args);

//-----pipe_utils-----//
char					*returncompletepath(t_comand *token, t_shell *args);
int						checklistsizeforpipes(t_comand *token);
int						handleexporttopipe(t_comand *tmp, t_shell *args);
int						isbuiltin(t_comand *tmp, t_shell *args);

//-----pipes-----//
void					handlefirstpipe(t_comand *token, t_shell *args,
							int *fd);
void					handlemidpipes(t_comand *token, t_shell *args, int *fd);
void					handlelastpipes(t_comand *token, t_shell *args,
							int *fd);
void					execpipes(t_comand *token, t_shell *args, int *fd,
							int *k);
void					pipes(t_comand *token, t_shell *args);
void					do_non_builtinsforpipes(t_shell *args, char *path);

//-----tokens-----//
int						process_quote(t_shell *args, int *x, int *p);
void					process_dollar_or_char(t_shell *args, int *x, int *k,
							char **res);
void					process_input_condition(t_shell *args, int *x, int *k,
							char **res);
int						validate_input(t_shell *args);
void					process_string(t_shell *args, int *x, char **res,
							int *k);

//-----tokens2-----//
int						checkisalpha(t_shell *args, int *i);
void					append_char_to_res(char **res, char c);
void					process_whitespace(t_shell *args, int *x, char **res);
void					append_ptr2_to_res(char **res, char **ptr2, char **tmp);
void					process_single_quotes(t_shell *args, int *x, int *t,
							char **res);

//-----tokens3-----//
void					process_dollar_sign(t_shell *args, int *x, int *k,
							char **res);
void					process_input(t_shell *args, int *x, int *k,
							char **res);
char					*checkbars(t_shell *args);

//----------init_and_checker----------//

//-----checker-----//
int						see_quote_double_string(char *str, int *i);
int						loop_input_helper(t_shell *args, int *i);
int						loop_input(t_shell *args, int *i);
int						valid_input(t_shell *args);

//-----init_utils-----//
int						check_pipe_rede(char c, char s);
void					add_bottom(t_comand **stack, t_comand *new);
t_comand				*get_bottom_stack(t_comand *stack);
void					alloc_env_mem(char **str, char **str1, char **str2);
void					get_path_struct(t_shell *args);

//-----init-----//
void					check_redir(t_shell *args, t_comand *ag, int *i,
							int *x);
int						check_for_first_redir(char **split, int *i);
t_comand				*init(t_shell *args, int *i);
t_comand				*init_token(t_shell *args);
void					init_values(t_shell *args, char **env, int i);

//-----utils-----//
int						checkpipered(t_shell *args, int *i);
int						see_closed_pipe(char *str, int *i);
int						see_dbquote_string(char *str, int *i);
int						see_quote_string(char *str, int *i);

//----------signals----------//

//-----signals-----//
void					handler(int sig);
void					config_signals(void);
void					new_prompt(int sig);

//----------main----------//

//-----main_utils2-----//
int						checkforinput(t_shell *args, size_t *i);
void					suppcountargs(char *str, int *i);
int						suppforquotes(char *str, int *i, int *dq, int *sq);

//-----main_utils-----//
int						ft_skipquotes(char *str);
int						ft_checkspecial(char *str);
int						ft_countargs(char *str);
char					**split_db_quotes(char *str);

//-----main-----//
int						check_valid_input(t_shell *args);
int						check_input(t_shell *args);
void					change_split(t_shell *args);

#endif
