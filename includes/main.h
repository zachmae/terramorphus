/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#ifndef MAIN_H_
#define MAIN_H_

#include "csfml.h"

static const int EXIT_ERROR = 84;
static const int LOWER_LIMIT = -5;
static const int UPPER_LIMIT = 10;
static const int HEIGHT = 64;
static const int WIDTH = 64;

typedef enum {
    raise_tile,
    lower_tile,
    reset_tile,
    end
} edit_mode_t;



static sfTexture *tileset;

int live_coding(void);
int print_usage(int ac, char **av);
int error_handling(int ac, char **env);
int **generate_map(int height, int width);
int **set_3dmap_limit(int **map, int height, int width, int lower_limit, int upper_limit);
int **randomize_map(int **map, int height, int width);
sfVector2f **allocate_2d_map(int height, int width);
sfVector2f **create_2d_map(sfVector2f **map, int **_3dmap, int height, int width, sfVector2f angle, sfVector2f translation, int zoom);
int draw_2d_map(sfRenderWindow *window, sfVector2f **map, int height, int width, sfVector2f translation, int **_3dmap, edit_mode_t edit_mode);
void print_map_3d(int **map, int height, int width);
void print_map_2d(sfVector2f **map, int height, int width);

#endif /* !MAIN_H_ */
