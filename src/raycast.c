/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:51:55 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	make_cast(t_core *cr)
{
	double camera;

	cr->rcurr = 1;
	while (cr->rcurr < WIN_WIDTH)
	{
		camera = 2 * cr->rcurr / (double)WIN_WIDTH - 1;
		cr->castx = cr->dir.x + cr->plane.x * camera;
		cr->casty = cr->dir.y + cr->plane.y * camera;
		dda2(cr);
		draw(cr, WIN_WIDTH - cr->rcurr);
		cr->rcurr++;
	}
}
