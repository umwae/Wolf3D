/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:07:09 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/18 18:51:16 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		sort_obj(t_core *cr)
{
	t_obj	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < cr->spritesnum - 1)
	{
		j = 0;
		while (j < cr->spritesnum - i - 1)
		{
			if (cr->objarr[j].dist > cr->objarr[j + 1].dist)
			{
				tmp = cr->objarr[j];
				cr->objarr[j] = cr->objarr[j + 1];
				cr->objarr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	remove_obj(t_core *cr)
{
	int	i;

	i = 0;
	while (i < cr->spritesnum - 1)
	{
		cr->objarr[i] = cr->objarr[i + 1];
		i++;
	}
	cr->spritesnum--;
}

void		pickup_obj(t_core *cr)
{
	cr->coins += 1;
	remove_obj(cr);
}

void		check_obj(t_core *cr)
{
	calc_dist(cr);
	sort_obj(cr);
	if (cr->spritesnum == 0)
		return ;
	if (cr->objarr[0].dist < 0.5)
		pickup_obj(cr);
}
