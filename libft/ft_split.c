/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:32:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/04 20:37:17 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
// #include <stdio.h>
// static unsigned int	how_many_split(char const *s, char c)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	unsigned int len =	ft_strlen(s);

// 	j = 0;
// 	i = 0;
// 	if (s[0] == '\0')
// 		return (0);
// 	if (ft_memchr(s, c, len) == NULL)
// 		return (1);
// 	while (s[i] == c)
// 		i++;
// 	while (i < ft_strlen(s))
// 	{
// 		if (s[i] == c)
// 		{
// 			j++;
// 			while (s[i] == c)
// 				i++;
// 		}
// 		i++;
// 	}
// 	if (s[len - 1] != c)
// 		return (j + 1);
// 	return (j);
// }

// static void	allocate_mem(char const *s, char c, char **ret)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	unsigned int	k;
// 	unsigned int len =	ft_strlen(s);

// 	k = 0;
// 	j = 0;
// 	i = 0;
// 	while (i < len)
// 	{
// 		j = 0;
// 		while (s[i] != c && s[i])
// 		{
// 			j++;
// 			i++;
// 		}
// 		if (j != 0)
// 		{
// 			ret[k] = (char *)malloc(sizeof(char) * (j + 1));
// 			if (!ret[k])
// 				return ;
// 			k++;
// 		}
// 		i++;
// 	}
// 	ret[k] = NULL;
// }

// static char	**implement_my_table(char const *s, char c, char **ret)
// {
// 	unsigned int	i;
// 	unsigned int	k;
// 	unsigned int	j;
// 	unsigned int len =	ft_strlen(s);

// 	k = 0;
// 	j = 0;
// 	i = 0;
// 	while (i < len)
// 	{
// 		if (s[i] != c)
// 		{
// 			j = 0;
// 			while (i < len && s[i] != c)
// 			{
// 				ret[k][j] = s[i];
// 				j++;
// 				i++;
// 			}
// 			ret[k][j] = '\0';
// 			k++;
// 		}
// 		i++;
// 	}
// 	return (ret);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char			**ret;

// 	if (!s)
// 		return (NULL);
// 	ret = (char **)malloc(sizeof(char *) * (how_many_split(s, c) + 1));
// 	if (!ret)
// 		return (NULL);
// 	allocate_mem(s, c, ret);
// 	implement_my_table(s, c, ret);
// 	return (ret);
//}
#include "libft.h"

static char **allocate_words(char const *s, char c, unsigned int len) {
    unsigned int word_count = 0;
    char **words;
    unsigned int i = 0;

    // Count words and allocate memory for words array
    while (i < len) {
        if (s[i] != c) {
            word_count++;
            while (i < len && s[i] != c) i++;
        } else {
            i++;
        }
    }
    words = (char **)malloc(sizeof(char *) * (word_count + 1));
    if (!words) return NULL;

    return words;
}

static void fill_words(char const *s, char c, char **words, unsigned int len) {
    unsigned int i = 0, j, word_index = 0, word_len;

    // Fill words array with each word
    while (i < len) {
        if (s[i] != c) {
            word_len = 0;
            j = i;
            while (i < len && s[i] != c) {
                word_len++;
                i++;
            }
            words[word_index] = (char *)malloc(sizeof(char) * (word_len + 1));
            if (!words[word_index]) {
                // Handle memory allocation failure
                // Free already allocated memory
                while (word_index > 0) {
                    free(words[--word_index]);
                }
                free(words);
                return;
            }
            ft_strlcpy(words[word_index], &s[j], word_len + 1);
            word_index++;
        } else {
            i++;
        }
    }
    words[word_index] = NULL; // Null-terminate the array of words
}


char **ft_split(char const *s, char c) {
    if (!s) return NULL;
    
    unsigned int len = ft_strlen(s);
	//printf("len = %u\n",len);
    char **words = allocate_words(s, c, len);
    if (!words) return NULL;

    fill_words(s, c, words, len);
    return words;
}
