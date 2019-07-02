/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/02 21:19:56 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "wolf.h"

int		hooks(t_win *cr)
{
	visual(cr);
	//
	// mlx_hook(cr->win, 4, 1, mouse_press, cr);
	// mlx_hook(cr->win, 5, 1, mouse_release, cr);
	// mlx_hook(cr->win, 6, 1, mouse_move, cr);
	mlx_hook(cr->win, 2, 1, key_action, cr);
	mlx_loop(cr->mlx);
	return (0);
}

void		vector_init(t_win *cr)
{
	cr->player.x = 6.5; //Добавить функцию поиска свободной клетки
	cr->player.y = 3.5; //для помещения туда игрока
	cr->dir.x = 0.0;
	cr->dir.y = 1.0;
	cr->plane.x = 0.5;
	cr->plane.y = 0;
	cr->dir.len = cr->dir.x > cr->dir.y ? cr->dir.x : cr->dir.y;
	cr->plane.len = cr->plane.x > cr->plane.y ? cr->plane.x : cr->plane.y;
}

static void	tex_init(t_win *cr)
{
	int	x;
	int	y;

	cr->text = mlx_xpm_file_to_image(cr->mlx, "src/brick.xpm", &x, &y);
	cr->textures[0] = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	cr->text = mlx_xpm_file_to_image(cr->mlx, "src/wood.xpm", &x, &y);
	cr->textures[1] = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	cr->text = mlx_xpm_file_to_image(cr->mlx, "src/coin.xpm", &x, &y);
	cr->textures[2] = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
}

int		init(char *argv, t_win *cr)
{
	int		fd0;
	int		fd;
	int		x;
	int		y;

	fd0 = open(argv, O_RDONLY);
	fd = open(argv, O_RDONLY);
	if (!(cr->mlx = mlx_init()))
		err_ex(0);
	if (!(cr->win = mlx_new_window(cr->mlx, WIN_WIDTH, WIN_HIGHT, "Wolf3d")))
		err_ex(0);
	if (!(cr->vs = (t_visual *)malloc(sizeof(t_visual))))
		err_ex(0);
	cr->rotation = ROTATION;
	if (!(cr->sprOrder = (t_spr *)malloc(sizeof(t_spr) * SPRITESNUM)))
		err_ex(0);
	cr->spritesnum = SPRITESNUM;
	obj_init(cr);
	x = TEXSIZE;
	y = TEXSIZE;
	if (!(cr->textures = (int **)malloc(sizeof(int *) * TEXNUM)))
		err_ex(0);
	cr->text = mlx_xpm_file_to_image(cr->mlx, "src/brick.xpm", &x, &y);
	cr->addrtext = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	cr->text = mlx_xpm_file_to_image(cr->mlx, "src/wood.xpm", &x, &y);
	cr->floortext = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	//
	tex_init(cr);
	get_map(fd0, fd, cr);
	return (0);
}
