/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/06/21 20:03:23 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "wolf.h"
#include <time.h>
#include <stdio.h>

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
	exit(1);
}

int		hooks(t_core *cr)
{
// 	int ms = 0;
// 	int msp = 0;
// 	int i = 0;
//
// visual(cr);
// 	while(i < 999999)
// 	{
// 		msp = ms;
// 		while (ms - msp < 3000)
// 		{
// 			ms = clock() * 1000 / CLOCKS_PER_SEC;
// 		}
// 		key_action(13, cr);
// 		i++;
// 	}
	// printf("%d\n", milliseconds_since);
	visual(cr);
	//
	// mlx_hook(cr->win, 4, 1, mouse_press, cr);
	// mlx_hook(cr->win, 5, 1, mouse_release, cr);
	// mlx_hook(cr->win, 6, 1, mouse_move, cr);
	mlx_hook(cr->win, 2, 1, key_action, cr);
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
	hooks(cr);
	(void)argc;
	return (0);
}
