/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gstatus_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:25:56 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/05 12:00:45 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//General Errors (Typically used to indicate general errors or unspecified failures)
void	error1()
{
	g_status = 1;
}

//Misuse of Shell Built-ins (ndicates incorrect usage or misuse of shell built-in commands)
void	error2()
{
	g_status = 2;
}

//Command Not Executable(Indicates that the command or program was found but couldn't be executed due to permission issues or other reasons)
void	error126()
{
	g_status = 126;
}

//Command Not Found
//(Indicates that the command or program was not found or is not in the system's executable search path)
void	error127()
{
	g_status = 127;
}

//Program-specific Error Codes
//(Many programs and commands define their own specific error codes to indicate different conditions or errors.
//These codes can vary widely and depend on the specific program being executed.)
void	error128()
{
	g_status = 128;
}
