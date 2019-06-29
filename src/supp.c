/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:21:49 by adoyle            #+#    #+#             */
/*   Updated: 2019/06/21 19:12:10 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
#include <math.h>

char	checker(t_win *cr, double x, double y, int **tiles)
{
	char s = ' ';

	// printf("%f %f | ", x, y);
	if ((x - (int)x) == 0)
	{
		if (tiles[(int)y][(int)(x + 0.00001)] == 0)
			s = 'e';
		else if (tiles[(int)y][(int)(x - 0.00001)] == 0)
			s = 'w';
	}
	else
	{
		if (tiles[(int)(y + 0.00001)][(int)x] == 0)
			s = 's';
		if (tiles[(int)(y - 0.00001)][(int)x] == 0)
			s = 'n';
	}
	return (s);
}

// char	checker(t_win *cr, double x, double y, int **tiles)
// {
// 	char s;
//
// 	if (tiles[(int)y][(int)(x + 0.00001)] == 0)
// 		s = 'e';
// 	else if (tiles[(int)y][(int)(x - 0.00001)] == 0)
// 		s = 'w';
// 	if (tiles[(int)(y + 0.00001)][(int)x] == 0)
// 		s = 's';
// 	if (tiles[(int)(y - 0.00001)][(int)x] == 0)
// 		s = 'n';
// 	return (s);
// }
