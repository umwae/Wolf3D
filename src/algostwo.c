/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algostwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:13:31 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/18 18:45:28 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"

void	ddathree(t_core *cr, t_dda *dda, int i)
{
	if (i > MAXDIST)
	{
		dda->hit = 1;
		cr->dodraw = 0;
	}
	else
		cr->dodraw = 1;
	if (dda->sidedx < dda->sidedy)
	{
		dda->sidedx += dda->deltadx;
		dda->mapx += dda->stepx;
		dda->side = 0;
	}
	else
	{
		dda->sidedy += dda->deltady;
		dda->mapy += dda->stepy;
		dda->side = 1;
	}
	if ((cr->tiles[dda->mapy][dda->mapx]) > 0)
		dda->hit = 1;
}

void	ddafour(t_core *cr, t_dda *dda)
{
	if (dda->side == 0)
		cr->dist = (dda->mapx - cr->player.x +
			(1 - dda->stepx) / 2) / cr->castx;
	else
		cr->dist = (dda->mapy - cr->player.y +
			(1 - dda->stepy) / 2) / cr->casty;
	cr->mdist[cr->rcurr] = cr->dist;
	if (dda->side == 0)
		dda->wx = cr->player.y + cr->dist * cr->casty;
	else
		dda->wx = cr->player.x + cr->dist * cr->castx;
}

void	ddainit(t_core *cr, t_dda *dda)
{
	dda->mapx = (int)cr->player.x;
	dda->mapy = (int)cr->player.y;
	dda->deltadx = sqrt(1 + (cr->casty * cr->casty) / (cr->castx * cr->castx));
	dda->deltady = sqrt(1 + (cr->castx * cr->castx) / (cr->casty * cr->casty));
	dda->hit = 0;
}
