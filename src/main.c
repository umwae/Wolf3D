/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:49:03 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf.h"

void	err_ex(int pr)
{
	if (pr == 0)
		ft_putstr("Error: memory allocation failure\n");
	if (pr == 1)
		ft_putstr("Error: invalid map\n");
	if (pr == 2)
		ft_putstr("Error: can't read from file\n");
	if (pr == 3)
		ft_putstr("Usage: ./wolf3d map_name\n");
	if (pr == 4)
		ft_putstr("Error: change player's position!\n");
	exit(1);
}

int		hooks(t_core *cr)
{
	visual(cr);
	mlx_hook(cr->win, 2, 1, key_action, cr);
	mlx_hook(cr->win, 17, 1, red_button, cr);
	mlx_loop(cr->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_core		*cr;

	if (argc != 2)
		err_ex(3);
	if (!(cr = (t_core *)malloc(sizeof(t_core))))
		err_ex(0);
	init(argv[1], cr);
	get_obj(cr, argv[1]);
	hooks(cr);
	(void)argc;
	return (0);
}
