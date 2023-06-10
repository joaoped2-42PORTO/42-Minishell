/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:00:46 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/10 19:53:03 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkisalpha(t_shell *args, int *i)
{
	int	x;

	x = *i;
	if (args->input[x] >= 48 && args->input[x] <= 57)
		return (1);
	else if (args->input[x] >= 65 && args->input[x] <= 90)
		return (1);
	else if (args->input[x] >= 97 && args->input[x] <= 122)
		return (1);
	return (0);
}

void	append_char_to_res(char **res, char c)
{
	char	*ptr;
	char	*tmp;

	ptr = (char *)malloc(2 * sizeof(char));
	ptr[0] = c;
	ptr[1] = '\0';
	tmp = malloc(ft_strlen(*res) + ft_strlen(ptr) + 1);
	strcpy(tmp, *res);
	strcat(tmp, ptr);
	free(*res);
	*res = tmp;
	free(ptr);
}

void	process_whitespace(t_shell *args, int *x, char **res)
{
	while (args->input[*x] == ' ' && args->input[*x + 1] == ' ')
		(*x)++;
	append_char_to_res(res, args->input[(*x)++]);
}

void	append_ptr2_to_res(char **res, char **ptr2, char **tmp)
{
	if (*ptr2)
	{
		*tmp = malloc(ft_strlen(*res) + ft_strlen(*ptr2) + 1);
		strcpy(*tmp, *res);
		strcat(*tmp, *ptr2);
		free(*res);
		*res = *tmp;
		free(*ptr2);
	}
}

void	process_single_quotes(t_shell *args, int *x, int *t, char **res)
{
	if (args->input[*x] == '\'')
	{
		(*x)++;
		(*t)++;
	}
	else
		append_char_to_res(res, args->input[(*x)++]);
}
