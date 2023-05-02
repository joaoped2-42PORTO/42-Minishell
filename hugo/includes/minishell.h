/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/02 15:32:48 by huolivei         ###   ########.fr       */
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
	char	**split; //1a experiencia
	char	*input; //1a experiencia
	char	**env; //1a experiencia
	char	**argvs; //1a experiencia
	char	*exp;
}		t_shell;

//Utils Functions

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
#endif
