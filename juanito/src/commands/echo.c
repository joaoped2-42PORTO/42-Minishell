/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/07 12:41:27 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkforspacesinstring(t_shell *args, int i)
{
	int	j;

	j = 0;
	if (!args->input[i])
		return (0);
	while (args->input[i])
	{
		while (args->input[i] != ' ' && args->input[i])
			i++;
		while (args->input[i] == ' ' && args->input[i])
		{
			j++;
			i++;
		}
		return (j);
		i++;
	}
	return (j);
}

int	isdoublequote(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
/*
void	checksplitcontent(t_shell *args)
{
	int		i;
	int		j;
	int		x;
	int		k;
	char	*res;

	res = NULL;
	i = 0;
	j = 1;
	k = 0;
	x = countvalues(args);
	if (x == 4)
	{
		printf("\n");
		return ;
	}
	else if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
	{
		while (args->split[j])
		{
			if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
			{
				i = 0;
				i++;
				while (args->split[j][i] == 'n')
					i++;
				if (args->split[j][i] == '\0')
				{
					j++;
					x += i;
					x += checkforspacesinstring(args, x);
					i = 0;
				}
			}
			else
			{
				printf("%s", args->split[j]);
				if (args->split[j + 1])
					printf(" ");
				j++;
			}
		}
		if (!args->split[j])
			return ;
		else
		{
			i = countvalues(args);
			res = checkbars(args, &i);
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
			k = 0;
			free(res);
			printf("\n");
			return ;
		}
	}
	else
	{
		i = countvalues(args);
		res = checkbars(args, &i);
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
		k = 0;
		free(res);
		printf("\n");
		return ;
	}
	res = checkbars(args, &x);
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
	k = 0;
	free(res);
}*/

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

void	process_option_n(t_shell *args, int *j, int *x)
{
	int		i;
	char	*res;

	i = 0;
	while (args->split[*j])
	{
		if (args->split[*j][i] == '-' && args->split[*j][i + 1] == 'n')
		{
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
		}
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
