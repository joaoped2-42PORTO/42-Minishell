#include "../../includes/minishell.h"

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
    return (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0' && args->input[x + 1] != '$');
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
                while (args->input[x] != ' ' && args->input[x] != '\0' && checkisalpha(args, &x))
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
                while (args->input[x] != ' ' && args->input[x] != '\0' && checkisalpha(args, &x))
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

/*
void	checksplitcontent(t_shell *args)
{
	int		i;
	int		j;
	int		x;
	int		k;
	char	*res;

	res = NULL;
	i = 0;
	j = 1;
	k = 0;
	x = countvalues(args);
	if (x == 4)
	{
		printf("\n");
		return ;
	}
	else if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
	{
		while (args->split[j])
		{
			if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
			{
				i = 0;
				i++;
				while (args->split[j][i] == 'n')
					i++;
				if (args->split[j][i] == '\0')
				{
					j++;
					x += i;
					x += checkforspacesinstring(args, x);
					i = 0;
				}
			}
			else
			{
				printf("%s", args->split[j]);
				if (args->split[j + 1])
					printf(" ");
				j++;
			}
		}
		if (!args->split[j])
			return ;
		else
		{
			i = countvalues(args);
			res = checkbars(args, &i);
			while (res[k])
			{
				if (isdoublequote(args) != 0)
				{
					printf("%s", res);
					break ;
				}
				if (res[k] == ' ' && res[k + 1] == ' ')
					k++;
				else if (res[k] == ' ' && k == 0)
					k++;
				else
					write(1, &res[k++], 1);
			}
			k = 0;
			free(res);
			printf("\n");
			return ;
		}
	}
	else
	{
		i = countvalues(args);
		res = checkbars(args, &i);
		while (res[k])
		{
			if (isdoublequote(args) != 0)
			{
				printf("%s", res);
				break ;
			}
			if (res[k] == ' ' && res[k + 1] == ' ')
				k++;
			else if (res[k] == ' ' && k == 0)
				k++;
			else
				write(1, &res[k++], 1);
		}
		k = 0;
		free(res);
		printf("\n");
		return ;
	}
	res = checkbars(args, &x);
	while (res[k])
	{
		if (isdoublequote(args) != 0)
		{
			printf("%s", res);
			break ;
		}
		if (res[k] == ' ' && res[k + 1] == ' ')
			k++;
		else if (res[k] == ' ' && k == 0)
			k++;
		else
			write(1, &res[k++], 1);
	}
	k = 0;
	free(res);
}*/
