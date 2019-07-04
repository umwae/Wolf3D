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

void	err_ex(int pr)
{
	if (pr == 0)
		ft_putstr("Error: memory allocation failure\n");
	if (pr == 1)
		ft_putstr("Error: invalid map\n");
	if (pr == 2)
		ft_putstr("Error: can't read from file\n");
	exit(1);
}

int		main(int argc, char **argv)
{
	t_core		*cr;

	if (!(cr = (t_core *)malloc(sizeof(t_core))))
		err_ex(0);
	init(argv[1], cr);
	hooks(cr);
	(void)argc;
	return (0);
}
