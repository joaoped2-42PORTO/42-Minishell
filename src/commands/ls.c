/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:53 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/20 11:09:04 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function: DIR *opendir (const char *dirname)
The opendir function opens and returns a directory stream for
reading the directory whose file name is dirname. The stream has type DIR *.

DIR: A type representing a directory stream.

It also defines the structure dirent which includes the following members:
	ino_t  d_ino       file serial number
	char   d_name[]    name of entry
The type ino_t is defined as described in <sys/types.h>.
The character array d_name is of unspecified size, but the number of bytes
preceding the terminating null byte will not exceed {NAME_MAX}.
The following are declared as functions and may also be defined as macros.
Function prototypes must be provided for use with an ISO C compiler.
	int            closedir(DIR *);
	DIR           *opendir(const char *);
	struct dirent *readdir(DIR *);
	int            readdir_r(DIR *, struct dirent *, struct dirent **);
	void           rewinddir(DIR *);
	void           seekdir(DIR *, long int);
	long int       telldir(DIR *);
*/

int	gotofile(char *str)
{
	int		i;
	int		j;
	char	*cd;

	i = 3;
	j = 0;
	while (str[i])
		i++;
	cd = malloc(i + 1 * sizeof(char));
	i = 3;
	while (str[i])
		cd[j++] = str[i++];
	cd[j] = '\0';
	if (chdir(cd) == 0)
		return (1);
	else
	{
		printf("ls: impossível aceder a %s: Ficheiro ou pasta inexistente\n", cd);
		free (cd);
		return (0);
	}
}

void	normalls(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	while (1)
	{
		dir = readdir(d);
		if (dir)
		{
			if (!ft_strcmp(dir->d_name, "."))
				continue ;
			else
				printf("%s ", dir->d_name);
		}
		else
		{
			printf("\n");
			return ;
		}
	}
}

char	*checkspaces(char *str)
{
	int	i;
	int j;
	int k;
	int z;
	char *dest;

	i = 0;
	j = 0;
	k = 0;
	z = 0;
	dest = malloc(i + 1 * sizeof(char));
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			j = 1;
		else if (str[i] == '\\')
			z = 1;
		else if (str[i] != ' ' && str[i] != '\t')
		{
			if (j)
			{
				dest[k] = ' ';
				k++;
				j = 0;
			}
			dest[k++] = str[i];
		}
		i++;
	}
	dest[k] = '\0';
	return (dest);
}

void	check_files_in_path(char *str)
{
	char	*save;
	char	path[1000];
	char	*dest;
	int	i = 0;

	save = getcwd(path, sizeof(path));
	dest = checkspaces(str);
	while (dest[i])
		i++;
	if (i == 2)
		normalls();
	else
	{
		if (gotofile(dest) == 1)
			normalls();
		chdir(save);
	}
}
