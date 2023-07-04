/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/04 11:11:26 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	open_exec_helper(t_shell *args, char *str)
{
	if (execve(str, args->split, NULL) != 0)
	{
		perror("Error");
		free(str);
		args->exit_status = 126;
		exit(126);
	}
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
	args->exit_status = 0;
	exit(0);
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
