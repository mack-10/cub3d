#include "cub3d.h"

void	draw(t_val *lst)
{
	for (int y = 0; y < screenH; y++)
	{
		for (int x = 0; x < screenW; x++)
		{
			lst->img.data[y * screenW + x] = lst->buf[y][x];
		}
	}
	mlx_put_image_to_window(lst->mlx, lst->win, lst->img.img, 0, 0);
}

void dda(int hit)
{
	while (hit == 0)
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
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
}


int		ray_c(t_val *lst)
{
	for (int y = 0; y < screenH; y++)
	{
		t_ray	ray;

		ray.rayDirX0 = lst->dirX - lst->planeX;
		ray.rayDirY0 = lst->dirY - lst->planeY;
		ray.rayDirX1 = lst->dirX + lst->planeX;
		ray.rayDirY1 = lst->dirY + lst->planeY;
		ray.p = y - screenH / 2;
		ray.posZ = 0.5 * screenH;
		ray.rowDistance = ray.posZ / ray.p;
		ray.floorStepX = ray.rowDistance * (ray.rayDirX1 - ray.rayDirX0) / screenW;
		ray.floorStepY = ray.rowDistance * (ray.rayDirY1 - ray.rayDirY0) / screenW;
		ray.floorX = lst->posX + ray.rowDistance * ray.rayDirX0;
		ray.floorY = lst->posY + ray.rowDistance * ray.rayDirY0;

		for (int x = 0; x < screenW; ++x)
		{
			int cellX = (int)(ray.floorX);
			int cellY = (int)(ray.floorY);
			int tx = (int)(textureW * (ray.floorX - cellX)) & (textureW - 1);
			int ty = (int)(textureH * (ray.floorY - cellY)) & (textureH - 1);

			ray.floorX += ray.floorStepX;
			ray.floorY += ray.floorStepY;

			int floorTexture = 3;
			//int ceilingTexture = 6;

			// Floor
			int color;
			color = lst->texture[floorTexture][textureW * ty + tx];
			color = (color >> 1) & 8355711;

			lst->buf[y][x] = color;

			// Ceiling
			// color = lst->texture[ceilingTexture][textureW * ty + tx];
			color = 0x00FF00;
			color = (color >> 1) & 8355711;

			lst->buf[screenH - y - 1][x] = color;
		}
	}

	for (int x = 0; x < screenW; x++)
	{
		double cameraX = 2 * x / (double)screenW - 1;
		double rayDirX = lst->dirX + lst->planeX * cameraX;
		double rayDirY = lst->dirY + lst->planeY * cameraX;
		int mapX = (int)lst->posX;
		int mapY = (int)lst->posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		int stepX;
		int stepY;
		
		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (lst->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - lst->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (lst->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - lst->posY) * deltaDistY;
		}

		// DDA Algorithm
		dda(ray, hit);

		// 수직거리 계산(PerpWallDist : 수직거리)
		if (side == 0)
			perpWallDist = (mapX - lst->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - lst->posY + (1 - stepY) / 2) / rayDirY;

		// 화면에 나타내야할 서느이 높이 구하기
		int lineHeight = (int)(screenH / perpWallDist);
		int drawStart = -lineHeight / 2 + screenH / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenH / 2;
		if (drawEnd >= screenH)
			drawEnd = screenH - 1;

		int texNum = worldMap[mapX][mapY] - 1;

		//벽 칠하기
		double wallX;
		if (side == 0)
			wallX = lst->posY + perpWallDist * rayDirY;
		else
			wallX = lst->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)textureW);
		if (side == 0 && rayDirX > 0)
			texX = textureW - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = textureW - texX - 1;

		double step = 1.0 * textureH / lineHeight;
		double texPos = (drawStart - screenH / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (textureH - 1);
			texPos += step;

			int color = lst->texture[texNum][textureH * texY + texX];

			if (side == 1)
				color = (color >> 1) & 8355711;

			lst->buf[y][x] = color;
		}

		double floorXWall, floorYWall;

		if (side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if (side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if (side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0)
			drawEnd = screenH;
		for (int y = drawEnd + 1; y < screenH; y++)
		{
			currentDist = screenH / (2.0 * y - screenH);

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double currentFloorX = weight * floorXWall + (1.0 - weight) * lst->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * lst->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * textureW) % textureW;
			floorTexY = (int)(currentFloorY * textureH) % textureH;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if (checkerBoardPattern == 0)
				floorTexture = 3;
			else
				floorTexture = 4;

			lst->buf[y][x] = (lst->texture[floorTexture][textureW * floorTexY + floorTexX] >> 1) & 8355711;
			lst->buf[screenH - y][x] = lst->texture[6][textureW * floorTexY + floorTexX];
		}
	}
	draw(lst);
	return (0);
}
