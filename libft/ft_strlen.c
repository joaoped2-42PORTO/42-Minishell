/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:39:34 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:27:20 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*int main()
{
	char	str[] = "Queres saber o meu tamanho?";
	char	str1[] = "O meu tambem?";
	char	str2[] = "Ja nao achas que estas curioso/a demais?";

	ft_putnbr_fd(ft_strlen(str), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_strlen(str1), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_strlen(str2), 1);
	ft_putchar_fd('\n', 1);
}*/
