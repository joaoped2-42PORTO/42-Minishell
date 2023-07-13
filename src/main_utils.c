/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:17:03 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/13 09:44:24 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_skipquotes(char *str)
{
	int	i;
	int	issquote;
	int	isdquote;

	issquote = 0;
	isdquote = 0;
	i = 0;
	if (suppforquotes(str, &i, &isdquote, &issquote) == 0)
		return (0);
	if (issquote)
	{
		while (str[i] != '\'')
			i++;
		i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[i] && (str[i] != '\'' || str[i] != '"'))
				i++;
		}
	}
	else if (isdquote)
	{
		while (str[i] && str[i] != '"')
			i++;
		i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[i] && (str[i] != '\'' || str[i] != '"'))
				i++;
		}
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
		suppcountargs(str, &i);
		if (!str[i])
			break ;
		++count;
		if (str[i] == '\'' || str[i] == '"')
			i += ft_skipquotes(str + i);
		else if (ft_checkspecial(str + i))
			i += ft_checkspecial(str + i);
		else
		{
			while (str[i] && str[i] != ' '&& str[i] != '\t' && !ft_checkspecial(str + i))
			{
				if (str[i] == '\'' || str[i] == '"')
					i += ft_skipquotes(str + i);
				i++;
			}
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
		while (str[l] && str[l] != ' '&& str[l] != '\t' && !ft_checkspecial(str + l))
			{
				if (str[l] == '\'' || str[l] == '"')
					l += ft_skipquotes(str + l);
				l++;
			}
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
		while ((*str != '\0' && *str == ' ') || (*str != '\0' && *str == '\t'))
			str++;
		result[i] = ft_word(str);
		str += ft_strlen(result[i++]);
	}
	result[i] = NULL;
	return (result);
}
