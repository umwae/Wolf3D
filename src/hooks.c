/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:41:27 by adoyle            #+#    #+#             */
/*   Updated: 2019/06/12 19:05:15 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int		mouse_move(int x, int y, void *param)
{
	t_core	*core;

	core = (t_core*)param;
	if (x > widht / 2)
		core->play->pa++;
	else
		core->play->pa++;
	raycast(core);
	return (0);
}

void	arrow(int key, t_core *core)
{
	double ray_ang;

	ray_ang = (double)core->play->pa - ((double)core->play->fov / 2);
	if (key == 124)
		core->play->pa += 8;
	if (key == 123)
		core->play->pa -= 8;
	if (key == 126)
	{
		core->play->px += (core->map->step * 2 * cos(core->play->pa * M_PI / 180) * 5);
		core->play->py += (core->map->step * 2 * sin(core->play->pa * M_PI / 180) * 5);
	}
	if (key == 125)
	{
		core->play->px += (core->map->step * 2 * cos((core->play->pa + 180) * M_PI / 180) * 5);
		core->play->py += (core->map->step * 2 * sin((core->play->pa + 180) * M_PI / 180) * 5);
	}
	raycast(core);
}

int		control(int press_key, void *param)
{
	t_core	*core;

	core = (t_core*)param;
	if (press_key == 53)
		exit(-2);
	if (press_key == 125 || press_key == 126 ||
	press_key == 124 || press_key == 123)
		arrow(press_key, core);
	return (0);
}