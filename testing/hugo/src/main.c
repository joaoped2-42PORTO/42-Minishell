/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/21 20:31:37 by user             ###   ########.fr       */
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
// Testes antigos, ainda podem ser uteis
/*
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
}*/

int	ft_skipquotes(char *str)
{
	int	i;
	int	issquote;
	int	isdquote;

	issquote = 0;
	isdquote = 0;
	i = 0;
	if (str[i] != '\'' && str[i] != '"')
		return (0);
	if (str[i] == '\'')
		issquote = 1;
	if (str[i] == '"')
		isdquote = 1;
	i++;
	if (issquote)
	{
		while (str[i] != '\'')
			i++;
	}
	else if (isdquote)
	{
		while (str[i] != '"')
			i++;
	}
	i++;
	return (i);
}

int	ft_checkspecial(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	ft_countargs(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		++count;
		if (str[i] == '\'' || str[i] == '"')
			i += ft_skipquotes(str + i);
		else if (ft_checkspecial(str + i))
			i += ft_checkspecial(str + i);
		else
		{
			while (str[i] && str[i] != ' ' && !ft_checkspecial(str + i) && str[i] != '\'' && str[i] != '"')
				i++;
			if (!str[i])
				break ;
		}
	}
	return (count);
}

static char	*ft_word(char *str)
{
	int		l;
	int		i;
	char	*res;

	l = 0;
	if (str[l] == '\'' || str[l] == '"')
			l += ft_skipquotes(str + l);
	else if (ft_checkspecial(str + l))
		l += ft_checkspecial(str + l);
	else
	{
		while (str[l] && str[l] != ' ' && !ft_checkspecial(str + l) && str[l] != '\'' && str[l] != '"')
				l++;
	}
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	i = 0;
	while (i < l)
		res[i++] = *str++;
	return (res);
}

char	**split_db_quotes(char *str)
{
	int		wcount;
	int		i;
	char	**result;

	wcount = ft_countargs(str);
	if (!wcount)
		return (NULL);
	result = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		while (*str != '\0' && *str == ' ')
			str++;
		result[i] = ft_word(str);
		str += ft_strlen(result[i++]);
	}
	result[i] = NULL;
	return (result);
}

int	check_valid_input(t_shell *args)
{
	if (args->input[0] == '\0')
	{
		rl_replace_line("", 0);
		rl_redisplay();
		free(args->input);
		return (0);
	}
	if(!valid_input(args))
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
	if(args->input == NULL)
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
		free (str);
		args->index++;
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
		if (!check_input(args))
			break;
		if (!check_valid_input(args))
			continue;
		else
		{
			args->token = init_token(args);
			cmdhandler(args);
			free_split(args);
			free_list(args);
		}
		free(args->input);
	}
	return (0);
}
