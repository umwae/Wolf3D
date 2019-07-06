/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:43 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 17:28:23 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
#include <stdio.h>

void			visual(t_core *cr)
{
	mlx_destroy_image(cr->mlx, cr->img_ptr);
	img_new(cr);
	make_cast(cr);
	sprite(cr);
	minimap_init(cr);
	minimap(cr);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->img_ptr, 0, 0);
	draw_gui(cr);
}
