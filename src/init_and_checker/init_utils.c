/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:26:22 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/22 16:47:47 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_rede(char c, char s)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	if ((c == '<' && s == '<') || (c == '>' && s == '>'))
		return (0);
	return (1);
}

void	add_bottom(t_comand **stack, t_comand *new)
{
	t_comand	*bottom;

	if (*stack == NULL)
	{
		*stack = new;
		return ;
	}
	bottom = get_bottom_stack(*stack);
	bottom->next = new;
}

t_comand	*get_bottom_stack(t_comand *stack)
{
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	alloc_env_mem(char **str, char **str1, char **str2)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		str1[i] = ft_strdup(str[i]);
		str2[i] = ft_strdup(str[i]);
	}
	str1[i] = 0;
	str2[i] = 0;
}

void	get_path_struct(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "PWD=", 4))
		{
			free (args->pwd);
			args->pwd = ft_strdup(args->env[i]);
		}
		i++;
	}
	args->env[i] = 0;
}
