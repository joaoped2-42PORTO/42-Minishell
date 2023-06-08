/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/08 11:42:21 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_processed_result(t_shell *args, char *res)
{
	int	k;

	k = 0;
	while (res[k])
	{
		if (isdoublequote(args) != 0)
		{
			printf("%s", res);
			break ;
		}
		if (res[k] == ' ' && res[k + 1] == ' ')
			k++;
		else if (res[k] == ' ' && k == 0)
			k++;
		else
			write(1, &res[k++], 1);
	}
	printf("\n");
}

void	processdefault(t_shell *args, int *x)
{
	char	*res;

	res = checkbars(args, x);
	print_processed_result(args, res);
	free(res);
}

void	process_option_n(t_shell *args, int *x)
{
	char	*res;
	int		i;

	i = *x;
	if (args->input[i] == '-' && args->input[i + 1] == 'n')
	{
		i += 2;
		while (args->input[i] == 'n')
			i++;
		if (args->input[i] == ' ' || args->input[i] == '\0')
		{
			i++;
			(*x) = i;
			res = checkbars(args, x);
			printf("%s", res);
			free(res);
			return ;
		}
	}
	processdefault(args, x);
}

void	checksplitcontent(t_shell *args)
{
	int	x;

	x = countvalues(args);
	if (x == 4)
	{
		printf("\n");
		return ;
	}
	else if (args->input[x] == '-' && args->input[x + 1] == 'n')
		process_option_n(args, &x);
	else
		processdefault(args, &x);
}

void	do_echo(t_shell *args)
{
	checksplitcontent(args);
}
