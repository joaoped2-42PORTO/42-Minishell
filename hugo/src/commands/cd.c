/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/19 16:36:34 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_cd(char *str)
{
	int		i;
	int		j;
	int		error;
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
	error = chdir(cd);
	if (error != 0)
		printf("Wrong directory!\n");
	free (cd);
}
