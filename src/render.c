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
	c = cr->textures[cr->wtexnum][tx + (t * TEXSIZE)];
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

   c = cr->textures[FLOORTEX][TEXSIZE * floorTexY + floorTexX];
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
