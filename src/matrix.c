/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:53:58 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/04 21:14:44 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

void			transform(t_win *win1, double *x0, double *y0, char dir)
{
	double	x = *x0;
	double	y = *y0;

	// printf("DO %d\n", win1->dir.y2);
	if (dir == 'R')
	{
		*x0 = x * cos(win1->rotation) + y * sin(win1->rotation);
		*y0 = x * -sin(win1->rotation) + y * cos(win1->rotation);
	}
	else if (dir == 'L')
	{
		*x0 = x * cos(win1->rotation) + y * -sin(win1->rotation);
		*y0 = x * sin(win1->rotation) + y * cos(win1->rotation);
	}
	// printf("POSLE %d\n", win1->dir.y2);
}
