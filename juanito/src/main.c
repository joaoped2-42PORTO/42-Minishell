/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/29 15:16:59 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_input(t_shell *args)
{
	if (args->input[0] == '\0')
	{
		rl_replace_line("", 0);
		rl_redisplay();
		free(args->input);
		return (0);
	}
	if (!valid_input(args))
	{
		printf("Forgot to close quotes or pipe\n");
		rl_replace_line("", 0);
		rl_redisplay();
		free(args->input);
		return (0);
	}
	return (1);
}

int	check_input(t_shell *args)
{
	args->input = readline("👾Phylothinkers👾> ");
	if (args->input == NULL)
	{
		free(args->input);
		printf("\n");
		do_small_exit(args);
		return (0);
	}
	add_history(args->input);
	return (1);
}

void	change_split(t_shell *args)
{
	char	*str;

	args->index = 0;
	while (args->split[args->index])
	{
		str = checkbars(args);
		free(args->split[args->index]);
		args->split[args->index] = ft_strdup(str);
		free(str);
		args->index++;
	}
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
		if (!check_input(args))
			break ;
		if (!check_valid_input(args))
			continue ;
		else
		{
			args->token = init_token(args);
			executer(args);
			free_split(args);
			free_list(args);
		}
		free(args->input);
	}
	return (0);
}
