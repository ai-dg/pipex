/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:13:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/15 15:02:26 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(s));
	while (*(str + i))
	{
		if (c % 256 == *(str + i))
			return (str + i);
		i++;
	}
	return (NULL);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	total_len;
	size_t	i;
	size_t	j;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	total_len = len_dst + len_src + 1;
	i = len_dst;
	j = 0;
	size = size + len_dst;
	while (i < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (total_len);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;
	int		i;

	len = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
