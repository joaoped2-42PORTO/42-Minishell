/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/14 17:26:04 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_max_string(t_shell *args)
{
	int	i;

	i = 0;
	while(args->split[i])
		i++;
	return (i);
}

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

int	ft_wordlen(char *str, char c)
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


char	*get_word(char *s, char c, char **words)
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

char	**split_db_quotes(char *s, char c)
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

int	check_valid_input(t_shell *args)
{
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
