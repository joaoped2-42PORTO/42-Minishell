/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/18 13:03:11 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_status;

int	check_valid_input(t_shell *args)
{
	size_t	i;

	i = 0;
	if (args->input[0] == '\0')
	{
		rl_replace_line("", 0);
		rl_redisplay();
		free(args->input);
		return (0);
	}
	if (!valid_input(args))
	{
		ft_putendl_fd("Error on syntax", 2);
		g_status = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		free(args->input);
		return (0);
	}
	if (checkforinput(args, &i) == 0)
		return (0);
	add_history(args->input);
	return (1);
}

int	check_input(t_shell *args)
{
	args->input = readline("Phylothinkers > ");
	if (args->input == NULL)
	{
		free(args->input);
		printf("exit\n");
		do_small_exit(args);
		return (0);
	}
	return (1);
}

void	change_split(t_shell *args)
{
	char	*str;
	t_comand	*tmp;
	int			i;

	str = NULL;
	tmp = args->token;
	args->index = 0;
	while (tmp)
	{
		if (args->split[args->index][0] == '|')
			args->index++;
		i = 0;
		str = checkbars(args);
		free(tmp->cmd);
		tmp->cmd = ft_strdup(str);
		free(str);
		while (tmp->argm[i])
		{
			if (check_pipe_rede(args->split[args->index][0], args->split[args->index][1]))
			{
				str = checkbars(args);
				free(tmp->argm[i]);
				tmp->argm[i] = ft_strdup(str);
				free(str);
				i++;
				args->index++;
			}
			else
				args->index++;
		}
		if (args->split[args->index] && (args->split[args->index][0] == '>' || args->split[args->index][0] == '<'))
			args->index += 2;
		tmp = tmp->next;
	}
}

void	dothingsinsidemain(t_shell *args)
{
	while (1)
	{
		if (!check_input(args))
			break ;
		if (!check_valid_input(args))
			continue ;
		else
		{
			args->token = init_token(args);
			change_split(args);
			executer(args);
			free_split(args);
			free_list(args);
		}
		free(args->input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*args;
	int		i;

	g_status = 0;
	(void)av;
	if (ac > 1)
		printf("Too many arguments!\n");
	i = get_env_size(env);
	args = malloc(sizeof(t_shell));
	rl_clear_history();
	init_values(args, env, i);
	dothingsinsidemain(args);
	free_list(args);
	return (0);
}
