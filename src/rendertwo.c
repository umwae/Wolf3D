/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertwo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:37:59 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/06 18:22:29 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		blender(int sc1, int sc2, double passed)
{
	return ((1 - passed) * sc1 + passed * sc2);
}

int		getgrad(int color1, int color2, double passed)
{
	int		red;
	int		green;
	int		blue;

	if (color1 == color2)
		return (color1);
	red = blender((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, passed);
	green = blender((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, passed);
	blue = blender(color1 & 0xFF, color2 & 0xFF, passed);
	return ((red << 16) | (green << 8) | blue);
}
