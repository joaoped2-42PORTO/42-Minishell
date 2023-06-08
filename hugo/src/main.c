/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/08 11:41:14 by huolivei         ###   ########.fr       */
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

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

int	ft_wordcount_meta(char *str, char c)
{
	int		i;
	int		wordcount;
	char	quote;

	i = 0;
	wordcount = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wordcount++;
		while ((str[i] && str[i] != c) || (str[i] && quote))
		{
			quote = quote_value(str[i], quote);
			i++;
		}
	}
	return (wordcount);
}

static int	ft_wordlen(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((str[i] && (str[i] != c)) || (str[i] && quote))
	{
		quote = quote_value(str[i], quote);
		i++;
	}
	return (i);
}

static char	*get_word(char *s, char c, char **words)
{
	char	quote;

	quote = 0;
	*words = ft_substr(s, 0, ft_wordlen(s, c));
	while ((*s && *s != c) || (*s && quote))
	{
		quote = quote_value(*s, quote);
		s++;
	}
	return (s);
}

char	**split_meta(char *s, char c)
{
	char	**words;
	int		wdcount;
	int		j;

	j = 0;
	if (!s)
		return (0);
	wdcount = ft_wordcount_meta(s, c);
	words = (char **)malloc(sizeof(char *) * (wdcount + 1));
	if (!words)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			s = get_word(s, c, &words[j++]);
	}
	words[j] = 0;
	return (words);
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
		if(!valid_input(args))
		{
			printf("Forgot to close quotes or pipe\n");
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			args->token = init(args);
			init_token(args);
			args->split = split_meta(args->input, ' ');
			/*while (args->split[++j])
				printf("%s\n", args->split[j]);
			break;*/
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
