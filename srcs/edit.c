static void		dda(t_main *lst)
{
	while (lst->ray.hit == 0)
	{
		if (lst->ray.sideDistX < lst->ray.sideDistY)
		{
			lst->ray.sideDistX += lst->ray.deltaDistX;
			lst->ray.mapX += lst->ray.stepX;
			lst->ray.side = 0;
		}
		else
		{
			lst->ray.sideDistY += lst->ray.deltaDistY;
			lst->ray.mapY += lst->ray.stepY;
			lst->ray.side = 1;
		}
		if (worldMap[lst->ray.mapX][lst->ray.mapY] > 0)
			lst->ray.hit = 1;
	}
}