/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 22:12:44 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* char	*print_env_var(t_shell *args, char *str)
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
} */

char	*print_env_var(t_shell *args, char *str)
{
	int		i;
	int		j;
	char	*src;
	char	*src1;
	//char	*rst;
	int		x;

	i = 0;
	j = 0;
	x = -1;
	src = ft_calloc(ft_strlen(str), 1);
	src1 = NULL;
	while (str[++x] != '$')
		src[x] = str[x];
	x++;
	while (args->env[i])
	{
		j = 0;
		while (args->env[i][j] && args->env[i][j] == str[x])
		{
			x++;
			j++;
		}
		if (args->env[i][j] == '=' && str[x] == '\0')
		{
			j++;
			//free(src);
			src1 = ft_strjoin(src, &args->env[i][j]);
			break ;
		}
		i++;
	}
	//rst = ft_strjoin(src, src1);
	if (src1[0] == '\0')
		return (NULL);
	return (src1);
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
