/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/20 17:16:43 by huolivei         ###   ########.fr       */
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
	i = see_pwd(args->env);
	while (args->env[i][j])
		printf("%c", args->env[i][j++]);
	printf("\n");
}
