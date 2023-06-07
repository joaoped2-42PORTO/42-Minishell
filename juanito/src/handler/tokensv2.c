#include "../../includes/minishell.h"

/*

//1st sheet of code

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


//2nd sheet of code

    	ptr = (char *)malloc(2 * sizeof(char));
    	ptr[0] = args->input[x++];
    	ptr[1] = '\0';
        tmp = malloc(ft_strlen(res) + ft_strlen(ptr) + 1);
        strcpy(tmp, res);
        strcat(tmp, ptr);
        free(res);
        res = tmp;
        free(ptr);


//3rd sheet of code



*/






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
