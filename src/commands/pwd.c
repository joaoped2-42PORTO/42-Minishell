/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/24 15:41:32 by huolivei         ###   ########.fr       */
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

	i = see_pwd(args->env);
	if (i > see_env_size(args))
	{
		ft_putendl_fd("No PWD recognized", 2);
		return ;
	}
	printf("%s\n", &args->pwd[5]);
}
