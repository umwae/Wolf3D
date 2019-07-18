/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:42:41 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf.h"

int			red_button(t_core *pr)
{
	(void)pr;
	exit(0);
}

static void	key_action2(int keycode, t_core *cr)
{
	if (keycode == 13)
	{
		cr->tmp_p_x += cr->dir.x / cr->dir.len * SPEED;
		cr->tmp_p_y += cr->dir.y / cr->dir.len * SPEED;
	}
	else if (keycode == 1)
	{
		cr->tmp_p_x -= cr->dir.x / cr->dir.len * SPEED;
		cr->tmp_p_y -= cr->dir.y / cr->dir.len * SPEED;
	}
	else if (keycode == 12)
	{
		transform(cr, &(cr->dir.x), &(cr->dir.y), 'L');
		transform(cr, &(cr->plane.x), &(cr->plane.y), 'L');
	}
	else if (keycode == 14)
	{
		transform(cr, &(cr->dir.x), &(cr->dir.y), 'R');
		transform(cr, &(cr->plane.x), &(cr->plane.y), 'R');
	}
}

int			key_action(int keycode, t_core *cr)
{
	cr->tmp_p_x = cr->player.x;
	cr->tmp_p_y = cr->player.y;
	if (keycode == 53)
		exit(0);
	else if (keycode == 0)
	{
		cr->tmp_p_x += cr->plane.x / cr->plane.len * SPEED;
		cr->tmp_p_y += cr->plane.y / cr->plane.len * SPEED;
	}
	else if (keycode == 2)
	{
		cr->tmp_p_x -= cr->plane.x / cr->plane.len * SPEED;
		cr->tmp_p_y -= cr->plane.y / cr->plane.len * SPEED;
	}
	else
		key_action2(keycode, cr);
	if (cr->tiles[(int)cr->tmp_p_y][(int)cr->player.x] == 0 && \
	cr->tmp_p_y <= cr->map_h)
		cr->player.y = cr->tmp_p_y;
	if (cr->tiles[(int)cr->player.y][(int)cr->tmp_p_x] == 0 && \
	cr->tmp_p_x <= cr->map_w)
		cr->player.x = cr->tmp_p_x;
	check_obj(cr);
	visual(cr);
	return (0);
}
