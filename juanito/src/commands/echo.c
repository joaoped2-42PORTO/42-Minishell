/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/07 14:57:38 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_remaining(t_shell *args, int *j, int *x)
{
	int	i;

	i = 0;
	i++;
	while (args->split[*j][i] == 'n')
		i++;
	if (args->split[*j][i] == '\0')
	{
		(*j)++;
		(*x) += i;
		(*x) += checkforspacesinstring(args, *x);
		i = 0;
	}
	else
	{
		printf("%s", args->split[*j]);
		if (args->split[*j + 1])
			printf(" ");
		(*j)++;
	}
}

void	process_option_n(t_shell *args, int *j, int *x)
{
	char	*res;
	int		i;

	i = 0;
	while (args->split[*j])
	{
		if (args->split[*j][i] == '-' && args->split[*j][i + 1] == 'n')
			process_remaining(args, j, x);
		else
		{
			printf("%s", args->split[*j]);
			if (args->split[*j + 1])
				printf(" ");
			(*j)++;
		}
	}
	if (!args->split[*j])
		return ;
	i = countvalues(args);
	res = checkbars(args, &i);
	print_processed_result(args, res);
	free(res);
}

void	processdefault(t_shell *args, int *x)
{
	char	*res;

	res = checkbars(args, x);
	print_processed_result(args, res);
	free(res);
}

void	checksplitcontent(t_shell *args)
{
	int	x;
	int	j;

	j = 1;
	x = countvalues(args);
	if (x == 4)
	{
		printf("\n");
		return ;
	}
	else if (args->split[j][0] == '-' && args->split[j][1] == 'n')
		process_option_n(args, &j, &x);
	else
		processdefault(args, &x);
}

void	do_echo(t_shell *args)
{
	checksplitcontent(args);
}
