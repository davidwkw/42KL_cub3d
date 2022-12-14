/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:16 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 14:24:43 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
filename - string to be evaluated.

Description:
Locates first instance of '.' character starting from the end of the string
and returns the pointer to the first character after '.' is located. 

Return value:
Returns one character after '.' is located from the reverse end of the string. 
Returns NULL is '.' can't be found.
*/
static char	*get_file_ext(const char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ext == filename)
		return (NULL);
	return (ext + 1);
}

/*
Parameters:
filename - string to be evaluated.
ext_to_check - string of desired extension to check against.

Description:
Checks whether given filename contains extension given as the ext_to_check
parameter

Return value:
Returns nothing. Throws errors if extension is no found or does not match the
extension to match.
*/
void	validate_ext(const char *filename, const char *ext_to_check)
{
	size_t	ext_len;
	size_t	check_len;
	char	*ext;

	ext = get_file_ext(filename);
	if (!ext)
		error_handler("Absent file extension", "check_valid_ext", EIO);
	ext_len = ft_strlen(ext);
	check_len = ft_strlen(ext_to_check);
	if (ext_len != check_len || ft_strncmp(ext, ext_to_check, check_len))
		error_handler("Wrong file extension", "check_valid_ext", EIO);
}
