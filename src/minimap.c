/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/20 21:58:29 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

// static void	draw_point(t_win *cr)
// {
// 	cr->vs->x_offset = WIN_WIDTH - cr->vs->gridsize * (cr->x_len - 1);
// 	cr->vs->y_offset = 0;
// 	img_pxl(t_win *cr, int x, int y, int color)
// 	{
//
// 	}
// }

static void	draw_player(t_win *cr)
{
	cr->vs->vcolor = 0x00ff00;
	draw_rectangle(cr, cr->player.x * cr->vs->gridsize + cr->vs->x_offset - 3, \
		cr->player.y * cr->vs->gridsize + cr->vs->y_offset - 3, 6, 6);
	cr->vs->vcolor = 0xffffff;
	cr->vs->x_i = cr->player.x * cr->vs->gridsize + cr->vs->x_offset;
	cr->vs->y_i = cr->player.y * cr->vs->gridsize + cr->vs->y_offset;
	cr->vs->x2_i = cr->player.x * cr->vs->gridsize + cr->dir.x / cr->dir.len * 2 * cr->vs->gridsize + cr->vs->x_offset;
	cr->vs->y2_i = cr->player.y * cr->vs->gridsize + cr->dir.y / cr->dir.len * 2 * cr->vs->gridsize + cr->vs->y_offset;
	bresenham(cr);
}

static void	draw_walls(t_win *cr)
{
	int		xlen;
	int		ylen = cr->y_len;
	cr->vs->vcolor = 0x909497;
	while(ylen--)
	{
		xlen = cr->x_len;
		while(xlen--)
		{
			if (cr->tiles[ylen][xlen] != 0)
			draw_rectangle(cr, cr->vs->x_offset + xlen * cr->vs->gridsize, \
				cr->vs->y_offset + ylen * cr->vs->gridsize, cr->vs->gridsize, cr->vs->gridsize);
		}
	}
}

static void	draw_grid(t_win *cr)
{
	int		y_len;
	int		x_len;
	int		yp = cr->vs->gridsize;

	cr->vs->vcolor = 0x909497;
	y_len = cr->y_len;
	x_len = cr->x_len - 1;
	while (y_len--)
	{
		cr->vs->x_i = cr->vs->x_offset;
		cr->vs->y_i = cr->vs->y_offset + yp;
		cr->vs->x2_i = cr->vs->x_offset + cr->vs->gridsize * (cr->x_len - 1);
		cr->vs->y2_i = cr->vs->y_offset + yp;
		bresenham(cr);
		// printf("%d %d %d %d %d\n", yp, cr->vs->mmsize, cr->x_len, cr->y_len, cr->vs->gridsize);
		yp += cr->vs->gridsize;
	}
	yp = cr->vs->gridsize;
	while (x_len--)
	{
		cr->vs->x_i = cr->vs->x_offset + yp;
		cr->vs->y_i = cr->vs->y_offset;
		cr->vs->x2_i = cr->vs->x_offset + yp;
		cr->vs->y2_i = cr->vs->y_offset + cr->vs->gridsize * (cr->y_len - 1);
		bresenham(cr);
		// printf("%d %d %d %d %d\n", yp, cr->vs->mmsize, cr->x_len, cr->y_len, cr->vs->gridsize);
		yp += cr->vs->gridsize;
	}
}

void		draw_rectangle(t_win *cr, int x, int y, int xlen, int ylen)
{
	while (ylen--)
	{
		cr->vs->x_i = x;
		cr->vs->y_i = y + ylen;
		cr->vs->x2_i = x + xlen;
		cr->vs->y2_i = y + ylen;
		bresenham(cr);
	}
}

void		minimap(t_win *cr)
{
		draw_rectangle(cr, cr->vs->x_offset, cr->vs->y_offset, cr->vs->gridsize * (cr->x_len - 1), cr->vs->gridsize * (cr->y_len - 1));
		draw_grid(cr);
		draw_walls(cr);
		draw_player(cr);
}

void		minimap_init(t_win *cr)
{
	cr->vs->mmsize = 300;
	cr->vs->gridsize = cr->x_len > cr->y_len ? (double)cr->vs->mmsize / cr->x_len : (double)cr->vs->mmsize / cr->y_len;
	cr->vs->x_offset = WIN_WIDTH - cr->vs->gridsize * (cr->x_len);
	cr->vs->y_offset = 0;
	cr->vs->vcolor = 0x34495E;
}
