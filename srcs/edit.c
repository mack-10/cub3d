lst.win = mlx_new_window(lst.mlx, lst.par.screenW, lst.par.screenH, "cub3D");
			lst.img.img = mlx_new_image(lst.mlx, lst.par.screenW, lst.par.screenH);
			lst.img.data = (int *)mlx_get_data_addr(lst->img.img, &lst->img.bpp, &lst.img.size_l, &lst->img.endian);
			mlx_loop_hook(lst.mlx, &main_loop, lst.
			mlx_hook(lst.win, X_EVENT_KEY_PRESS, 0, &key_press, lst.
			mlx_hook(lst.win, X_EVENT_KEY_EXIT, 0, &ft_exit, 0);
			mlx_loop(lst.mlx);