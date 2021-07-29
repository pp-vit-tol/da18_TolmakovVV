#ifndef MAP_H
# define MAP_H

# define INITIAL_MAP_SIZE 128

struct s_legend {
	unsigned int	n_lines;
	char			empty;
	char			obstacle;
	char			full;
};

struct s_map {
	unsigned int	**map;
	unsigned int	n_lines;
	size_t			line_len;
	size_t			map_size;
};

struct s_square {
	unsigned int	y;
	size_t			x;
	unsigned int	size;
};

typedef struct s_legend	t_legend;

typedef struct s_map	t_map;

typedef struct s_square	t_square;

t_map		*new_map(t_legend	*legend);

void		delete_map(t_map **map);

t_square	find_square(t_map *map);

void		calculate_map(t_map *map);

void		print_map(t_map *map, t_legend *legend, t_square square);

#endif
