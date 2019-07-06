
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void		bresenham(t_core *cr)
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

void	dda2(t_core *cr)
{
    int mapX = (int)cr->player.x;
    int mapY = (int)cr->player.y;

    double sideDistX;
    double sideDistY;

    double deltaDistX = sqrt(1 + (cr->casty * cr->casty) / (cr->castx * cr->castx));
    double deltaDistY = sqrt(1 + (cr->castx * cr->castx) / (cr->casty * cr->casty));

    int stepX;
    int stepY;

    int hit = 0;
    int side;
	if (cr->castx < 0)
	{
		stepX= -1;
		sideDistX = (cr->player.x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
       	sideDistX = (mapX + 1.0 - cr->player.x) * deltaDistX;
	}
	if (cr->casty < 0)
    {
    	stepY = -1;
		sideDistY = (cr->player.y - mapY) * deltaDistY;
    }
	else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - cr->player.y) * deltaDistY;
    }
    while (hit == 0 && (mapX < 40 && mapY <= 40))
    {
    	if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        if (((cr->tiles[mapY][mapX]) > 0) || (mapX > 40 || mapY > 40))
					hit = 1;
    }
	if (side == 0)
		cr->dist = (mapX - cr->player.x + (1 - stepX) / 2) / cr->castx;
    else
		cr->dist = (mapY - cr->player.y + (1 - stepY) / 2) / cr->casty;

	cr->mdist[cr->rcurr] = cr->dist;
	double wallX; //where exactly the wall was hit
  if (side == 0)
  	wallX = cr->player.y + cr->dist * cr->casty;
  else
  	wallX = cr->player.x + cr->dist * cr->castx;
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
	if(side == 0 && cr->castx > 0)
      {
        cr->hitx = mapX;
        cr->hity = wallX;
		cr->wall = 'w';
		cr->wtexnum = 1;
      }
      else if(side == 0 && cr->castx < 0)
      {
        cr->hitx = mapX + 1.0;
        cr->hity = wallX;
		cr->wall = 'e';
		cr->wtexnum = 6;
      }
      else if(side == 1 && cr->casty > 0)
      {
        cr->hitx = wallX;
        cr->hity = mapY;
		cr->wall = 'n';
		cr->wtexnum = 4;
      }
      else
      {
        cr->hitx = wallX;
        cr->hity = mapY + 1.0;
		cr->wall = 's';
		cr->wtexnum = 7;
      }
	if (cr->hitx > cr->map_w)
		cr->hitx = cr->map_w - 1;
	if (cr->hity > cr->map_h)
		cr->hity = cr->map_h - 1;
	if (cr->hitx < 1)
		cr->hitx = 1;
	if (cr->hity < 1)
		cr->hity = 1;
	// printf("x - %f, y - %f\n", cr->hitx, cr->hity);
}
