/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:45:12 by amakela           #+#    #+#             */
/*   Updated: 2024/10/26 18:26:57 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;

	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s))
		return (ft_strdup(&s[start]));
	if (len > ft_strlen(s) - start)
	{
		substr = malloc(sizeof(char) * len);
		if (!substr)
			return (NULL);
		ft_strlcpy(substr, &s[start], len);
		return (substr);
	}
	substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
