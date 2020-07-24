/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomfevrier <tomfevrier@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:24:57 by tomfevrie         #+#    #+#             */
/*   Updated: 2020/07/11 16:05:04 by tomfevrie        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

char	*init_canvas(t_options options)
{
	char			*canvas;
	unsigned int	i;

	if (!(canvas = malloc(options.width * options.height)))
		return (NULL);
	i = 0;
	while (i < options.width * options.height)
		canvas[i++] = options.background_char;
	return canvas;
}

void	display_canvas(char *canvas, t_options options)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < options.height)
	{
		j = 0;
		while (j < options.width)
		{
			write(1, canvas + i * options.width + j, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	draw_circle(char *canvas, t_options options)
{
	unsigned int	i;
	unsigned int	j;
	float			dist;

	i = 0;
	while (i < options.height)
	{
		j = 0;
		while (j < options.width)
		{
			dist = sqrtf(powf(options.x - j, 2) + powf(options.y - i, 2));
			if ((options.type == 'C' && dist <= options.r) ||
				(options.type == 'c' && dist <= options.r && dist > options.r - 1))
				canvas[i * options.width + j] = options.draw_char;
			j++;
		}
		i++;
	}

}

int		main(int argc, char **argv)
{
	FILE		*file;
	t_options	options;
	char		*canvas;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	file = fopen(argv[1], "r");
	fscanf(file, "%u %u %c\n",
		&options.width, &options.height, &options.background_char);
	printf("%u %u %c\n", options.width, options.height, options.background_char);
	if (!(canvas = init_canvas(options)))
		return (1);
	// display_canvas(canvas, options);
	while (fscanf(file, "%c %f %f %f %c\n", &options.type, &options.x, &options.y,
		&options.r, &options.draw_char) != EOF)
	{
		draw_circle(canvas, options);
		//write(1, "\n", 1);
		//display_canvas(canvas, options);
	}
	display_canvas(canvas, options);
	free(canvas);
	return (0);
}
