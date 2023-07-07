/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 19:21:42 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_pwd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (var_is_equal(str[i], "PWD"))
			return(i);
		i++;
	}
	i++;
	return (i);
}

void	check_pwd(t_shell *args)
{
	int	i;
	int	j;

	j = 5;
	i = see_pwd(args->env);
	printf("index : %d\n env size : %d\n", i, see_env_size(args));
	if (i > see_env_size(args))
	{
		printf("No PWD recognized\n");
		return ;
	}
	while (args->env[i][j])
		printf("%c", args->env[i][j++]);
	printf("\n");
}
