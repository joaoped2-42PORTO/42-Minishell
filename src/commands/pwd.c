/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 20:40:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	see_pwd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (var_is_equal(str[i], "PWD"))
			return (i);
		i++;
	}
	i++;
	return (i);
}

void	check_pwd(t_shell *args)
{
	int	i;
	/* int	j;

	j = 5 */;
	i = see_pwd(args->env);
	if (i > see_env_size(args))
	{
		ft_putendl_fd("No PWD recognized", 2);
		return ;
	}
	printf("%s\n", &args->pwd[5]);
	/* while (args->env[i][j])
		printf("%c", args->env[i][j++]); */
	//printf("\n");
}
