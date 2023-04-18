/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/18 16:18:04 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

void	do_cd(char *str)
{
	int	i;
	int	j;
	int	error;
	char	*cd;

	i = 3;
	j = 0;
	error = 0;
	while (str[i])
		i++;
	cd = malloc(i + 1 * sizeof(char));
	i = 3;
	while (str[i])
		cd[j++] = str[i++];
	cd[j] = '\0';
	//printf("%s\n", cd);
	error = chdir(cd);
	if (error != 0)
		printf("Wrong directory!\n");
	free (cd);
}

void	check_pwd(void)
{
	char	path[1000];
	getcwd(path, sizeof(path));
	if (path[0] == '\0')
		printf("Something went wrong!\n");
	else
		printf("%s\n", path);
}

void	check_files_in_path(void)
{
	DIR	*d;
	struct dirent	*dir;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
				continue;
			else
				printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
}


int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("👾Phylothinkers👾> ");
		if (input && *input)
			add_history(input);
		if (!ft_strncmp(input, "pwd", 3))
			check_pwd();
		else if (!ft_strncmp(input, "cd ", 3))
			do_cd(input);
		else if (!ft_strncmp(input, "cd", 2))
		{
			chdir("/nfs/homes/");
			printf("OI!\n");
		}
		else if (!ft_strncmp(input, "exit", 4))
			return (0);
		else if (!ft_strncmp(input, "ls", 2))
			check_files_in_path();
		else
			printf("command not found: %s\n", input);
		free(input);
	}
	return (0);
}
