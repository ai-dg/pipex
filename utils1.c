/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/15 15:06:00 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_malloc_split(char **dest)
{
	int	i;

	if (dest == NULL)
		return ;
	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

static size_t	count_strings(const char *str, char c)
{
	size_t	nbr_mots;

	nbr_mots = 0;
	while (*str != '\0')
	{
		if (*str != c)
		{
			while (*str != '\0' && *str != c)
				str++;
			nbr_mots++;
		}
		else
		{
			str++;
		}
	}
	return (nbr_mots);
}

static const char	*ft_replace(char **dest, const char *src, char c)
{
	size_t	len;
	size_t	i;

	while (*src == c)
		src++;
	len = 0;
	while (src[len] != '\0' && src[len] != c)
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (*dest == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	if (src[len] != '\0')
		src += len + 1;
	else
		src += len;
	return (src);
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	size_t	nbr_mots;
	size_t	i;

	if (!s)
		return (NULL);
	nbr_mots = count_strings(s, c);
	dest = (char **)malloc(sizeof(char *) * (nbr_mots + 1));
	if (dest == NULL)
		return (NULL);
	dest[nbr_mots] = NULL;
	i = 0;
	while (i < nbr_mots)
	{
		s = ft_replace(dest + i, s, c);
		if (s == NULL)
		{
			i++;
			while (i-- > 0)
				free(dest[i]);
			return (free(dest), NULL);
		}
		i++;
	}
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	i = 0;
	while (s11[i] && s22[i] && s11[i] == s22[i] && i < n - 1)
	{
		i++;
	}
	return (s11[i] - s22[i]);
}
