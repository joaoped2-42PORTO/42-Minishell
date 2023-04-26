/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/26 17:03:42 by joaoped2         ###   ########.fr       */
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
	char	**split;
	char	*input;
	char	**env;
	char	**var;
	//int		**val;
}		t_shell;

//Commands
void	check_files_in_path(char *str);
void	do_cd(t_shell *args);
void	check_pwd(void);
void	clearcmd(t_shell *args);
void	lscmd(t_shell *args);
void	print_env(t_shell *args);
void	ft_export(t_shell *args);

//Handler
int		cmdhandler(t_shell *args);

//Signals
void	config_signals(void);

#endif
