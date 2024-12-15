/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:24:31 by daniel            #+#    #+#             */
/*   Updated: 2024/12/15 12:36:51 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* calcula la distancia vertical que un rayo ha recorrido desde el jugador 
hasta el punto de impacto con una pared, ajustando la diferencia de ángulo y 
asegurando que la distancia vertical no sea extremadamente pequeña para evitar
problemas de precisión*/
void    calculate_vertical_distance(t_data *data, t_ray *ray)
{
    double  player_angle; // para almacenar el angulo del jugador
    double  dif_angle; // para la diferencia de angulo entre jugador y rayo

    // Convierte el ángulo del jugador de grados a radianes 
    player_angle = data->player.angle * (M_PI / 180);

    // Calcula la diferencia de ángulo entre el jugador y el rayo
    dif_angle = fabs(ray->angle_ret - player_angle);

    // Si la diferencia de ángulo es mayor que PI(180 grados)
    if (dif_angle > M_PI)
        // Ajusta dif_angle restándolo de 2 * M_PI para obtener el ángulo 
        //complementario si la diferencia inicial era mayor que π.
        dif_angle = 2 * M_PI - dif_angle;

    // Calcula la dist. vert. multiplicando la distancia hipotenusa por 
    //el coseno de la dif. de angulo
    ray->ver_distance = ray->hyp_distance * cos(dif_angle);
   
    // Si la distancia vertical es extremadamente pequeña (menor que 0.0001),
    // la ajusta a un valor muy grande para evitar problemas de precisión.
    if (ray->ver_distance < 0.0001)
        // Establece la distancia vertical a un valor muy grande
        ray->ver_distance = 9999999999999.0;
}

/* traza el camino de un rayo a través de un mapa de cuadrícula, avanzando 
paso a paso en las direcciones x e y hasta que encuentra una pared. Actualiza
las distancias laterales y las posiciones del rayo en el mapa, y utiliza una 
bandera para indicar si el impacto es vertical u horizontal. Este proceso es 
fundamental para determinar la distancia desde el jugador hasta la pared más 
cercana en la dirección del rayo, lo cual es esencial para el renderizado de 
la escena en un motor de raycasting. */
void    dda_loop(t_data *data, t_ray *ray)
{
    // Mientras el rayo no haya impactado en una pared
    while (data->map.map[ray->map_y][ray->map_x] != '1')
    {
        // Si la distancia lateral en x es menor que la distancia lateral en y
        if (ray->side_dist_x < ray->side_dist_y)
        {
            // Añade la distancia lateral en x a la distancia lateral en x
            ray->side_dist_x += ray->delta_dist_x;
            // Añade el paso en x al rayo en x
            ray->map_x += ray->step_x;
            // Establece la bandera en 0
            ray->flag = 0;
        }
        // Si la distancia lateral en x es mayor o igual que la distancia lateral en y
        else
        {
            // Añade la distancia lateral en y a la distancia lateral en y
            ray->side_dist_y += ray->delta_dist_y;
            // Añade el paso en y al rayo en y
            ray->map_y += ray->step_y;
            // Establece la bandera en 1
            ray->flag = 1;
        }
    }
    // Si la flag esta en 0
    if (ray->flag == 0)
        // Calcula la distancia perpendicular entre el jugador y la pared más cercana en x
        ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    
    // Si la flag esta en 1
    else
        // Calcula la distancia perpendicular entre el jugador y la pared más cercana en y
        ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}


/* Función que calcula las distancias iniciales que un rayo debe recorrer en 
los ejes x e y para alcanzar la primera línea de cuadrícula en cada dirección,
 teniendo en cuenta la dirección del rayo y la posición actual del jugador.*/
void    calculate_side_distance(t_data *data, t_ray *ray)
{
    // Si la dirección del rayo en el eje x es positiva (hacia la derecha)
    if (ray->ray_dir_x > 0)
        //Calcula la distancia desde la posición actual del jugador hasta 
        //la próxima línea de cuadrícula en el eje x.
        ray->side_dist_x = (data->player.map_x + ray->step_x - data->player.pos_x) * ray->delta_dist_x;
    
    // Si la dirección del rayo en el eje x es negativa (hacia la izquierda)
    else
        //Calcula la distancia desde la posición actual del jugador hasta la 
        //próxima línea de cuadrícula en el eje x de manera similar, pero sin sumar el paso en x.
        ray->side_dist_x = (data->player.pos_x - data->player.map_x) * ray->delta_dist_x;
    
    // Si la dirección del rayo en el eje y es positiva (hacia arriba)
    if (ray->ray_dir_y > 0)
        //Calcula la distancia desde la posición actual del jugador hasta la
        //próxima línea de cuadrícula en el eje y.
        ray->side_dist_y = (data->player.map_y + ray->step_y - data->player.pos_y) * ray->delta_dist_y;
    
    // Si la dirección del rayo en el eje y es negativa (hacia abajo)
    else
        //Calcula la distancia desde la posición actual del jugador hasta la
        //próxima línea de cuadrícula en el eje y de manera similar, pero sin sumar el paso en y.
        ray->side_dist_y = (data->player.pos_y - data->player.map_y) * ray->delta_dist_y;
}

/* determina el punto de impacto de un rayo con una pared, maneja el impacto 
y calcula las distancias necesarias para renderizar correctamente la escena 
en el juego. */
void    find_ray_hit_pont(t_data *data, t_ray *ray)
{
    // FT que inicializa las variables del rayo
    init_ray_variables(data, ray);

    // FT que calcula la distancia lateral entre el jugador y la pared más cercana
    calculate_side_distance(data, ray);

    // FT que calcula el punto de impacto del rayo en el mapa
    dda_loop(data, ray);

    // Si el rayo impacta en una pared vertical
    if (ray->flag == 0)
    {
        ray->hit = ray->pos_y + (ray->perp_wall_dist * ray->ray_dir_y);
        ver_pixel_impact(ray); // PTE cambiar el nombre a vertical
    }
    // Si el rayo impacta en una pared horizontal
    else
    {
        ray->hit = ray->pos_x + (ray->perp_wall_dist * ray->ray_dir_x);    
        hor_pixel_impact(ray); // PTE cambiar el nombre a horizontal
    }
    // FT que calcula la distancia hipotenusa entre el jugador y la pared más cercana
    calculate_hypotenuse_distance(ray);

    // FT que calcula la distancia vertical entre el jugador y la pared más cercana
    calculate_vertical_distance(data, ray);
}

/* Ft q imprime los rayos que el jugador lanza en el juego, los cuales se 
utilizan para determinar lo que el jugador ve en la pantalla */
void    print_ray(t_data *data, t_player *player)
{
    int i;

    // Inicializa los rayos del jugador
    ray_init(data);
    i = 0;

    // Mientras el rayo no haya llegado al final (WIDTH) de la pantalla
    while (i < WIDTH)
    {
        // FT que busca el punto de impacto del rayo en el mapa
        find_ray_hit_point(data, &player->ray[i]);

        // FT que pinta la columna de la pared correspondiente al rayo en la 
        //posición i.
        print_wall_column(data, &player->ray[i], i);
        i++;
    }
}