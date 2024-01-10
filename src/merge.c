/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:32:11 by ldoppler          #+#    #+#             */
/*   Updated: 2024/01/10 18:25:57 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	merge_rgba(unsigned int color1, unsigned int color2)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = (((color1 >> 24) & 0xFF) + ((color2 >> 24) & 0xFF)) / 2;
	g = (((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF)) / 2;
	b = (((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF)) / 2;
	a = ((color1 & 0xFF) + (color2 & 0xFF)) / 2;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
