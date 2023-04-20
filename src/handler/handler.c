/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/20 14:41:47 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmdhandler(char *input)
{
	if (!ft_strncmp(input, "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(input, "cd ", 3))
		do_cd(input);
	else if (!ft_strncmp(input, "cd", 2))
	{
		chdir("/nfs/homes/");
		printf("OI!\n");
	}
	else if (!ft_strncmp(input, "exit", 4))
		return (0);
	/*else if (!ft_strncmp(input, "ls", 2))
	{
		if ((pid = fork()) == 0)
			execv(lspath, &input);
		waitpid(-1, NULL, 0);
	}
	else if(!ft_strncmp(input, "clear", 5))
	{
		if ((pid = fork()) == 0)
			execv(clear, &input);
		waitpid(-1, NULL, 0);
	}*/
	else
		printf("command not found: %s\n", input);
	return(1);
}
