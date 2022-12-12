/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:30 by kwang             #+#    #+#             */
/*   Updated: 2022/12/12 16:16:41 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
msg - Custom message to displat to standard error.
func_name - name of the function from which the function is called.
err_no - desired error number to display via perror.

Description:
Displays error message formatted according to
Error : <strerror(errno)>
<Custom message>
<Function which error_handler was called form>.
Exits the program after printing without freeing any dynamically allocated
memory.

Return value:
Returns nothing. 
*/
void	error_handler(const char *msg, const char *func_name, int err_no)
{
	if (errno == 0)
		errno = err_no;
	perror("Error");
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(func_name, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
