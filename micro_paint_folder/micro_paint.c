#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

typedef struct		s_info
{
	int				width;
	int				height;
	char			background;
}					t_info;

typedef struct		s_rect
{
	char			type;
	float			x;
	float			y;
	float			width;
	float			height;
	char			color;
}					t_rect;

int		put_error(char *error)
{
	int		len;
	
	len = 0;
	while (error[len])
		len++;
	write(1, error, len);
	return (0);
}

char	*get_canvas(FILE *file, t_info *info)
{
	char		*canvas;
	int			i;

	if (fscanf(file, "%d %d %c\n", &info->width, &info->height, &info->background) != 3)
		return (NULL);
	if (info->width < 0 || info->width > 300 || info->height < 0 || info->height > 300)
		return (NULL);
	if (!(canvas = malloc(info->width * info->height * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < info->width * info->height)
		canvas[i++] = info->background;
	return (canvas);
}

void	display_canvas(char *canvas, t_info info)
{
	int		i;
	int		j;

	i = 0;
	while (i < info.height)
	{
		j = 0;
		while (j < info.width)
		{
			write(1, canvas + i * info.width + j, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int		is_in_rect(int i, int j, t_rect rect)
{
	return (i >= rect.y && i <= rect.y + rect.height &&
			j >= rect.x && j <= rect.x + rect.width);
}

int		paint(FILE *file, char *canvas, t_info info)
{
	t_rect		rect;
	int			i;
	int			j;

	while (fscanf(file, "%c %f %f %f %f %c\n",
		&rect.type, &rect.x, &rect.y,
		&rect.width, &rect.height, &rect.color) == 6)
	{
		if (rect.width < 0.0 || rect.height < 0.0 || (rect.type != 'R' && rect.type != 'r'))
			return (0);
		i = 0;
		while (i < info.height)
		{
			j = 0;
			while (j < info.width)
			{
				if (rect.type == 'R')
				{
					if (is_in_rect(i, j, rect))
						canvas[i * info.width + j] = rect.color;
				}
				else if (rect.type == 'r')
				{
					if (is_in_rect(i, j, rect) &&
						(i < rect.y + 1.0 || i > rect.y + rect.height - 1.0 ||
						 j < rect.x + 1.0 || j > rect.x + rect.width - 1.0))
						canvas[i * info.width + j] = rect.color;
				}
				j++;
			}
			i++;
		}
	}
	return (1);
}


int		main(int argc, char **argv)
{
	FILE		*file;
	t_info		info;
	char		*canvas;

	if (argc != 2)
		return (!put_error("Error: argument\n"));
	if(!(file = fopen(argv[1], "r")))
		return (!put_error("Error: Operation file corrupted\n"));
	if (!(canvas = get_canvas(file, &info)))
		return (!put_error("Error: Operation file corrupted\n"));
	if (!paint(file, canvas, info))
	{
		free(canvas);
		fclose(file);
		return (!put_error("Error: Operation file corrupted\n"));
	}
	display_canvas(canvas, info);
	free(canvas);
	fclose(file);

}
