/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 19:17:16 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*print_env_var(t_shell *args, char *str)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	src = NULL;
	while (args->env[i])
	{
		j = 0;
		while (args->env[i][j] && str[j] && args->env[i][j] == str[j])
			j++;
		if (args->env[i][j] == '=' && str[j] == '\0')
		{
			j++;
			free(src);
			src = ft_strdup(&args->env[i][j]);
			break ;
		}
		i++;
	}
	if (src == NULL)
		return (NULL);
	return (src);
}

char	*suppprintvar2(t_shell *args, char *str, char *src, char *src1)
{
	args->envar2x++;
	while (args->env[args->envar2i])
	{
		args->envar2j = 0;
		while (args->env[args->envar2i][args->envar2j]
			&& args->env[args->envar2i][args->envar2j] == str[args->envar2x])
		{
			args->envar2x++;
			args->envar2j++;
			if ((str[args->envar2x] >= 32 && str[args->envar2x] <= 47)
				|| (str[args->envar2x] >= 58 && str[args->envar2x] <= 64)
				|| (str[args->envar2x] >= 91 && str[args->envar2x] <= 96)
				|| ((str[args->envar2x] >= 123 && str[args->envar2x] <= 126))
				|| !str[args->envar2x])
			{
				args->envar2f = 1;
				break ;
			}
		}
		if (args->env[args->envar2i][args->envar2j] == '='
			&& args->envar2f == 1)
		{
			args->envar2j++;
			src1 = ft_strjoin(src, &args->env[args->envar2i][args->envar2j]);
			//free(src);
			break ;
		}
		args->envar2i++;
	}
	return (src1);
}

void	verifyvar2(t_shell *args, char *str)
{
	while (str[args->envar2x] != ' ' && args->envar2j == 0
		&& str[args->envar2x])
	{
		if (args->envar2f == 1)
		{
			args->envar2x++;
			break ;
		}
		args->envar2x++;
	}
}

void	initvalsforvar2(t_shell *args)
{
	args->envar2i = 0;
	args->envar2j = 0;
	args->envar2x = 0;
	args->envar2f = 0;
	args->envar2k = 0;
}

char	*print_env_var2(t_shell *args, char *str)
{
	char	*src;
	char	*src1;
	char	*src2;

	src = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	src1 = NULL;
	src2 = NULL;
	initvalsforvar2(args);
	while (str[args->envar2x])
	{
		if (str[args->envar2x] == '$')
		{
			src1 = suppprintvar2(args, str, src, src1);
			args->envar2f = 0;
			if (str[args->envar2x] >= 48 && str[args->envar2x] <= 57)
				args->envar2f = 1;
			verifyvar2(args, str);
			if (src1 == NULL)
				src2 = ft_strjoin(src, &str[args->envar2x]);
			else
			{
				src2 = ft_strdup(src1);
				free(src1);
				while (src2[args->envar2k] && str[args->envar2k])
					args->envar2k++;
			}
			free(src);
			src = src2;
		}
		else
		{
			src[args->envar2k] = str[args->envar2x];
			args->envar2k++;
			args->envar2x++;
		}
	}
	if (src2 == NULL)
		return (ft_strdup(""));
	return (src2);
}

void	open_exec_helper(t_shell *args, char *str)
{
	if (access(str, F_OK) == 0)
	{
		printf("%s: Permission denied\n", args->token->cmd);
		g_status = 126;
	}
	else if (execve(str, args->split, NULL) != 0)
	{
		printf("%s: No such file or directory\n", args->token->cmd);
		free(str);
		g_status = 127;
		exit(g_status);
	}
	exit(g_status);
}

void	open_exec(t_shell *args)
{
	char	*str;
	int		i;
	int		total;
	int		j;

	j = 0;
	total = (ft_strlen(args->path) + ft_strlen(args->split[0]));
	i = 4;
	str = malloc(total * sizeof(char));
	if (!str)
		return ;
	while (args->path[i])
		str[j++] = args->path[i++];
	i = 1;
	while (args->split[0][i])
		str[j++] = args->split[0][i++];
	str[j] = '\0';
	open_exec_helper(args, str);
	free(str);
	g_status = 0;
	exit(g_status);
}

char	*get_path(t_shell *args)
{
	int		i;
	char	*str;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "PATH", 4))
		{
			str = ft_strdup(args->env[i]);
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*get_acess(char **str, t_comand *args)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		join = ft_strjoin(tmp, args->cmd);
		free(tmp);
		if (access(join, F_OK) == 0)
			break ;
		if (str[i + 1] == 0)
			break ;
		i++;
		free(join);
	}
	free_matrix(str);
	return (join);
}
