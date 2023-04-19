/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:56:53 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/19 16:59:14 by joaoped2         ###   ########.fr       */
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

void	gotofile(char *str)
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
	chdir(cd);
	free (cd);
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
				printf("%s\n", dir->d_name);
		}
		else
			return ;
	}
}

void	check_files_in_path(char *str)
{
	char	*dest;
	char	*save;
	char	path[1000];

	dest = str;
	save = getcwd(path, sizeof(path));
	gotofile(dest);
	normalls();
	chdir(save);
}
