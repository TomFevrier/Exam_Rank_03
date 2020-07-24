#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_options
{
	unsigned int	width;
	unsigned int	height;
	char			background_char;
	char			type;
	float			x;
	float			y;
	float			r;
	char			draw_char;

}					t_options;

#endif
