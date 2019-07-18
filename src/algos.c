/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:12:33 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/18 18:09:44 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void		bresenham(t_core *cr)
{
	int	sx;
	int	err;
	int	sy;
	int	e2;

	cr->vs->dx = abs(cr->vs->x2_i - cr->vs->x_i);
	cr->vs->dy = abs(cr->vs->y2_i - cr->vs->y_i);
	sx = cr->vs->x_i < cr->vs->x2_i ? 1 : -1;
	sy = cr->vs->y_i < cr->vs->y2_i ? 1 : -1;
	err = (cr->vs->dx > cr->vs->dy ? cr->vs->dx : -cr->vs->dy) / 2;
	while (cr->vs->x_i != cr->vs->x2_i || cr->vs->y_i != cr->vs->y2_i)
	{
		(*cr->print_func)((void *)cr, cr->vs->x_i, cr->vs->y_i, cr->vs->vcolor);
		e2 = err;
		if (e2 > -cr->vs->dx)
		{
			err -= cr->vs->dy;
			cr->vs->x_i += sx;
		}
		if (e2 < cr->vs->dy)
		{
			err += cr->vs->dx;
			cr->vs->y_i += sy;
		}
	}
}

void		ddaonepart(t_core *cr, t_dda *dda)
{
	cr->hitx = dda->mapx;
	cr->hity = dda->wx;
	cr->wall = 'w';
	cr->wtexnum = 1;
}

void		ddaone(t_core *cr, t_dda *dda)
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

void		ddatwo(t_core *cr, t_dda *dda)
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

void		dda2(t_core *cr)
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
