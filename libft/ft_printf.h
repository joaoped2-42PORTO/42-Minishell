/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:54:12 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/04 15:35:40 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		get_format(va_list args, const char str);
int		ft_prtstr(char *str);
int		ft_putchar(int c);
int		ft_nbsup16(unsigned long long nb);
void	ft_prtadr(unsigned long long ptr);
int		ft_putadr(unsigned long long ptr);
int		ft_prtnb(int nb);
int		ft_nbsup10(unsigned int nb);
char	*ft_uitoa(unsigned int n);
int		ft_prtunnb(unsigned int nb);
void	ft_puthex(unsigned int nb, const char str);
int		ft_printhex(unsigned int nb, const char str);
char	*ft_itoa(int n);
int		numlen(long n);

#endif
