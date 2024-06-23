/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:38:27 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/13 15:31:39 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char c, char const *s2)
{
	char	*s;
	size_t	size1;
	size_t	size2;

	size1 = 0;
	while (s1[size1])
		size1++;
	size2 = 0;
	while (s2[size2])
		size2++;
	if (size1 && c)
		size1++;
	s = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (!s)
		return (NULL);
	s[size1 + size2] = '\0';
	while (size2--)
		s[size1 + size2] = s2[size2];
	if (size1 && c)
		s[--size1] = c;
	while (size1--)
		s[size1] = s1[size1];
	return (s);
}
