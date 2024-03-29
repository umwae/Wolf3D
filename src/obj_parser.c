/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:58:47 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/18 18:50:40 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "wolf.h"

double	ft_atod(char *l)
{
	int		i;
	int		k;
	int		j;
	int		c;
	double	r;

	i = 0;
	if (l[0] > 47 && l[0] < 58)
		k = ft_atoi(l);
	else
		k = ft_atoi(l + 3);
	while (l[i] != '.')
		i++;
	j = ft_atoi(l + i + 1);
	c = 0;
	i++;
	while (l[i++] != ',')
		c++;
	i = 1;
	while (c--)
		i = i * 10;
	r = k + ((double)j / (double)i);
	return (r);
}

int		checkd(char *l, int i)
{
	int j;

	j = 0;
	while (l[i] && l[i] != ',')
	{
		if (l[i] == '.')
			j = 1;
		i++;
	}
	return (j);
}

void	writemass(t_obj *spr, char *l)
{
	int		i;
	int		j;
	double	tx;

	i = 0;
	j = 0;
	if (checkd(l, i) == 1)
		spr->x = ft_atod(l + 2);
	else
		spr->x = ft_atoi(l + 5);
	while (l[i])
	{
		if (l[i] == ',' && j == 0)
		{
			if (checkd(l, i + 2) == 1)
				spr->y = ft_atod(l + i + 2);
			else
				spr->y = ft_atoi(l + i + 2);
			j++;
			i++;
		}
		if (l[i] == ',' && j == 1)
			spr->tex = ft_atoi(l + i + 2);
		i++;
	}
}

void	write_obj(t_core *cr, int fd, int count)
{
	t_obj	spr[count];
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] > 47 && line[0] < 58)
		{
			free(line);
			break ;
		}
		if (i == 1)
		{
			writemass(&cr->objarr[j], line);
			j++;
		}
		if (ft_strcmp("obj:", line) == 0)
			i = 1;
		free(line);
	}
}

void	get_obj(t_core *cr, char *argv)
{
	int		i;
	char	*line;

	cr->fd3 = open(argv, O_RDONLY);
	cr->fd4 = open(argv, O_RDONLY);
	i = 0;
	cr->count = 0;
	while (get_next_line(cr->fd3, &line) == 1)
	{
		if (line[0] > 47 && line[0] < 58)
		{
			free(line);
			break ;
		}
		if (i == 1)
			cr->count++;
		if (ft_strcmp("obj:", line) == 0)
			i = 1;
		free(line);
	}
	while (get_next_line(cr->fd3, &line) == 1)
		free(line);
	close(cr->fd3);
	write_obj(cr, cr->fd4, cr->count);
	close(cr->fd4);
}
