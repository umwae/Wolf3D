/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/20 21:51:16 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "stdio.h"

void		img_new(t_win *cr)
{
	char	*img;

	if (!(img = mlx_new_image(cr->mlx, WIN_WIDTH, WIN_HIGHT)))
		err_ex(0);
	cr->image = mlx_get_data_addr(img, &cr->bpp, &(cr->linesize), &cr->endian);
	cr->img_ptr = img;
	//
	cr->addr = (int *)cr->image;
}

void		img_pxl(t_win *cr, int x, int y, int color)
{
	char	*p;

	if (x >= WIN_WIDTH - 1 || y >= WIN_HIGHT - 1 || \
		x < 0 || y < 0)
	{
		// printf("OOB! ");
		return ;
	}
	// if (x > WIN_WIDTH)
	// {
	// 	printf("RIGHT! %d ", x);
	// 	return ;
	// }
	// if (x < 0)
	// {
	// 	printf("LEFT! ");
	// 	return ;
	// }
	// if (y >= WIN_HIGHT)
	// {
	// 	printf("TOP! ");
	// 	return ;
	// }
	// if (y < 0)
	// {
	// 	printf("BOT! ");
	// 	return ;
	// }
	p = cr->image;
	p += (x * 32 / 8) + (cr->linesize * y);
	*p++ = (color) & 0xFF;
	*p++ = (color >> 8) & 0xFF;
	*p = (color >> 16) & 0xFF;
}
