/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/02 16:36:04 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "wolf.h"
#include <stdio.h>
#include <math.h>

void	make_cast(t_win *cr)
{

	cr->rcurr = 1; //??????????????????
	// rcurr = -cr->rays;
	while (cr->rcurr < WIN_WIDTH)
	{
		// cr->castx = cr->dir.x - cr->plane.x / 2 + (cr->plane.x / WIN_WIDTH * cr->rcurr);
		// cr->casty = cr->dir.y - cr->plane.y / 2 + (cr->plane.y / WIN_WIDTH * cr->rcurr);
		double camera = 2 * cr->rcurr / (double)WIN_WIDTH - 1;
		cr->castx = cr->dir.x + cr->plane.x * camera;
		cr->casty = cr->dir.y + cr->plane.y * camera;
		dda2(cr);
		// printf("%d    ", cr->rcurr);
		// fflush(stdout);
		draw(cr, WIN_WIDTH - cr->rcurr);
		cr->rcurr++;
	}
}
