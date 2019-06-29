/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/21 18:14:45 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

// void	calc_line(t_win *cr)
// {
// 	// // printf("%f\n", cr->dist);
// 	// cr->vs->y2_i = WIN_HIGHT / 2 + WIN_HIGHT / 4 / cr->dist;
// 	// cr->vs->x_i = WIN_WIDTH - cr->rcurr;
// 	// cr->vs->x2_i = cr->vs->x_i;
// 	// cr->vs->y_i = WIN_HIGHT / 2 - WIN_HIGHT / 4 / cr->dist;
// 	// bresenham(cr);
// 	draw(cr, WIN_WIDTH - cr->rcurr);
// 	cr->dist = 0;
// }

void			visual(t_win *cr)
{
	mlx_destroy_image(cr->mlx, cr->img_ptr);
	img_new(cr);
	//
	// mlx_put_image_to_window(cr->mlx, cr->win, cr->img_ptr, 0, 0);
	// mlx_put_image_to_window(cr->mlx, cr->win, cr->text, 0, 0);
	// return ;
	//
	make_cast(cr);
	// mlx_put_image_to_window(cr->mlx, cr->win, cr->text, 0, 0);
	// return ;
	//
	minimap_init(cr);
	minimap(cr);
	//
	printf("px: %f, py: %f, dirx: %f, diry: %f\n", cr->player.x, cr->player.y, cr->dir.x, cr->dir.y);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->img_ptr, 0, 0);
}
