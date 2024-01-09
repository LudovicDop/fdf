/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:32:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:13:59 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
