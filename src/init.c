/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 21:28:50 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "wolf.h"

void		vector_init(t_core *cr)
{
	cr->player.x = 6.5; //Добавить функцию поиска свободной клетки
	cr->player.y = 3.5; //для помещения туда игрока
	cr->dir.x = 0.0;
	cr->dir.y = 1.0;
	cr->plane.x = 0.5;
	cr->plane.y = 0;
	cr->dir.len = sqrt(pow(cr->dir.x, 2) + pow(cr->dir.y, 2));
	cr->plane.len = sqrt(pow(cr->plane.x, 2) + pow(cr->plane.y, 2));
}

static void	tex_init(t_core *cr)
{
	int	x;
	int	y;
	int	i = 1;

	// cr->text = mlx_xpm_file_to_image(cr->mlx, "src/wall1.xpm", &x, &y);
	while (i <= TEXNUM)
	{
		cr->text = mlx_xpm_file_to_image(cr->mlx, ft_strjoin(ft_strjoin("./textures/texture", ft_itoa(i)), ".xpm"), &x, &y);
		//Это тоже надо бы сохранять в массив чтобы не выглядело как утечка
		cr->textures[i++] = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	}
}

int		init(char *argv, t_core *cr)
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
	if (!(cr->vs = (t_minimap *)malloc(sizeof(t_minimap))))
		err_ex(0);
	cr->rotation = ROTATION;
	if (!(cr->objarr = (t_obj *)malloc(sizeof(t_obj) * SPRITESNUM)))
		err_ex(0);
	cr->spritesnum = SPRITESNUM;
	// obj_init(cr);
	x = TEXSIZE;
	y = TEXSIZE;
	if (!(cr->textures = (int **)malloc(sizeof(int *) * TEXNUM)))
		err_ex(0);
	// cr->text = mlx_xpm_file_to_image(cr->mlx, "src/texture1.xpm", &x, &y);
	// cr->addrtext = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	// cr->text = mlx_xpm_file_to_image(cr->mlx, "src/texture2.xpm", &x, &y);
	// cr->floortext = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
	//
	tex_init(cr);
	get_map(fd0, fd, cr);
	return (0);
}
