/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/14 17:01:58 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "stdio.h"

void		img_new(t_core *cr)
{
	char	*img;

	if (!(img = mlx_new_image(cr->mlx, WIN_WIDTH, WIN_HIGHT)))
		err_ex(0);
	cr->image = mlx_get_data_addr(img, &cr->bpp, &(cr->linesize), &cr->endian);
	cr->img_ptr = img;
	//
	cr->addr = (int *)cr->image;
}

void		img_minimap_new(t_core *cr)
{
	char	*img;

	// printf("%d\n", cr->vs->mmsize);
	if (!(img = mlx_new_image(cr->mlx, cr->vs->mmsize, cr->vs->mmsize_y)))
		err_ex(0);
	cr->mm_image = mlx_get_data_addr(img, &cr->bpp, &(cr->linesize), &cr->endian);
	cr->mm_img_ptr = img;
}

void		pxl_put_wrap(void *td, int x, int y, int color)
{
	t_core		*cr;

	cr = (t_core *)(td);
	mlx_pixel_put(cr->mlx, cr->win, x, y, color);
}

void		img_pxl(void *td, int x, int y, int color)
{
	t_core		*cr;
	char	*p;

	cr = (t_core *)(td);
	if (x >= WIN_WIDTH - 1 || y >= WIN_HIGHT - 1 || \
		x < 0 || y < 0)
	{
		printf("OOB! ");
		return ;
	}
	// if (x >= cr->vs->mmsize - 1 || y >= cr->vs->mmsize_y - 1 || \
	// 	x < 0 || y < 0)
	// {
	// 	printf("OOB! ");
	// 	return ;
	// }
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
	p = cr->img_switcher;
	p += (x * 32 / 8) + (cr->linesize * y);
	*p++ = (color) & 0xFF;
	*p++ = (color >> 8) & 0xFF;
	*p = (color >> 16) & 0xFF;
}
