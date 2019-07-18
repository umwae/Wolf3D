/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:49:55 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_objects(t_core *cr)
{
	int		i;
	t_coo	xy;

	i = 0;
	cr->vs->vcolor = 0xffffff;
	while (i < cr->spritesnum)
	{
		xy.x = cr->objarr[i].x * cr->vs->gridsize + cr->vs->x_offset - 3;
		xy.y = cr->objarr[i].y * cr->vs->gridsize + cr->vs->y_offset - 3;
		draw_rectangle(cr, xy,
					cr->vs->gridsize / 3, cr->vs->gridsize / 3);
		i++;
	}
}

void	draw_player(t_core *cr)
{
	int		pp;
	t_coo	xy;

	pp = cr->vs->gridsize / 3;
	cr->vs->vcolor = 0xffffff;
	cr->vs->x_i = cr->player.x * cr->vs->gridsize + cr->vs->x_offset;
	cr->vs->y_i = cr->player.y * cr->vs->gridsize + cr->vs->y_offset;
	cr->vs->x2_i = cr->player.x * cr->vs->gridsize + cr->dir.x /
		cr->dir.len * 2 * cr->vs->gridsize + cr->vs->x_offset;
	cr->vs->y2_i = cr->player.y * cr->vs->gridsize + cr->dir.y /
		cr->dir.len * 2 * cr->vs->gridsize + cr->vs->y_offset;
	bresenham(cr);
	cr->vs->vcolor = 0x00ff00;
	xy.x = cr->player.x * cr->vs->gridsize + cr->vs->x_offset - pp / 2;
	xy.y = cr->player.y * cr->vs->gridsize + cr->vs->y_offset - pp / 2;
	draw_rectangle(cr, xy, pp, pp);
}
