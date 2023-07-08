/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:56:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 12:22:50 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->in_fd != -1)
		close(args->token->out_fd);
	args->token->in_fd = open(args->token->redir[*i], O_RDONLY, 0777);
	if (args->token->in_fd == -1)
		perror("open");
	args->flag = 1;
	dup2(args->token->in_fd, STDIN_FILENO);
}

void	handle_output(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close(args->token->out_fd);
	args->token->out_fd = open(args->token->redir[*i],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	args->flag = 1;
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_append(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close(args->token->out_fd);
	dup2(args->token->in_fd, STDIN_FILENO);
	close(args->token->in_fd);
	args->token->out_fd = open(args->token->redir[*i],
			O_APPEND | O_CREAT | O_RDWR, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	args->flag = 1;
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_redir(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
			handle_append(args, &i);
		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '<')
			handle_heredoc(args, &i);
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<')
			handle_input(args, &i);
		i++;
	}
}

/* char	*expand(char *str, t_shell *args, int i)
{
	int		j;
	char	*str1;
	int		x;
	int		y

	x = 0;
	i++;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] !='\'')
	{
		str1[j++] = str[i++]
	}
	j = -1;
	while (args->env[++j])
	{
		if (var_is_equal(str1, args->env[j]))
		{
			while (args->env[j][x] != '=')
				x++;
			str1 = ft_strdup
		}
	}
} */

void	start_heredoc(t_shell *args, int i)
{
	char	*buffer;
	int		fd;
	char	*tmp;
	int		flag;

	flag = 1;
	dup2(args->stdout_here, STDOUT_FILENO);
	//close(args->out);
	dup2(args->stdin_here, STDIN_FILENO);
	//close(args->in);
	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		perror("open");
	while (1)
	{
		buffer = readline("heredoc >");
		if (buffer == NULL)
		{
			perror("heredoc");
			break ;
		}
		if (str_is_equal(buffer, args->token->redir[i]))
			break ;
		if (ft_strchr(buffer, '$'))
		{
				flag = 0;
				tmp = print_env_var(args, buffer);
		}
		if (flag == 0)
		{
			free (buffer);
			buffer = ft_strdup(tmp);
			free (tmp);
			ft_putendl_fd(buffer, fd);
			free (buffer);
		}
		else
		{
			ft_putendl_fd(buffer, fd);
			free(buffer);
		}
	}
	free(buffer);
	close(fd);
}
