/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:52:28 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			iterate_y(t_core *cr, int y, int x)
{
	while (y < cr->map_h)
	{
		if (cr->tiles[y][x] == 0)
			err_ex(1);
		y++;
	}
}

static void			iterate_x(t_core *cr, int y, int x)
{
	while (x < cr->map_w)
	{
		if (cr->tiles[y][x] == 0)
			err_ex(1);
		x++;
	}
}

void				check_borders(t_core *cr)
{
	if (cr->map_h < 3 && cr->map_w < 3)
		err_ex(1);
	iterate_x(cr, 0, 0);
	iterate_x(cr, cr->map_h - 1, 0);
	iterate_y(cr, 0, 0);
	iterate_y(cr, 0, cr->map_w - 1);
	if (cr->tiles[(int)cr->player.y][(int)cr->player.x] != 0)
		err_ex(4);
}
