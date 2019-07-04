/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:12:24 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/02 21:21:42 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"
#include <stdio.h>

static int		blender(int sc1, int sc2, double passed)
{
	return ((1 - passed) * sc1 + passed * sc2);
}

static int				getgrad(int color1, int color2, double passed)
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

static int		colors(t_core *cr, int i, double column)
{
	int tx;
	double	ty;
	double	x;
	int t;
	int c;


	// if (cr->wall == 'n')
	// 	cr->objcl = 0xff0000;
	// else if (cr->wall == 's')
	// 	cr->objcl = 0x00ff00;
	// else if (cr->wall == 'w')
	// 	cr->objcl = 0x0000ff;
	// else if (cr->wall == 'e')
	// 	cr->objcl = 0xffffff;
	// else if (cr->wall == ' ')
	// 	cr->objcl = 0x000000;

	if (cr->wall == 'n' || cr->wall == 's')
		x = cr->hitx;
	else
		x = cr->hity;
	tx = (x - (int)x) * TEXSIZE;
	ty = (double)TEXSIZE / column;
	t = i * ty;
	// if (1 / cr->dist > 1)
	// 	return (0xffffff);
	c = getgrad(getgrad(cr->textures[cr->wtexnum][tx + (t * TEXSIZE)], 0x7B241C, 1/(cr->dist + 1)), 0x000000, 1 - 1 / (cr->dist + 1));
		return (c);
		// return (cr->objcl);
}

int	floormap(double y, double distWall, t_core *cr)
{
	double distPlayer;
	double currentDist;
	int c;

    currentDist = (double)WIN_HIGHT / (2.0 * (double)y - (double)WIN_HIGHT);
	double weight = currentDist / distWall;

    double currentFloorX = weight * cr->hitx + (1.0 - weight) * cr->player.x;
    double currentFloorY = weight * cr->hity + (1.0 - weight) * cr->player.y;

    int floorTexX, floorTexY;
    floorTexX = (int)(currentFloorX * TEXSIZE) % TEXSIZE;
    floorTexY = (int)(currentFloorY * TEXSIZE) % TEXSIZE;

	// if (1 / currentDist > 1)
	// return (0xffffff);
	c = getgrad(getgrad(cr->textures[FLOORTEX][TEXSIZE * floorTexY + floorTexX], 0x7B241C, 1/(currentDist + 1)), 0x000000, 1 - 1 / (currentDist + 1));
	return (c);
}

void	draw_gui(t_core *cr)
{
	char	*string;

	string = ft_strjoin("COINS ", ft_itoa(cr->coins));
	mlx_string_put(cr->mlx, cr->win, WIN_WIDTH * 0.05, WIN_HIGHT * 0.95, 0xffffff, string);
}

void	draw(t_core *cr, int ray)
{
	int i;
	double	column;
	double	beg;

	i = 0;
	column = WIN_HIGHT / cr->dist;//Заменить на норм. расчет высоты столбцов
	beg = (WIN_HIGHT - column) / 2;
	// printf("%d    ", ray);
	// fflush(stdout);
	while (i < WIN_HIGHT)
	{
		if ((i > beg) && (i < WIN_HIGHT - beg) && i > 0)
		{
			// cr->wall = checker(cr, cr->hitx, cr->hity, cr->tiles);
			// cr->wall = 's';
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
		i++;
	}
}
