/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 08:22:50 by daniel            #+#    #+#             */
/*   Updated: 2024/12/14 08:50:58 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ft para ajustar el ángulo del jugador (se usa una var de tipo souble para
angle porque ésta permite una mayor precisión en la cifra)*/
void    move_player_by_angle(t_data *data, double angle)
{
    double  move_x;
    double  move_y;

    // calcula el movimiento en x e y multiplicando el coseno 
    //y seno por la velocidad de movimiento del jugador
    move_x = (cos(angle * M_PI / 180) * data->move);
    move_y = (sin(angle * M_PI / 180) * data->move);

    // si el movimiento en y es válido, actualiza la posición en y
    if (update_move(data, 0, move_y))
        data->player.pos_y += move_y / 64;

    // si el movimiento en x es válido, actualiza la posición en x
    if (update_move(data, move_x, 0))
        data->player.pos_x += move_x / 64;
}

/* Ft para manejar los movimientos del jugador al pulsar las teclas y la
velocidad a la que éste se mueve */
void    handle_player_movement(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        move_player_by_angle(data, data->player.angle);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        move_player_by_angle(data, data->player.angle + 180);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        move_player_by_angle(data, data->player.angle - 90);
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        move_player_by_angle(data, data->player.angle + 90);
    
    // si se presiona la tecla E, el movimiento(velocidad) es 12
    if (mlx_is_key_down(data->mlx, MLX_KEY_E))
        data->move = 12;

    // si no se presiona la tecla E, el movimiento(velocidad) es 4
    if (!mlx_is_key_down(data->mlx, MLX_KEY_E))
        data->move = 4;
}

/* Ft para ajustar el ángulo del jugador */
void    adjust_angle(double *angle, double var)
{
    // aumenta o disminuye el ángulo según la variable var
    *angle += var;

    // si el ángulo es mayor a 359, lo pone a 0
    // para trabajar solo entre 0 y 360 grados
    if (*angle > 359)
        *angle = 0;

    // si el ángulo es menor a 0, lo pone a 359
    if (*angle < 0)
        *angle = 359;
}

/* Ft para manejar la rotación del jugador al pulsar las teclas. Al disminuir
el ángulo resulta en un giro a la izquierda y al aumentarlo, a la derecha */
void    handle_player_rotation(t_data *data)
{
    // si se presiona la tecla de flecha izquierda, el ángulo disminuye en 3
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        adjust_angle(&data->player.angle, -3);
    
    // si se presiona la tecla de flecha derecha, el ángulo aumenta en 3
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        adjust_angle(&data->player.angle, 3);
}