/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:32:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 17:31:35 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**allocate_words(char const *s, char c, unsigned int len)
{
	unsigned int	word_count;
	char			**words;
	unsigned int	i;

	word_count = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c)
		{
			word_count++;
			while (i < len && s[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	words = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	return (words);
}

static char	*create_word(const char *start, unsigned int word_len)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (word)
	{
		ft_strlcpy(word, start, word_len + 1);
	}
	return (word);
}

static void	free_words(char **words, unsigned int word_index)
{
	while (word_index > 0)
	{
		free(words[--word_index]);
	}
	free(words);
}

static void	fill_words(const char *s, char c, char **words, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	word_index;

	i = 0;
	j = 0;
	word_index = 0;
	while (i < len)
	{
		if (s[i] != c)
		{
			j = i;
			while (i < len && s[i] != c)
				i++;
			words[word_index] = create_word(&s[j], i - j);
			if (!words[word_index])
				return (free_words(words, word_index));
			word_index++;
		}
		else
			i++;
	}
	words[word_index] = NULL;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	len;
	char			**words;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	words = allocate_words(s, c, len);
	if (!words)
		return (NULL);
	fill_words(s, c, words, len);
	return (words);
}
