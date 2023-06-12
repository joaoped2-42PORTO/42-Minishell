/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/12 14:56:42 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_max_string(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[i])
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
	while (args->split[x])
	{
		j = 0;
		flag = 0;
		while (args->split[x][j])
		{
			if (args->split[x][j] == '"')
			{
				j++;
				while (1)
				{
					if (args->split[x] == 0)
						break ;
					while (args->split[x][j] != '"')
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

int	main(int ac, char **av, char **env)
{
	t_shell	*args;
	int		i;

	(void)ac;
	(void)av;
	i = get_env_size(env);
	args = malloc(sizeof(t_shell));
	init_values(args, env, i);
	while (1)
	{
		args->input = readline("👾Phylothinkers👾> ");
		if (args->input)
			add_history(args->input);
		if (args->input == NULL)
		{
			free(args->input);
			printf("\n");
			do_small_exit(args);
			break ;
		}
		if (!valid_input(args))
		{
			printf("Forgot to close quotes or pipe\n");
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			args->token = init(args);
			init_token(args);
			args->split = ft_split(args->input, ' ');
			if (args->input)
				add_history(args->input);
			if (cmdhandler(args) == 0)
				return (0);
			free_split(args);
			free_list(args);
		}
		free(args->input);
	}
	return (0);
}
