/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:30:01 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 16:04:41 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = dest;
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*see_aplha_expander(t_shell *args, char *str, char *ptr, int *i)
{
	args->var_start = *i;
	while (ft_isalnum(str[*i]))
		(*i)++;
	args->var_len = *i - args->var_start;
	args->var_name = malloc((args->var_len + 1) * sizeof(char));
	ft_strncpy(args->var_name, &str[args->var_start], args->var_len);
	args->var_name[args->var_len] = '\0';
	args->env_value = get_env_value(args, args->var_name);
	free(args->var_name);
	if (args->env_value != NULL)
	{
		while (*args->env_value)
			*ptr++ = *args->env_value++;
	}
	else if (str[*i] != ' ' && str[*i] != '\0')
	{
		*ptr++ = ' ';
		*ptr++ = str[*i];
	}
	return (ptr);
}

char	*see_digit_expander(t_shell *args, char *ptr, char *str, int *i)
{
	args->var_start = *i;
	(*i)++;
	args->var_len = *i - args->var_start;
	args->var_name = malloc((args->var_len + 1) * sizeof(char));
	ft_strncpy(args->var_name, &str[args->var_start], args->var_len);
	args->var_name[args->var_len] = '\0';
	args->env_value = get_env_value(args, args->var_name);
	free(args->var_name);
	if (args->env_value != NULL)
	{
		while (*args->env_value)
			*ptr++ = *args->env_value++;
	}
	return (ptr);
}

char	*get_result(char *str)
{
	size_t	len;
	char	*rst;

	rst = NULL;
	len = ft_strlen(str);
	rst = ft_calloc(len + 1, sizeof(char));
	return (rst);
}

char	*print_env_var2(t_shell *args, char *str)
{
	char	*result;
	char	*ptr;
	int		i;

	result = get_result(str);
	ptr = result;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (ft_isdigit(str[i]))
				ptr = see_digit_expander(args, ptr, str, &i);
			else if (ft_isalpha(str[i]))
				ptr = see_aplha_expander(args, str, ptr, &i);
			else
				*ptr++ = '$';
		}
		else
			*ptr++ = str[i++];
	}
	*ptr = '\0';
	return (result);
}
