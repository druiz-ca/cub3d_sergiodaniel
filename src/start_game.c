/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 06:51:54 by daniel            #+#    #+#             */
/*   Updated: 2024/12/14 08:21:49 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Ft para manejar eventos durante la ejecución del juego */
void	ft_hook(void *param)
{
	t_data		*data;

	data = param;

	// Borra la imagen de las paredes si el rayo 0 tiene delta_dist_y (??)
	if (data->player.ray[0].delta_dist_y)
		mlx_delete_image(data->mlx, data->walls);

	// Cierra la ventana si se presiona la tecla ESC
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);

	// Maneja los movimientos del jugador
	handle_player_movement(data);

	// Maneja la rotación del jugador
	handle_player_rotation(data);

	// Inicia la imagen de las paredes
	image_init(data, &data->walls);

	// Dibuja el rayo
	print_ray(data, &data->player);
}

/* Función que carga la imagen correspondiente, comprueba que no haya errores, 
y la muestra en pantalla comprobando también posibles errores */
void	image_init(t_data *data, mlx_image_t **image)
{
	// Crea una nueva imagen de tamaño WIDTH x HEIGHT
	*image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if(!*image)
	{
		print_error("Failed creating floor-ceiling image\n");
		exit(FAILURE);
	}

	// Muestra la imagen en la pantalla en la posición 0,0
	if (mlx_image_to_window(data->mlx, *image, 0, 0) == -1)
	{
		print_error("Failed in mlx_image_to_window() for floor-ceiling image\n");
		exit(FAILURE);
	}
}

/* Función que crea la ventana gráfica: inicia la MLX y comprueba que haya iniciado 
correctamente, desactiva el mouse, inicia la imagen de fondo y las paredes, 
establece move a 4, busca la  posición del jugador en el mapa y pinta de colores 
diferentes el techo y el suelo */
void	game_init(t_data *data)
{
	// Inicializa la mlx
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	// Desactiva el mouse
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);

	// Comprueba que haya iniciado correctamente
	if (!data->mlx)
	{
		print_error("Failed to initialiaze mlx.\n");
		exit(1);
	}

	// Inicia la imagen de fondo
	image_init(data, &data->background);
	// Inicia la imagen de las paredes
	image_init(data, &data->walls);

	// Establece move a 4
	data->move = 4;

	// Busca la posición del jugador en el mapa
	find_player_position(data, data->map.map);

	// Pinta el techo y el suelo de 2 colores diferentes
	paint_floor_ceiling(data);
}

/* Función que inicia el juego */
void    start_game(t_data *data)
{
	// Función que crea la ventana gráfica
	game_init(data);

	//Ft que permite ejecutar una ft(ft_hook) en cada iteración del loop de la mlx
	mlx_loop_hook(data->mlx, ft_hook, data);
	
	// Función que inicia el bucle de la mlx
	mlx_loop(data->mlx);

	//Ft que finaliza la conexión con la mlx y libera los recursos usados
	mlx_terminate(data->mlx);
}