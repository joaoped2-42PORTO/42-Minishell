/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/07 10:58:47 by joaoped2         ###   ########.fr       */
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

int isDoubleQuote(t_shell *args, int x)
{
    int p = 0;
    int t = 0;

    if (args->input[x] == '"')
    {
        x++;
        p++;
    }
    else if (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0')
        return (1);
    return (p % 2 != 0) && (t % 2 == 0);
}

int isSingleQuote(t_shell *args, int x)
{
    int p;
    int t;

    p = 0;
    t = 0;
    if (args->input[x] == '\'')
    {
        x++;
        t++;
    }
    return (t % 2 != 0) && (p % 2 == 0);
}

void handleDoubleQuote(t_shell *args, int *x, char **res)
{
    int     k;
    char    *str = NULL;
    char    *ptr2 = NULL;
    char    *tmp = NULL;

    k = 0;
    (*x)++;
    str = malloc((ft_strlen(args->input) + 1) * sizeof(char));
    while (args->input[*x] != ' ' && args->input[*x] != '\0' && checkisalpha(args, x))
        str[k++] = args->input[(*x)++];
    str[k] = '\0';
    ptr2 = print_env_var(args, str);
    if (ptr2)
    {
        tmp = malloc(ft_strlen(*res) + ft_strlen(ptr2) + 1);
        strcpy(tmp, *res);
        strcat(tmp, ptr2);
        free(*res);
        *res = tmp;
        free(ptr2);
    }
    free(str);
    k = 0;
}

void handleSingleQuote(t_shell *args, int *x, char **res)
{
    char    *ptr = NULL;
    char    *tmp = NULL;

    (*x)++;
    ptr = malloc(2 * sizeof(char));
    ptr[0] = args->input[(*x)++];
    ptr[1] = '\0';
    tmp = malloc(ft_strlen(*res) + ft_strlen(ptr) + 1);
    strcpy(tmp, *res);
    strcat(tmp, ptr);
    free(*res);
    *res = tmp;
    free(ptr);
}

void appendToString(char **res, char *str)
{
    char *tmp;

    tmp = malloc(ft_strlen(*res) + ft_strlen(str) + 1);
    strcpy(tmp, *res);
    strcat(tmp, str);
    free(*res);
    *res = tmp;
}

int isDollarSign(t_shell *args, int x)
{
    if (args->input[x] == '$' && args->input[x + 1] != ' '
	&& args->input[x + 1] != '\0' && args->input[x + 1] != '$')
		return (1);
	retunr (0);
}

void handleDollarSign(t_shell *args, int *x, char **res)
{
    int     k;
    char    *str;
    char    *ptr2;

    k = 0;
    str = malloc((ft_strlen(args->input) + 1) * sizeof(char));
    while (args->input[*x] != ' ' && args->input[*x] != '\0' && checkisalpha(args, x))
        str[k++] = args->input[(*x)++];
    str[k] = '\0';
    ptr2 = print_env_var(args, str);
    if (ptr2)
    {
        appendToString(res, ptr2);
        free(ptr2);
    }
    free(str);
}

void handleSpaceAndCharacter(t_shell *args, int *x, char **res)
{
    char *ptr;

    ptr = malloc(2 * sizeof(char));
    while (args->input[*x] == ' ' && args->input[*x + 1] == ' ')
        (*x)++;
    ptr[0] = args->input[(*x)++];
    ptr[1] = '\0';
    appendToString(res, ptr);
    free(ptr);
}

void handleRegularCharacter(t_shell *args, int *x, char **res)
{
    if (isDollarSign(args, *x))
        handleDollarSign(args, x, res);
    else
        handleSpaceAndCharacter(args, x, res);
}

char *checkbars(t_shell *args, int *i)
{
    char    *res;
    int     x;

    res = malloc(1);
    res[0] = '\0';
    x = *i;
    while (args->input[x])
    {
        if (valid_input(args) == 0)
        {
            printf("Error");
            break;
        }
        if (isDoubleQuote(args, x))
            handleDoubleQuote(args, &x, &res);
        else if (isSingleQuote(args, x))
            handleSingleQuote(args, &x, &res);
        else
            handleRegularCharacter(args, &x, &res);
    }
    return (res);
}

int	countvalues(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i] == ' ')
		i++;
	while (args->input[i] != ' ' && args->input[i])
		i++;
	while (args->input[i] == ' ')
		i++;
	return (i);
}
