/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/23 22:46:15 by huolivei         ###   ########.fr       */
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

void	alloc_env_mem(char **str, char **str1)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		str1[i] = ft_strdup(str[i]);
	}
	str1[i] = 0;
}

int	get_env_size(char **str)
{
	int	i;

	i = 0;
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

int	check_pipe_rede(char c, char s)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	if ((c == '<' && s == '<') || (c == '>' && s == '>'))
		return (0);
	return (1);
}

t_comand	*get_bottom_stack(t_comand *stack)
{
	while (stack -> next)
		stack = stack -> next;
	return (stack);
}

t_comand	*init(t_shell *args)
{
	t_comand *ag;

	ag = malloc(sizeof(t_comand));
	if (!ag)
		return (NULL);
	ag->cmd = ft_calloc(ft_strlen(args->input), sizeof(char));
	ag->argm = ft_calloc(ft_strlen(args->input), sizeof(char));
	ag->pipe_dir = ft_calloc(3, sizeof(char));
	ag->next = NULL;
	return (ag);
}

void	add_bottom(t_comand **stack, t_comand *new)
{
	t_comand	*bottom;

	bottom = get_bottom_stack(*stack);
	bottom -> next = new;
}

void	init_token(t_shell *args)
{
	int	i;
	int	j;
	t_comand *tmp;

	tmp = args->token;
	j = 0;
	i = 0;
	while (args->input[i])
	{
		j = 0;
		while (!ft_isalnum(args->input[i]))
			i++;
		while (args->input[i] && args->input[i] != ' ')
			tmp->cmd[j++] = args->input[i++];
		if (args->input[i] == '\0')
			return ;
		i++;
		j = 0;
		while (!ft_isalnum(args->input[i]))
			i++;
		while (args->input[i] && check_pipe_rede(args->input[i], args->input[i + 1]))
			tmp->argm[j++] = args->input[i++];
		j = 0;
		if (args->input[i] != '\0')
		{
			if (!check_pipe_rede(args->input[i], args->input[i + 1]))
				add_bottom(&args->token, init(args));
			while (args->input[i] != ' ' && !ft_isalnum(args->input[i]))
				args->token->pipe_dir[j++] = args->input[i++];
		}
		tmp = tmp->next;
	}
}

void	init_values(t_shell *args, char	**env, int i)
{
	args->env = ft_calloc(sizeof(char *), i + 1);
	args->path = ft_calloc(1, sizeof(char));
	alloc_env_mem(env, args->env);
	get_path_struct(args);
	config_signals();
	args->exit_status = 127;
}

void	free_list(t_shell *args)
{
	t_comand *tmp;

	while (args->token)
	{
		tmp = args->token->next;
		free(args->token->cmd);
		free(args->token->argm);
		free(args->token->pipe_dir);
		free(args->token);
		args->token = tmp;
	}
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
			//free_list(args);
			do_small_exit(args);
			break;
		}
		args->token = init(args);
		init_token(args);
		args->split = ft_split(args->input, ' ');
		if (args->input)
			add_history(args->input);
		if (cmdhandler(args) == 0)
			return (0);
		free(args->input);
		free_split(args);
		free_list(args);
	}
	return (0);
}
