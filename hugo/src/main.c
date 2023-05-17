/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/17 22:22:05 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

//CTRL+I = ls -la ???

int	check_max_string(t_shell *args)
{
	int	i;

	i = 0;
	while(args->split[i])
		i++;
	return (i);
}

void	check_valid_input(t_shell *args)
{
	int	j;
	int	x;
	int	y;
	int	flag;

	y = 0;
	x = 0;
	j = 0;
	args->exp = ft_calloc(ft_strlen(args->input), sizeof(char));
	//args->split = ft_split(args->input, ' ');
	while (args->split[x])
	{
		j = 0;
		flag = 0;
		while (args->split[x][j])
		{
			if (args->split[x][j] == '"')
			{
				j++;
				while(1)
				{
					if (args->split[x] == 0)
						break ;
					while(args->split[x][j] != '"')
					{
						flag = 1;
						args->exp[y] = args->split[x][j];
						j++;
						y++;
						if (args->split[x][j] == '\0')
							break ;
					}
					if (flag == 1)
						args->exp[y++] = ' ';
					j = 0;
					x++;
				}
				flag = 1;
			}
			if (args->split[x] == 0)
						break ;
			j++;
		}
		if (args->split[x] == 0)
			break ;
		x++;
	}
	args->exp = ft_strtrim(args->exp, " ");
}

void	alloc_env_mem(char **str, char **str1, char **str2)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		str1[i] = ft_strdup(str[i]);
		str2[i] = ft_strdup("1");
	}
	str1[i] = 0;
	str2[i] = 0;
}

int	get_env_size(char **str)
{
	int	i;

	while(str[i])
		i++;
	return (i);
}

void	free_split(t_shell *args)
{
	int	i;

	i = -1;
	while (args->split[++i])
		free(args->split[i]);
	free(args->split);
}

void	get_path_struct(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "PWD=", 4))
		{
			free(args->path);
			args->path = ft_strdup(args->env[i]);
		}
		i++;
	}
	args->env[i] = 0;
}

void	init_values(t_shell *args, char	**env, int i)
{
	args->new_env = ft_calloc(sizeof(char *), i + 1);
	args->env = ft_calloc(sizeof(char *), i + 1);
	args->path = ft_calloc(1, sizeof(char));
	alloc_env_mem(env, args->env, args->new_env);
	get_path_struct(args);
	config_signals();
	args->exit_status = 127;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell	*args;
	int	i;

	i = get_env_size(env);
	args = malloc(sizeof(t_shell));
	init_values(args, env, i);
	while (1)
	{
		args->input = readline("👾Phylothinkers👾> ");
		if (args->input == NULL)
		{
			free(args->input);
			printf("\n");
			do_small_exit(args);
			break;
		}
		args->split = ft_split(args->input, ' ');
		if (args->input)
			add_history(args->input);
		if (cmdhandler(args) == 0)
			return (0);
		free(args->input);
		free_split(args);
	}
	return (0);
}
