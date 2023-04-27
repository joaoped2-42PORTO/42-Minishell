/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 13:25:09 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_pwd(t_shell *args)
{
	/*char	path[1000];

	getcwd(path, sizeof(path));
	if (path[0] == '\0')
		printf("Something went wrong!\n");
	else
		printf("%s\n", path);*/
	int	i;
	char	*pwd = NULL;

	i = 0;
	while (args->env[i])
	{
		if (!strncmp(args->env[i], "PWD=", 4))
			pwd = args->env[i] + 4;
		i++;
	}
	if (!pwd)
		return;
	else
		printf("%s\n", pwd);
}
