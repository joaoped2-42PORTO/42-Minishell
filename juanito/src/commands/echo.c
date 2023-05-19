/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/19 14:49:45 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echonoflags(t_shell *args)
{
	int		i;
	int		j;
	int		x;
	int		z;
	int		flag;
	char	*src;
	//int		k;
	int		b;

	i = 5;
	flag = 0;
	b = 0;
	while (args->input[i])
	{
		if (args->input[i] == '$')
			b = 1;
		i++;
	}
	i = 5;
	while (args->input[i])
	{
		if (b >= 1)
		{
			if (args->input[i + 1] == '\0')
			{
				printf("$");
				break ;
			}
			if (args->input[i] == '"' || args->input[i] == '\'')
				i++;
			i++;
			j = 0;
			x = 0;
			z = 0;
			src = (char *) malloc(sizeof(char) * (ft_strlen(args->input + i) + 1));
			if (!src)
			{
				free(src);
				return ;
			}
			while (args->input[i] != '"' && args->input[i] != '\'')
				src[j++] = args->input[i++];
			src[j] = '\0';
			while (args->env[x])
			{
				if (ft_strncmp(src, args->env[x], ft_strlen(src)) == 0)
				{
					while (args->env[x][z] && args->env[x][z] != '=')
						z++;
					if (z == j)
					{
						z++;
						while (args->env[x][z])
							write(1, &args->env[x][z++], 1);
					}
					break ;
				}
				x++;
			}
			free (src);
		}
		else
			if (countvalues(args) == 1)
				break ;
	}
	printf("\n");
}

void	do_echo(t_shell *args)
{
	int		i;
	//int		x;
	//int		j;
	//int		z;
	int		flag;
	//char	*src;
	//int		k;

	flag = 0;
	if (!args->split[1])
		printf("\n");
	else if (!ft_strncmp(args->split[1], "-n", 2))
	{
		i = 8;
		while (args->input[i])
		{
			if (args->input[i] == '$')
			{
				if (args->input[i + 1] == '\0')
				{
					printf("$");
					break ;
				}
				break ;
				//countvalues(args);
				/*j = 0;
				x = 0;
				z = 0;
				src = (char *) malloc(sizeof(char) * (ft_strlen(args->input + i) + 1));
				if (!src)
				{
					free(src);
					return ;
				}
				while (args->input[i])
					src[j++] = args->input[i++];
				src[j] = '\0';
				while (args->env[x])
				{
					if (ft_strcmp(src, args->env[x]) == 0)
					{
						while (args->env[x][z] && args->env[x][z] != '=')
							z++;
						if (z == j)
							printf("%s", args->env[x]);
						break ;
					}
					x++;
				}
				free(src);*/
			}
			else
				if (countvalues(args) == 1)
					break ;
		}
	}
	else
		echonoflags(args);
}

