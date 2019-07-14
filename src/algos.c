/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:12:33 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/14 17:05:09 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void		bresenham(t_core *cr)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int dx;
	int sx;

	x0 = cr->vs->x_i;
	y0 = cr->vs->y_i;
	x1 = cr->vs->x2_i;
	y1 = cr->vs->y2_i;
	dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
 	while (x0 != x1 || y0 != y1)
	{
    	(*(cr->print_func))((void *)cr, x0, y0, cr->vs->vcolor);
    	// if (x0 == x1 && y0 == y1)
		// 	break;
    	e2 = err;
    	if (e2 >- dx)
		{
			err -= dy;
			x0 += sx;
		}
    	if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
  	}
}

void	ddaonepart(t_core *cr, t_dda *dda)
{
	cr->hitx = dda->mapx;
	cr->hity = dda->wx;
	cr->wall = 'w';
	cr->wtexnum = 1;
}

void	ddaone(t_core *cr, t_dda *dda)
{
	if (dda->side == 0 && cr->castx > 0)
	{
		ddaonepart(cr, dda);
	}
	else if (dda->side == 0 && cr->castx < 0)
	{
		cr->hitx = dda->mapx + 1.0;
		cr->hity = dda->wx;
		cr->wall = 'e';
		cr->wtexnum = 6;
	}
	else if (dda->side == 1 && cr->casty > 0)
	{
		cr->hitx = dda->wx;
		cr->hity = dda->mapy;
		cr->wall = 'n';
		cr->wtexnum = 4;
	}
	else
	{
		cr->hitx = dda->wx;
		cr->hity = dda->mapy + 1.0;
		cr->wall = 's';
		cr->wtexnum = 7;
	}
}

void	ddatwo(t_core *cr, t_dda *dda)
{
	if (cr->castx < 0)
	{
		dda->stepx = -1;
		dda->sidedx = (cr->player.x - dda->mapx) * dda->deltadx;
	}
	else
	{
		dda->stepx = 1;
		dda->sidedx = (dda->mapx + 1.0 - cr->player.x) * dda->deltadx;
	}
	if (cr->casty < 0)
	{
		dda->stepy = -1;
		dda->sidedy = (cr->player.y - dda->mapy) * dda->deltady;
	}
	else
	{
		dda->stepy = 1;
		dda->sidedy = (dda->mapy + 1.0 - cr->player.y) * dda->deltady;
	}
}

void	dda2(t_core *cr)
{
	t_dda	*dda;
	int		i;

	dda = malloc(sizeof(t_dda));
	ddainit(cr, dda);
	i = 0;
	ddatwo(cr, dda);
	while (dda->hit == 0)
	{
		ddathree(cr, dda, i);
		i++;
	}
	ddafour(cr, dda);
	ddaone(cr, dda);
	if (cr->hitx > cr->map_w)
		cr->hitx = cr->map_w - 1;
	if (cr->hity > cr->map_h)
		cr->hity = cr->map_h - 1;
	if (cr->hitx < 1)
		cr->hitx = 1;
	if (cr->hity < 1)
		cr->hity = 1;
	free(dda);
}
