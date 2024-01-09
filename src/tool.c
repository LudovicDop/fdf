/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:08:05 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/09 16:24:51 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"

#include <stdlib.h>

void free_char_array(char **array) {
    if (array == NULL) {
        return; // Handle null pointer
    }

    int i = 0;
    while (array[i] != NULL) {
		printf("array[%d] = free\n",i);
        free(array[i]); // Free each string
        i++;
    }

    free(array); // Finally, free the array of pointers itself
}

