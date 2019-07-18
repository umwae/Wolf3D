/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:07:09 by adoyle            #+#    #+#             */
/*   Updated: 2019/07/18 18:51:04 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf.h"

void		renderspr(t_core *cr, int ray, t_sprq *spr, int objnum)
{
	int		i;
	int		beg;
	int		tx;
	double	ty;
	int		c;

	i = 0;
	beg = (WIN_HIGHT - spr->sprh) / 2;
	while (i < spr->sprh && (i + beg) < WIN_HIGHT)
	{
		tx = (double)(spr->nd - ray) / (spr->nd - spr->st) * 592;
		ty = (double)(592) / spr->sprh;
		c = getgrad(cr->textures[cr->objarr[objnum].tex]
			[tx + ((int)(i * ty) * 592)],
			0, 1 - 1 / (cr->objarr[objnum].dist / 2 + 1));
		if (c != 0)
			cr->addr[ray + ((i + beg) * WIN_WIDTH)] = c;
		i++;
	}
}

void		calc_dist(t_core *cr)
{
	int i;

	i = 0;
	while (i < cr->spritesnum)
	{
		(cr->objarr[i].dist) = ((cr->player.x - cr->objarr[i].x) *
		(cr->player.x - cr->objarr[i].x) + \
		(cr->player.y - cr->objarr[i].y) * (cr->player.y - cr->objarr[i].y));
		i++;
	}
}

void		spritecalc(t_sprq *spr, t_core *cr, int i)
{
	spr->sprx = cr->objarr[i].x - cr->player.x;
	spr->spry = cr->objarr[i].y - cr->player.y;
	spr->invd = 1.0 / (cr->plane.x * cr->dir.y - cr->dir.x * cr->plane.y);
	spr->tx = spr->invd * (cr->dir.y * spr->sprx - cr->dir.x * spr->spry);
	spr->ty = spr->invd * (-cr->plane.y * spr->sprx + cr->plane.x * spr->spry);
	spr->sprscrx = (int)((WIN_WIDTH / 2) * (1 + spr->tx / spr->ty));
	spr->u = 1;
	spr->v = 1;
	spr->sprh = abs((int)(WIN_HIGHT / spr->ty)) / spr->v;
	spr->sprw = abs((int)(WIN_HIGHT / spr->ty)) / spr->u;
	spr->bspr = -spr->sprw / 2 + spr->sprscrx;
	spr->st = WIN_WIDTH - spr->bspr;
	if (spr->bspr < 0)
		spr->bspr = 0;
	spr->espr = spr->sprw / 2 + spr->sprscrx;
	spr->nd = WIN_WIDTH - spr->espr;
	if (spr->espr >= WIN_WIDTH)
		spr->espr = WIN_WIDTH - 1;
	spr->strp = spr->bspr;
}

void		sprite(t_core *cr)
{
	t_sprq	*spr;
	int		i;

	spr = malloc(sizeof(t_sprq));
	i = cr->spritesnum - 1;
	calc_dist(cr);
	while (i >= 0)
	{
		spritecalc(spr, cr, i);
		while (spr->strp < spr->espr)
		{
			if (spr->ty > 0 && spr->strp > 0 && spr->strp < WIN_WIDTH &&
				spr->ty < cr->mdist[spr->strp])
				renderspr(cr, WIN_WIDTH - spr->strp, spr, i);
			spr->strp++;
		}
		i--;
	}
	free(spr);
}
