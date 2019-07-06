/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 18:32:32 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "wolf.h"
#include <stdio.h>
#include <math.h>

void	make_cast(t_core *cr)
{
	double camera;

	cr->rcurr = 1;
	while (cr->rcurr < WIN_WIDTH)
	{
		camera = 2 * cr->rcurr / (double)WIN_WIDTH - 1;
		cr->castx = cr->dir.x + cr->plane.x * camera;
		cr->casty = cr->dir.y + cr->plane.y * camera;
		dda2(cr);
		draw(cr, WIN_WIDTH - cr->rcurr);
		cr->rcurr++;
	}
}
