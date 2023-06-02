/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/31 17:06:28 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *checkbars(t_shell *args, int *i)
{
    int x;
    int p;
    int k;
    int t;
    char *str = NULL;
    char *ptr = NULL;
    char *ptr2 = NULL;
	char *tmp = NULL;
    char *res;

	res = malloc(1);
	res[0] = '\0';
	x = *i;
	p = 0;
	k = 0;
    t = 0;
    while (args->input[x])
    {
        if (valid_input(args) == 0)
        {
            printf("Error");
            break;
        }

        if ((args->input[x] == '"' || p % 2 != 0) && t % 2 == 0)
        {
            if (args->input[x] == '"')
            {
                x++;
                p++;
            }
            else if (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0')
            {
                x++;
                str = (char *)malloc((ft_strlen(args->input) + 1) * sizeof(char));
                while (args->input[x] != ' ' && args->input[x] != '\0' && args->input[x] != '$' && args->input[x] != '"' && args->input[x] != '\'')
                    str[k++] = args->input[x++];
                str[k] = '\0';
                ptr2 = print_env_var(args, str);
                if (ptr2)
                {
                    tmp = malloc(ft_strlen(res) + ft_strlen(ptr2) + 1);
                    strcpy(tmp, res);
                    strcat(tmp, ptr2);
                    free(res);
                    res = tmp;
                    free(ptr2);
                }
                free(str);
                k = 0;
            }
            else
            {
                ptr = (char *)malloc(2 * sizeof(char));
                ptr[0] = args->input[x++];
                ptr[1] = '\0';
                tmp = malloc(ft_strlen(res) + ft_strlen(ptr) + 1);
                strcpy(tmp, res);
                strcat(tmp, ptr);
                free(res);
                res = tmp;
                free(ptr);
            }
        }
        else if ((args->input[x] == '\'' || t % 2 != 0) && p % 2 == 0)
        {
            if (args->input[x] == '\'')
            {
                x++;
                t++;
            }
            else
            {
                ptr = (char *)malloc(2 * sizeof(char));
                ptr[0] = args->input[x++];
                ptr[1] = '\0';
                tmp = malloc(ft_strlen(res) + ft_strlen(ptr) + 1);
                strcpy(tmp, res);
                strcat(tmp, ptr);
                free(res);
                res = tmp;
                free(ptr);
            }
        }
        else if (p % 2 == 0)
        {
            if (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0' && args->input[x + 1] != '$')
            {
                x++;
                str = (char *)malloc((ft_strlen(args->input) + 1) * sizeof(char));
                while (args->input[x] != ' ' && args->input[x] != '\0' && args->input[x] != '$' && args->input[x] != '"')
                    str[k++] = args->input[x++];
                str[k] = '\0';
                ptr2 = print_env_var(args, str);
                if (ptr2)
                {
                    tmp = malloc(ft_strlen(res) + ft_strlen(ptr2) + 1);
                    strcpy(tmp, res);
                    strcat(tmp, ptr2);
                    free(res);
                    res = tmp;
                    free(ptr2);
                }
                free(str);
                k = 0;
            }
            else
            {
                while (args->input[x] == ' ' && args->input[x + 1] == ' ')
                    x++;
                ptr = (char *)malloc(2 * sizeof(char));
                ptr[0] = args->input[x++];
                ptr[1] = '\0';
                tmp = malloc(ft_strlen(res) + ft_strlen(ptr) + 1);
                strcpy(tmp, res);
                strcat(tmp, ptr);
                free(res);
                res = tmp;
                free(ptr);
            }
        }
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
