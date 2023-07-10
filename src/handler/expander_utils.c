/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:52:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 12:52:56 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isprintable(char c)
{
	if (c >= 33 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 126)
		return (1);
	else
		return (0);
	return (1);
}

void	checkisnumonfirst(char *str, int *x, char **res)
{
	(*x)++;
	while (str[*x] != ' ' && str[*x])
		append_char_to_res1(res, str[(*x)++]);
}

int	checkdollar(char *str, int *x)
{
	if (str[*x] == '$' && str[*x + 1] != '$'
		&& str[*x + 1] != ' ' && str[*x + 1] != '\0')
		return (1);
	else
		return (0);
	return (1);
}

void	append_ptr2_to_res1(char **res, char **ptr2, char **tmp)
{
	if (*ptr2)
	{
		*tmp = malloc(ft_strlen(*res) + ft_strlen(*ptr2) + 1);
		ft_strcpy(*tmp, *res);
		ft_strcat(*tmp, *ptr2);
		free(*res);
		*res = *tmp;
		free(*ptr2);
	}
}

void	append_char_to_res1(char **res, char c)
{
	char	*ptr;
	char	*tmp;

	ptr = (char *)malloc(2 * sizeof(char));
	ptr[0] = c;
	ptr[1] = '\0';
	tmp = malloc(ft_strlen(*res) + ft_strlen(ptr) + 1);
	ft_strcpy(tmp, *res);
	ft_strcat(tmp, ptr);
	free(*res);
	*res = tmp;
	free(ptr);
}
