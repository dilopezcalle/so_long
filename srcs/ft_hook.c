/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 07:47:09 by dilopez-          #+#    #+#             */
/*   Updated: 2022/07/05 14:16:31 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdio.h>

int	ft_press_key(int key, void *param)
{
	t_program	*program;
	int			move;
	int			x;
	int			y;

	program = (t_program *)param;
	move = 0;
	x = program->sprite_position.x / 64;
	y = program->sprite_position.y / 64;
	if (key == 0 && ((program->map)->ber)[y][x - 1] != '1' && ++move)
		program->sprite_position.x -= program->sprite.size.x;
	else if (key == 1 && ((program->map)->ber)[y + 1][x] != '1' && ++move)
		program->sprite_position.y += program->sprite.size.y;
	else if (key == 2 && ((program->map)->ber)[y][x + 1] != '1' && ++move)
		program->sprite_position.x += program->sprite.size.x;
	else if (key == 13 && ((program->map)->ber)[y - 1][x] != '1' && ++move)
		program->sprite_position.y -= program->sprite.size.y;
	else if (key == 53)
		ft_exit_program(program);
	if (!move)
		return (0);
	ft_upgrade_sprites(program, x, y);
	return (0);
}

void	ft_upgrade_sprites(t_program *program, int x, int y)
{
	mlx_put_image_to_window(program->mlx, program->window.reference, \
							program->floor.reference, x * 64, y * 64);
	if (((program->map)->ber)[y][x] == 'C')
		(program->coins)--;
	if (((program->map)->ber)[y][x] == 'E')
		mlx_put_image_to_window(program->mlx, program->window.reference, \
								program->exit.reference, x * 64, y * 64);
	else
		((program->map)->ber)[y][x] = 0;
	printf("Movement: %d\n", ++(program->movements));
	mlx_put_image_to_window(program->mlx, program->window.reference, \
			program->sprite.reference, program->sprite_position.x, \
			program->sprite_position.y);
	if (((program->map)->ber)[program->sprite_position.y / 64]
		[program->sprite_position.x / 64] == 'E' && program->coins == 0)
		ft_exit_program(program);
}
