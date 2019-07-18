/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:48:33 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "wolf.h"

void		vector_init(t_core *cr)
{
	cr->player.x = PLAYER_START_X;
	cr->player.y = PLAYER_START_Y;
	cr->dir.x = 0.0;
	cr->dir.y = 1.0;
	cr->plane.x = 0.5;
	cr->plane.y = 0;
	cr->dir.len = sqrt(pow(cr->dir.x, 2) + pow(cr->dir.y, 2));
	cr->plane.len = sqrt(pow(cr->plane.x, 2) + pow(cr->plane.y, 2));
}

static void	tex_init(t_core *cr)
{
	int		x;
	int		y;
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	if (!(cr->textures = (int **)malloc(sizeof(int *) * TEXNUM)))
		err_ex(0);
	if (!(cr->textrash = (int **)malloc(sizeof(int *) * TEXNUM)))
		err_ex(0);
	while (i <= TEXNUM)
	{
		tmp = ft_itoa(i);
		tmp2 = ft_strjoin("./textures/texture", tmp);
		free(tmp);
		tmp = ft_strjoin((tmp2), ".xpm");
		free(tmp2);
		cr->textrash[i] = mlx_xpm_file_to_image(cr->mlx, tmp, &x, &y);
		free(tmp);
		cr->textures[i] = (int *)mlx_get_data_addr(cr->textrash[i], \
			&cr->bpp, &(cr->linesize), &(cr->endian));
		i++;
	}
}

void		init(char *argv, t_core *cr)
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
	if (!(cr->objarr = malloc(sizeof(t_obj) * SPRITESNUM)))
		err_ex(0);
	cr->spritesnum = SPRITESNUM;
	tex_init(cr);
	get_map(fd0, fd, cr);
	vector_init(cr);
	check_borders(cr);
	minimap_init(cr);
	img_new(cr);
	visual(cr);
}
