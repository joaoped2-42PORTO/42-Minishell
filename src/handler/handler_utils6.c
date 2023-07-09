/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:40:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 15:21:54 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_null(char *buffer)
{
	if (buffer == NULL)
	{
		perror("heredoc");
		return (0);
	}
	return (1);
}

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

char	*get_env_value(t_shell *args, const char *name)
{
	char	*value;
	int		i;

	value = NULL;
	i = 1;
	while (args->env[i] != NULL)
	{
		if (ft_strncmp(args->env[i], name, ft_strlen(name)) == 0)
		{
			value = args->env[i] + ft_strlen(name) + 1;
			break ;
		}
		i++;
	}
	return (value);
}
