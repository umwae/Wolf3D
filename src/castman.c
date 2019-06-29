#include "mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void		bresenham(t_win *cr)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	x0 = cr->vs->x_i;
	y0 = cr->vs->y_i;
	x1 = cr->vs->x2_i;
	y1 = cr->vs->y2_i;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
 	while (x0 != x1 || y0 != y1)
	{
    	img_pxl(cr, x0, y0, cr->vs->vcolor);
    	// if (x0 == x1 && y0 == y1)
		// 	break;
    	e2 = err;
    	if (e2 >- dx)
		{
			err -= dy;
			x0 += sx;
		}
    	if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
  	}
}

static int	ft_roundl(double x, double istep)
{
	int	y;

	if (istep > 0)
	{
		y = floor(x);
	}
	else
	{
		y = ceil(x) - 1;
	}
	// printf("%f::::%f  ", x, y);
	// fflush(stdout);
	if (y < 0)
	{
		// printf("! OOB < 0 ");
		y = 0;
	}
	if (y > 23)
	{
		// printf("! OOB > 23 ");
		y = 0;
	}
	// printf("%d ++++ ", y);
	// fflush(stdout);
	return (y);
}

void	dda(t_win *cr)
{
	t_obj	inext;
	t_obj	d_inv;
	t_obj	istep;
	float	px;
	float	py;
	float	dx;
	float	dy;
	int		i_max = MAX_DIST;
	int		mapValue;

	cr->dist = 0;
	cr->objcl = 0;
	d_inv.x = 1.0f / cr->castx;
	d_inv.y = 1.0f / cr->casty;

	istep.x = (cr->castx < 0.0f) ? -1 : 1;
	istep.y = (cr->casty < 0.0f) ? -1 : 1;

	inext.x = (cr->castx < 0.0f) ? ceil(cr->player.x) + istep.x : floor(cr->player.x) + istep.x;
	inext.y = (cr->casty < 0.0f) ? ceil(cr->player.y) + istep.y : floor(cr->player.y) + istep.y;
	while (i_max--)
	{
		px = cr->player.x + cr->castx * cr->dist;
		py = cr->player.y + cr->casty * cr->dist;
		//
		// mapValue = wall_check(cr, px, py);
		//
		// printf("%d, %d\n", (int)ceil(py + 0.01 * istep.y), (int)ceil(px + 0.01 * istep.x));
		// fflush(stdout);
		// printf("%d, %d | ", ft_roundl(py, istep.y), ft_roundl(px, istep.x));
		// fflush(stdout);
		if (cr->tiles[ft_roundl(py, istep.y)][ft_roundl(px, istep.x)] != 0)
		{
			// img_pxl(cr, px * cr->vs->gridsize + cr->vs->x_offset, py * cr->vs->gridsize + cr->vs->y_offset, 0x0000ff);//Для минимапы
			cr->hitx = px;
			cr->hity = py;
			return ;
		}
		// mapValue = cr->tiles[(int)ceil(py + 0.01 * istep.y)][(int)ceil(px + 0.01 * istep.x)];
		// if (mapValue != 0)
		// {
		// 	tile_color(mapValue, cr);
		// 	cr->hitx = px;
		// 	cr->hity = py;
		// 	return ;
		// }
		dx = ((float)(inext.x) - cr->player.x) * d_inv.x;
		dy = ((float)(inext.y) - cr->player.y) * d_inv.y;
		cr->dist = dx < dy ? dx : dy;
		if (dx == cr->dist)
			inext.x += istep.x;
		if (dy == cr->dist)
			inext.y += istep.y;
	}
}
