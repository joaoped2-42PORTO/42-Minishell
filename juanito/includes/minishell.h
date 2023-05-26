/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/25 13:37:12 by joaoped2         ###   ########.fr       */
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

typedef struct s_shell
{
	char	**new_splt;
	char	**new_env;
	char	**split;
	char	*input;
	char	**env;
	char	**argvs;
	char	*exp;
}		t_shell;

//Commands
void	check_files_in_path(char *str);
void	do_cd(t_shell *args);
void	check_pwd(void);

//Handler
int		cmdhandler(t_shell *args);
int		do_builtins(t_shell *args);

//Signals
void	config_signals(void);
void	change_env_oldpwd(t_shell *args);
void	change_env_pwd(t_shell *args);
void	do_mult_export(t_shell *args);
int		see_env_size(t_shell *args);
void	mult_export_new(t_shell *args);
void	print_export(t_shell *args);
void	matrix_cleaner(char	**str);
void	do_export(t_shell *args);
void	do_unset(t_shell *args);
void	print_env(t_shell *args);
void	do_echo(t_shell *args);
void	do_unset_new(t_shell *args);
void	checkermultexp2(t_shell *args, int *flag, int *y);
void	newenvmalloc(t_shell *args, int *y, int *i);
int		cleandel(t_shell *args);
void	freesformain(t_shell *args);
int		countvalues(t_shell *args);
char	*checkbars(t_shell *args, int *i);
void	treatingdollarsign(t_shell *args, int *i);
int		string(t_shell *args, int *i);
int		isdollar(t_shell *args);
void	getindexafterdollar(t_shell *args, int *i);
int		checkafterdollar(t_shell *args);
char	*print_env_var(t_shell *args, char *str);
void	put_var(t_shell *args, char	*str);
#endif
