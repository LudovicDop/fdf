/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:54:22 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:35:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	string_size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s2)
	{
		s2 = ft_calloc(1, 1);
	}
	string_size = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (string_size + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		ret[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (free(s1), s1 = NULL, free(s2), s2 = NULL, ret);
}
