#include "mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include "wolf.h"

void	renderspr(t_win *cr, int ray, int spriteH, int startspr, int endspr)
{
	int i;
	double	column;
	int	beg;
	//
	int tx;
	double	ty;
	double	x;
	int t;
	int c;
	char	*img;

	i = 0;
	column = spriteH;//Заменить на норм. расчет высоты столбцов
	beg = (WIN_HIGHT - column) / 1.5;
	// printf("%d    ", ray);
	// fflush(stdout);
	x = ray;
	//
	while (i < WIN_HIGHT)
	{
		if ((i > beg) && (i < WIN_HIGHT - beg) && i > 0)
		{
			tx = (double)(endspr - ray) / (endspr - startspr) * 592;
			if (tx < 0)
				tx = 0;//?????????????????????????
			ty = (double)592 / spriteH;
			t = i * ty;
			if (t > 592)
				t = 592;//??????????????????//
			c = cr->textures[2][tx + (t * 592)];
			if (((c >> 16) & 0xff) != 0)
				cr->addr[ray + ((i + beg) * WIN_WIDTH)] = c;
		}
		i++;
	}
}

static void	calc_dist(t_win *cr)
{
	int i = 0;

	while (i < cr->spritesnum)
	{
		(cr->sprOrder[i].sprdist) = ((cr->player.x - cr->sprOrder[i].x) * (cr->player.x - cr->sprOrder[i].x) + \
		(cr->player.y - cr->sprOrder[i].y) * (cr->player.y - cr->sprOrder[i].y));
		i++;
	}
}

void	sprite(t_win *cr)
{
	int i;
	//
	int	st;
	int	nd;

	i = 0;
	calc_dist(cr);
	while (i < cr->spritesnum)
	{
		double	sprX = cr->sprOrder[i].x - cr->player.x;
		double	sprY = cr->sprOrder[i].y - cr->player.y;
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
		st = startspr;
		if (startspr < 0)
			startspr = 0;
		int	endspr = spriteW / 2 + sprscrX;
		//
		nd = endspr;
		if (endspr >= WIN_WIDTH)
			endspr = WIN_WIDTH - 1;
		int stripe = startspr;
		while(stripe < endspr)
		{
			if(transY > 0 && stripe > 0 && stripe < WIN_WIDTH && transY < cr->mdist[stripe])
				renderspr(cr, WIN_WIDTH - stripe, spriteH, st, nd);
			stripe++;
		}
		i++;
	}
}

void		sort_sprites(t_win *cr)
{
	int		i, j;
	for (i = 0 ; i < cr->spritesnum - 1; i++)
	{
		for (j = 0 ; j < cr->spritesnum - i - 1 ; j++)
		{
			if (cr->sprOrder[j].sprdist > cr->sprOrder[j+1].sprdist)
			{
				t_spr tmp = cr->sprOrder[j];
				cr->sprOrder[j] = cr->sprOrder[j + 1];
				cr->sprOrder[j + 1] = tmp;
			}
		}
	}
}

static void	remove_obj(t_win *cr)
{
	int	i = 0;
	while (i < cr->spritesnum - 1)
	{
		cr->sprOrder[i] = cr->sprOrder[i + 1];
		i++;
	}
	cr->spritesnum--;
}

void		pickup_obj(t_win *cr)
{
	if (cr->sprOrder[0].type == 'c')
	{
		cr->coins += cr->sprOrder[0].val;
	}
	remove_obj(cr);
}

void		check_obj(t_win *cr)
{
	calc_dist(cr);
	sort_sprites(cr);
	if (cr->spritesnum == 0)
		return ;
	if (cr->sprOrder[0].sprdist < 0.5)
		pickup_obj(cr);
}

void		obj_init(t_win *cr)
{
	int		y;

	t_spr	sprarr[SPRITESNUM] =
	{{5.5, 5.5, 2, 0.0, 'c', 1},
	{3.5, 7.5, 2, 0.0, 'c', 1},
	{8.5, 2.5, 2, 0.0, 'c', 1}};
	int	i = 0;
	while (i < cr->spritesnum)
	{
		cr->sprOrder[i].x = sprarr[i].x;
		cr->sprOrder[i].y = sprarr[i].y;
		cr->sprOrder[i].tex = sprarr[i].tex;
		cr->sprOrder[i].type = sprarr[i].type;
		cr->sprOrder[i].val = sprarr[i].val;
		// cr->text = mlx_xpm_file_to_image(cr->mlx, "src/coin.xpm", &(cr->sprOrder[i].texsize), &y);
		// cr->sprOrder[i].tex = (int *)mlx_get_data_addr(cr->text, &cr->bpp, &(cr->linesize), &(cr->endian));
		i++;
	}
}
