/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:12:24 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/06 18:55:19 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
#include <stdlib.h>

int		colors(t_core *cr, int i, double column)
{
	int		tx;
	double	ty;
	double	x;
	int		t;
	int		c;

	if (cr->wall == 'n' || cr->wall == 's')
		x = cr->hitx;
	else
		x = cr->hity;
	tx = (x - (int)x) * TEXSIZE;
	ty = (double)TEXSIZE / column;
	t = i * ty;
	c = getgrad(cr->textures[cr->wtexnum][tx + (t * TEXSIZE)],
		0, 1 - 1 / (cr->dist + 1));
	return (c);
}

int		floormap(double y, double dist, t_core *cr)
{
	t_flc ceil;

	ceil.c_dist = (double)WIN_HIGHT / (2.0 * (double)y - (double)WIN_HIGHT);
	ceil.wght = ceil.c_dist / dist;
	ceil.c_flrx = ceil.wght * cr->hitx + (1.0 - ceil.wght) * cr->player.x;
	ceil.c_flry = ceil.wght * cr->hity + (1.0 - ceil.wght) * cr->player.y;
	ceil.flrtx = (int)(ceil.c_flrx * TEXSIZE) % TEXSIZE;
	ceil.flrty = (int)(ceil.c_flry * TEXSIZE) % TEXSIZE;
	ceil.c = getgrad(getgrad(cr->textures[FLOORTEX][TEXSIZE *
		ceil.flrtx + ceil.flrty],
		0xffffff, 1 / (ceil.c_dist + 1)), 0x000000, 1 - 1 / (ceil.c_dist + 1));
	return (ceil.c);
}

int		seil(double y, double dist, t_core *cr)
{
	t_flc ceil;

	ceil.c_dist = (double)WIN_HIGHT / (2.0 * (double)y - (double)WIN_HIGHT);
	ceil.wght = ceil.c_dist / dist;
	ceil.c_flrx = ceil.wght * cr->hitx + (1.0 - ceil.wght) * cr->player.x;
	ceil.c_flry = ceil.wght * cr->hity + (1.0 - ceil.wght) * cr->player.y;
	ceil.flrtx = (int)(ceil.c_flrx * TEXSIZE) % TEXSIZE;
	ceil.flrty = (int)(ceil.c_flry * TEXSIZE) % TEXSIZE;
	ceil.c = getgrad(getgrad(cr->textures[CEILTEX][TEXSIZE *
		ceil.flrtx + ceil.flrty],
		0xffffff, 1 / (ceil.c_dist + 1)), 0x000000, 1 - 1 / (ceil.c_dist + 1));
	return (ceil.c);
}

void	draw_gui(t_core *cr)
{
	char	*string;

	string = ft_strjoin("COINS ", ft_itoa(cr->coins));
	mlx_string_put(cr->mlx, cr->win, 50, 950, 0xffffff, string);
	free(string);
}

void	draw(t_core *cr, int ray)
{
	int		i;
	double	column;
	double	beg;

	i = -1;
	column = WIN_HIGHT / cr->dist;
	beg = (WIN_HIGHT - column) / 2;
	while (++i < WIN_HIGHT)
	{
		if ((i > beg) && (i < WIN_HIGHT - beg) && i > 0)
		{
			if (cr->wall == 'e')
				cr->addr[ray + (i * WIN_WIDTH)] = colors(cr, i - beg, column);
			if (cr->wall == 'n')
				cr->addr[ray + (i * WIN_WIDTH)] = colors(cr, i - beg, column);
			if (cr->wall == 's')
				cr->addr[ray + (i * WIN_WIDTH)] = colors(cr, i - beg, column);
			if (cr->wall == 'w')
				cr->addr[ray + (i * WIN_WIDTH)] = colors(cr, i - beg, column);
		}
		else if (i > beg + column)
			cr->addr[ray + (i * WIN_WIDTH)] = floormap(i, cr->dist, cr);
		else
			cr->addr[ray + (i * WIN_WIDTH)] = seil(WIN_HIGHT - i, cr->dist, cr);
	}
}
