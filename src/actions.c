/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/21 19:39:57 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "wolf.h"

// int			mouse_move(int x, int y, t_win *win1)
// {
// 	if (win1->dragl == 1)
// 	{
// 		// win1->x_offset += x - win1->x_mem;
// 		// win1->y_offset += y - win1->y_mem;
// 		win1->x_mem = x;
// 		win1->y_mem = y;
// 	}
// 	else if (win1->dragr == 1)
// 	{
// 		// win1->cre_start += (x - win1->x_mem) / win1->zoom;
// 		// win1->cim_start += (y - win1->y_mem) / win1->zoom;
// 		// win1->x_mem = x;
// 		// win1->y_mem = y;
// 		return (0);
// 	}
// 	else
// 		return (0);
// 	visual(win1);
// 	return (0);
// }

// int			mouse_release(int button, int x, int y, t_win *win1)
// {
// 	if (button == 1)
// 		win1->dragl = 0;
// 	else if (button == 2)
// 		win1->dragr = 0;
// 	return (0);
// 	(void)x;
// 	(void)y;
// }
//
// static void	mouse_press2(int button, int x, int y, t_win *win1)
// {
// 	if (button == 1)
// 	{
// 		win1->x_mem = x;
// 		win1->y_mem = y;
// 		win1->dragl = 1;
// 	}
// 	else if (button == 2)
// 	{
// 		win1->x_mem = x;
// 		win1->y_mem = y;
// 		win1->dragr = 1;
// 	}
// }

// int			mouse_press(int button, int x, int y, t_win *win1)
// {
// 	if (button == 5)
// 	{
// 		win1->x_mem = WIN_WIDTH / 2;
// 		win1->y_mem = WIN_HIGHT / 2;
// 		win1->zoom += win1->zoom / 2;
// 		// win1->x_offset += (win1->x_len - (x - win1->x_mem) / 2);
// 		// win1->y_offset += (win1->y_len - (y - win1->y_mem) / 2);
// 	}
// 	else if (button == 4)
// 	{
// 		win1->x_mem = WIN_WIDTH / 2;
// 		win1->y_mem = WIN_HIGHT / 2;
// 		win1->zoom -= win1->zoom / 3;
// 		// win1->x_offset -= win1->x_len - (x - win1->x_mem) / 3;
// 		// win1->y_offset -= win1->y_len - (y - win1->y_mem) / 3;
// 	}
// 	else
// 		mouse_press2(button, x, y, win1);
// 	visual(win1);
// 	return (0);
// }

int			key_action(int keycode, t_win *win1)
{
	// printf("%d ", keycode);
	fflush(stdout);
	if (keycode == 53)
		exit(0);
	// else if (keycode == 123)
	// 	win1->dir.x -= 9;
	// else if (keycode == 124)
	// 	win1->dir.x += 9;
	// else if (keycode == 125)
	// 	win1->dir.y += 9;
	// else if (keycode == 126)
	// 	win1->dir.y -= 9;
	else if (keycode == 0)
	{
		win1->player.x += win1->plane.x / win1->plane.len * SPEED;
		win1->player.y += win1->plane.y / win1->plane.len * SPEED;
	}
	else if (keycode == 2)
	{
		win1->player.x -= win1->plane.x / win1->plane.len * SPEED;
		win1->player.y -= win1->plane.y / win1->plane.len * SPEED;
	}
	else if (keycode == 13)
	{
		win1->player.x += win1->dir.x / win1->dir.len * SPEED;
		win1->player.y += win1->dir.y / win1->dir.len * SPEED;
	}
	else if (keycode == 1)
	{
		win1->player.x -= win1->dir.x / win1->dir.len * SPEED;
		win1->player.y -= win1->dir.y / win1->dir.len * SPEED;
	}
	else if (keycode == 12)
	{
		transform(win1, &(win1->dir.x), &(win1->dir.y), 'L');
		transform(win1, &(win1->plane.x), &(win1->plane.y), 'L');
	}
	else if (keycode == 14)
	{
		transform(win1, &(win1->dir.x), &(win1->dir.y), 'R');
		transform(win1, &(win1->plane.x), &(win1->plane.y), 'R');
	}
	visual(win1);
	return (0);
}
