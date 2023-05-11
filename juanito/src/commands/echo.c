/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/08 16:02:20 by joaoped2         ###   ########.fr       */
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

	i = 5;
	flag = 0;
	while (args->input[i])
	{
		if (args->input[i] == '$')
		{
			if (args->input[i + 1] == '\0')
			{
				printf("$");
				break ;
			}
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
			while (args->input[i])
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
		{
			while (args->input[i])
			{
				if (args->input[i] == '\'' || args->input[i] == '"')
					flag++;
				i++;
			}
			i = 5;
			while (args->input[i])
			{
				if (flag == 2)
					write(1, &args->input[i++], 1);
				else
				{
					printf("Error");
					break ;
				}
			}
		}
		break ;
	}
	printf("\n");
}

void	do_echo(t_shell *args)
{
	int		i;
	int		x;
	int		j;
	int		z;
	int		flag;
	char	*src;

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
				free(src);
			}
			else
			{
				while (args->input[i])
				{
					if (args->input[i] == '\'' || args->input[i] == '"')
						flag++;
					i++;
				}
				i = 8;
				while (args->input[i])
				{
					if (flag == 2)
						write(1, &args->input[i++], 1);
					else
					{
						printf("Error");
						break ;
					}
				}
			}
			break;
		}
	}
	else
		echonoflags(args);

}