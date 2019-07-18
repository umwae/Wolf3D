/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:10 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:51:29 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

static void		map_line(char *line, int j, t_core *cr)
{
	char			**arr;
	int				i;
	int				line_len_ct;

	i = 0;
	arr = ft_strsplit(line, ' ');
	line_len_ct = cr->map_w;
	while (line_len_ct--)
	{
		if (!arr[i])
			err_ex(1);
		cr->tiles[j][cr->map_w - line_len_ct - 1] = ft_atoi(arr[i]);
		i++;
	}
	ft_arrfree(&arr, cr->map_w);
}

void			get_mappart(t_core *cr, int fd, char *line, int yc)
{
	cr->map_h = yc;
	if (!(cr->tiles = (int **)malloc(sizeof(int *) * cr->map_h)))
		err_ex(0);
	yc = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == 0 || line[0] == '\n')
		{
			free(line);
			break ;
		}
		if (!((cr->tiles)[yc] = (int *)malloc(sizeof(int) * cr->map_w)))
			err_ex(0);
		map_line(line, yc, cr);
		yc++;
		free(line);
	}
}

void			get_map(int fd0, int fd, t_core *cr)
{
	char		*line;
	int			yc;

	yc = 0;
	if (get_next_line(fd0, &line) == 1)
		yc++;
	else
		err_ex(2);
	cr->map_w = ft_ctwords(line, ' ');
	free(line);
	img_new(cr);
	while (get_next_line(fd0, &line) == 1)
	{
		if (line[0] == 0 || line[0] == '\n')
		{
			free(line);
			break ;
		}
		yc++;
		free(line);
	}
	close(fd0);
	get_mappart(cr, fd, line, yc);
	close(fd);
}
