/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:17:03 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/30 11:40:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	ft_skipquotes(char *str, t_shell *args)
{
	int	i;

	i = 0;
	if (str[i] != '\'' && str[i] != '"')
		return (0);
	if (str[i] == '\'')
		args->issquote = 1;
	if (str[i] == '"')
		args->isdquote = 1;
	i++;
	if (args->issquote)
	{
		while (str[i] != '\'')
			i++;
	}
	else if (args->isdquote)
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

int	ft_countargs(char *str, t_shell *args)
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
			i += ft_skipquotes(str + i, args);
		else if (ft_checkspecial(str + i))
			i += ft_checkspecial(str + i);
		else
		{
			while (str[i] && str[i] != ' ' && !ft_checkspecial(str + i)
				&& str[i] != '\'' && str[i] != '"')
				i++;
			if (!str[i])
				break ;
		}
	}
	return (count);
}

static char	*ft_word(char *str, t_shell *args)
{
	int		l;
	int		i;
	char	*res;

	l = 0;
	if (str[l] == '\'' || str[l] == '"')
		l += ft_skipquotes(str + l, args);
	else if (ft_checkspecial(str + l))
		l += ft_checkspecial(str + l);
	else
	{
		while (str[l] && str[l] != ' ' && !ft_checkspecial(str + l)
			&& str[l] != '\'' && str[l] != '"')
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

char	**split_db_quotes(t_shell *args, char *str)
{
	int		wcount;
	int		i;
	char	**result;

	wcount = ft_countargs(str, args);
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
		result[i] = ft_word(str, args);
		str += ft_strlen(result[i++]);
	}
	result[i] = NULL;
	return (result);
} */
