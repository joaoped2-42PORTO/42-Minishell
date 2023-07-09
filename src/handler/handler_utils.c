/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 15:27:49 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  char	*print_env_var2(t_shell *args, char *str)
{
	size_t	len;
	char	*result;
	char	*ptr;
	int		i;
	size_t	var_start;
	size_t	var_len;
	char	*var_name;
	char	*env_value;

	len = ft_strlen(str);
	result = malloc((len + 1) * sizeof(char));
	ptr = result;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (isdigit(str[i]))
			{
				var_start = i;
				i++;
				var_len = i - var_start;
				var_name = malloc((var_len + 1) * sizeof(char));
				ft_strncpy(var_name, &str[var_start], var_len);
				var_name[var_len] = '\0';
				env_value = get_env_value(args, var_name);
				free(var_name);
				if (env_value != NULL)
				{
					while (*env_value)
						*ptr++ = *env_value++;
				}
			}
			else if (isalpha(str[i]))
			{
				var_start = i;
				while (isalnum(str[i]))
					i++;
				var_len = i - var_start;
				var_name = malloc((var_len + 1) * sizeof(char));
				ft_strncpy(var_name, &str[var_start], var_len);
				var_name[var_len] = '\0';
				env_value = get_env_value(args, var_name);
				free(var_name);
				if (env_value != NULL)
				{
					while (*env_value)
						*ptr++ = *env_value++;
				}
				else if (str[i] != ' ' && str[i] != '\0')
				{
					*ptr++ = ' ';
					*ptr++ = str[i];
				}
			}
			else
				*ptr++ = '$';
		}
		else
			*ptr++ = str[i++];
	}
	*ptr = '\0';
	return (result);
} */

void	open_exec_helper(t_shell *args, char *str)
{
	(void)str;
	if (access(args->token->argm[0], X_OK) == 0)
		execve(args->token->argm[0], args->token->argm, NULL);
	else if (access(str, F_OK) == 0)
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
