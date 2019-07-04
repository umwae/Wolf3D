#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void	renderspr(t_core *cr, int ray, double column, int startspr, int endspr, int objnum)
{
	int i;
	int	beg;
	int tx;
	double	ty;
	int t;
	int c;

	i = 0;
	beg = (WIN_HIGHT - column) / 2;
	while (i < column)
	{
		tx = (double)(endspr - ray) / (endspr - startspr) * cr->objarr[objnum].texsize;
		ty = (double)(cr->objarr[objnum].texsize) / column;
		t = i * ty;
		c = cr->textures[cr->objarr[objnum].tex][tx + (t * cr->objarr[objnum].texsize)];
		if (((c >> 16) & 0xff) != 0)
			cr->addr[ray + ((i + beg) * WIN_WIDTH)] = c;
		i++;
	}
}

static void	calc_dist(t_core *cr)
{
	int i = 0;

	while (i < cr->spritesnum)
	{
		(cr->objarr[i].dist) = ((cr->player.x - cr->objarr[i].x) * (cr->player.x - cr->objarr[i].x) + \
		(cr->player.y - cr->objarr[i].y) * (cr->player.y - cr->objarr[i].y));
		i++;
	}
}

void	sprite(t_core *cr)
{
	int i;
	//
	int	st;
	int	nd;

	i = 0;
	calc_dist(cr);
	while (i < cr->spritesnum)
	{
		double	sprX = cr->objarr[i].x - cr->player.x;
		double	sprY = cr->objarr[i].y - cr->player.y;
		double invDet = 1.0 / (cr->plane.x * cr->dir.y - cr->dir.x * cr->plane.y);

		double	transX = invDet * (cr->dir.y * sprX - cr->dir.x * sprY);
		double	transY = invDet * (-cr->plane.y * sprX + cr->plane.x * sprY);

		int sprscrX = (int)((WIN_WIDTH / 2) * (1 + transX / transY));
		int uDiv = 1;
		int vDiv = 1;
		double vMove = 0.0;
		int vMovescr = (int)(vMove / transY);
		int spriteH = abs((int)(WIN_HIGHT / transY)) / vDiv;
		int spriteW = abs((int)(WIN_HIGHT / transY)) / uDiv;
		int startspr = -spriteW /2 + sprscrX;
		//
		st = WIN_WIDTH - startspr;
		if (startspr < 0)
			startspr = 0;
		int	endspr = spriteW / 2 + sprscrX;
		//
		nd = WIN_WIDTH - endspr;
		if (endspr >= WIN_WIDTH)
			endspr = WIN_WIDTH - 1;
		int stripe = startspr;
		while(stripe < endspr)
		{
			if(transY > 0 && stripe > 0 && stripe < WIN_WIDTH && transY < cr->mdist[stripe])
				renderspr(cr, WIN_WIDTH - stripe, spriteH, st, nd, i);
			stripe++;
		}
		i++;
	}
}

void		sort_obj(t_core *cr)
{
	int		i, j;
	for (i = 0 ; i < cr->spritesnum - 1; i++)
	{
		for (j = 0 ; j < cr->spritesnum - i - 1 ; j++)
		{
			if (cr->objarr[j].dist > cr->objarr[j+1].dist)
			{
				t_obj tmp = cr->objarr[j];
				cr->objarr[j] = cr->objarr[j + 1];
				cr->objarr[j + 1] = tmp;
			}
		}
	}
}

static void	remove_obj(t_core *cr)
{
	int	i = 0;
	while (i < cr->spritesnum - 1)
	{
		cr->objarr[i] = cr->objarr[i + 1];
		i++;
	}
	cr->spritesnum--;
}

void		pickup_obj(t_core *cr)
{
	if (cr->objarr[0].type == 'c')
	{
		cr->coins += cr->objarr[0].val;
	}
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

void		obj_init(t_core *cr)
{
	int		y;

	t_obj	sprarr[SPRITESNUM] =
	{{6.5, 5.5, 3, 592, 0.0, 'c', 1},
	{3.5, 7.5, 3, 592, 0.0, 'c', 1},
	{8.5, 2.5, 3, 592, 0.0, 'c', 1}};
	int	i = 0;
	while (i < cr->spritesnum)
	{
		cr->objarr[i].x = sprarr[i].x;
		cr->objarr[i].y = sprarr[i].y;
		cr->objarr[i].tex = sprarr[i].tex;
		cr->objarr[i].texsize = sprarr[i].texsize;
		cr->objarr[i].type = sprarr[i].type;
		cr->objarr[i].val = sprarr[i].val;
		// cr->text = mlx_xpm_file_to_image(cr->mlx, "src/coin.xpm", &(cr->objarr[i].texsize), &y);
		// cr->objarr[i].tex = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
		i++;
	}
}
