/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:23:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/24 12:34:29 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_countargsaux(int *i, char *str)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !ft_checkspecial(str + *i))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_skipquotes(str + *i);
		else
			(*i)++;
	}
}

void	init_lexer(char *str, t_shell *args, t_comand *tmp)
{
	if (!args->split[args->index])
		return ;
	if (args->split[args->index][0] == '|')
		args->index++;
	str = checkbars(args);
	free(tmp->cmd);
	tmp->cmd = ft_strdup(str);
	free(str);
}

void	lexer_argm(char	*str, t_shell *args, t_comand *tmp)
{
	str = checkbars(args);
	free(tmp->argm[args->index_arg]);
	tmp->argm[args->index_arg] = ft_strdup(str);
	free(str);
	args->index_arg++;
	args->index++;
}

void	lexer_redir(char *str, t_shell *args, t_comand *tmp)
{
	str = checkbars(args);
	free (tmp->redir[args->index_redir]);
	tmp->redir[args->index_redir] = ft_strdup(str);
	free(str);
	args->index_redir++;
	args->index++;
	str = checkbars(args);
	free (tmp->redir[args->index_redir]);
	tmp->redir[args->index_redir] = ft_strdup(str);
	free(str);
	args->index_redir++;
	args->index++;
}

void	child_exit(t_shell *args)
{
	g_status = 0;
	free_split(args);
	free_list(args);
	do_small_exit(args);
}
