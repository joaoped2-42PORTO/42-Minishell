/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:28:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 14:05:26 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_pwd()
{
	char	path[1000];

	getcwd(path, sizeof(path));
	if (path[0] == '\0')
		printf("Something went wrong!\n");
	else
		printf("%s\n", path);
}
