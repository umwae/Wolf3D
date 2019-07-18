/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:49:37 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_walls(t_core *cr)
{
	int		xlen;
	int		ylen;
	t_coo	xy;

	ylen = cr->map_h;
	cr->vs->vcolor = 0x909497;
	while (ylen--)
	{
		xlen = cr->map_w;
		while (xlen--)
		{
			if (cr->tiles[ylen][xlen] != 0)
			{
				xy.x = xlen * cr->vs->gridsize;
				xy.y = ylen * cr->vs->gridsize;
				draw_rectangle(cr, xy, cr->vs->gridsize, cr->vs->gridsize);
			}
		}
	}
}

static void		draw_grid(t_core *cr, int map_w, int map_h)
{
	int		yp;

	yp = cr->vs->gridsize;
	cr->vs->vcolor = 0x909497;
	while (map_h--)
	{
		cr->vs->x_i = 0;
		cr->vs->y_i = yp - 1;
		cr->vs->x2_i = cr->vs->gridsize * (cr->map_w) - 1;
		cr->vs->y2_i = yp - 1;
		bresenham(cr);
		yp += cr->vs->gridsize;
	}
	yp = cr->vs->gridsize;
	while (map_w--)
	{
		cr->vs->x_i = yp - 1;
		cr->vs->y_i = 0;
		cr->vs->x2_i = yp - 1;
		cr->vs->y2_i = cr->vs->gridsize * (cr->map_h) - 1;
		bresenham(cr);
		yp += cr->vs->gridsize;
	}
}

void			draw_rectangle(t_core *cr, t_coo xy, int xlen, int ylen)
{
	while (ylen--)
	{
		cr->vs->x_i = xy.x;
		cr->vs->y_i = xy.y + ylen;
		cr->vs->x2_i = xy.x + xlen;
		cr->vs->y2_i = xy.y + ylen;
		bresenham(cr);
	}
}

void			minimap(t_core *cr)
{
	mlx_put_image_to_window(cr->mlx, cr->win, \
		cr->mm_img_ptr, cr->vs->x_offset, cr->vs->y_offset);
	cr->print_func = &pxl_put_wrap;
	cr->img_switcher = cr->mm_image;
	draw_objects(cr);
	draw_player(cr);
}

void			minimap_init(t_core *cr)
{
	t_coo	xy;

	cr->vs->mmsize = MMSIZE;
	cr->vs->gridsize = cr->map_w > cr->map_h ? \
		(double)cr->vs->mmsize / cr->map_w : (double)cr->vs->mmsize / cr->map_h;
	cr->vs->mmsize_y = cr->vs->gridsize * cr->map_h;
	cr->vs->x_offset = WIN_WIDTH - cr->vs->gridsize * (cr->map_w);
	cr->vs->y_offset = 0;
	cr->vs->vcolor = MM_COLOR;
	img_minimap_new(cr);
	cr->print_func = &img_pxl;
	cr->img_switcher = cr->mm_image;
	xy.x = 0;
	xy.y = 0;
	draw_rectangle(cr, xy, cr->vs->gridsize * (cr->map_w) - 1, \
		cr->vs->gridsize * (cr->map_h) - 1);
	draw_grid(cr, cr->map_w, cr->map_h);
	draw_walls(cr);
}
