/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/11 12:52:36 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_pwd(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "PATH"))
			break ;
		i++;
	}
	return (i);
}

void	check_pwd(t_shell *args)
{
	int	i;
	int	j;

	j = 5;
	if (args->new_env[0] == 0)
	{
		i = see_pwd(args->env);
		while (args->env[i][j])
			printf("%c", args->env[i][j++]);
		printf("\n");
	}
	else
	{
		i = see_pwd(args->new_env);
		while (args->new_env[i][j])
			printf("%c", args->new_env[i][j++]);
		printf("\n");
	}
}
