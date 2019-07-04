/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:53:58 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/02 19:10:33 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

void			transform(t_core *win1, double *x0, double *y0, char dir)
{
	double	x;
	double	y;

	x = *x0;
	y = *y0;
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
}
