#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include <time.h>
#include "main.h"

#define FNL_IMPL
#include "FastNoiseLite.h"

int **set_3dmap_limit(int **map, int height, int width, int lower_limit, int upper_limit)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {
            if (map[i][j] < lower_limit)
                map[i][j] = lower_limit;
            if (map[i][j] > upper_limit)
                map[i][j] = upper_limit;
        }
    }
    return map;
}

int **generate_map(int height, int width)
{
    int **map = malloc(sizeof(int *) * height);
    if (map == NULL)
        return NULL;

    for (int i = 0; i < height; i++)
    {
        map[i] = malloc(sizeof(int) * width);
        if (map[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
        for (int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }
    return map;
}

int **randomize_map(int **map, int height, int width)
{
    fnl_state noise = fnlCreateState();
    noise.seed = time(NULL);
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;

    // Gather noise data
    float* noiseData = malloc(height * width * sizeof(float));
    if (noiseData == NULL)
        return NULL;
    int index = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            noiseData[index] = fnlGetNoise2D(&noise, j, i);
            index++;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (noiseData[i * width + j] < 0)
                map[i][j] = -1;
            else
                map[i][j] = (int)(noiseData[i * width + j] * 10);
        }
    }
    free(noiseData);

    return map;
}


void print_map_3d(int **map, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

void print_map_2d(sfVector2f **map, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("(%f, %f) ", map[i][j].x, map[i][j].y);
        }
        printf("\n");
    }
}

#define ATORAD(x) (x * M_PI / 180)

static sfVector2f project_iso_point(int x, int y, int z, const sfVector2f angle, const sfVector2f translation, const int zoom) {
    sfVector2f point = {0, 0};
    x *= zoom;
    y *= zoom;
    z *= zoom;
    point.x = cos(ATORAD(angle.x)) * x - cos(ATORAD(angle.x)) * y;
    point.y = sin(ATORAD(angle.y)) * y + sin(ATORAD(angle.y)) * x - z;
    point.x += translation.x;
    point.y += translation.y;
    return point;
}


sfVector2f **allocate_2d_map(int height, int width)
{
    tileset = sfTexture_createFromFile("assets/tileset.png", NULL);
    sfVector2f **map = malloc(sizeof(sfVector2f *) * height);
    if (map == NULL)
        return NULL;
    for (int i = 0; i < height; i++)
    {
        map[i] = malloc(sizeof(sfVector2f) * width);
        if (map[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(map[j]);
            free(map);
            return NULL;
        }
        for (int j = 0; j < width; j++)
            map[i][j] = (sfVector2f){0, 0};
    }
    return map;
}

sfVector2f **create_2d_map(sfVector2f **map, int **_3dmap, int height, int width, sfVector2f angle, sfVector2f translation, int zoom)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = project_iso_point(j, i, _3dmap[i][j], angle, translation, zoom);
        }
    }
    return map;
}

sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2, sfVector2f translation)
{
    sfVertexArray *line = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};

    vertex1.position.x += translation.x;
    vertex1.position.y += translation.y;
    vertex2.position.x += translation.x;
    vertex2.position.y += translation.y;
    
    sfVertexArray_append(line, vertex1);
    sfVertexArray_append(line, vertex2);
    sfVertexArray_setPrimitiveType(line, sfLinesStrip);
    return line;
}

static int get_heighest_point(int **map, int x, int y)
{
    int heighest = map[x][y];
    if (map[x + 1][y] > heighest)
        heighest = map[x + 1][y];
    if (map[x][y + 1] > heighest)
        heighest = map[x][y + 1];
    if (map[x + 1][y + 1] > heighest)
        heighest = map[x + 1][y + 1];
    return heighest;
}

static sfConvexShape *create_convex_shape(sfVector2f **map, int x, int y, sfVector2f translation, int **_3dmap)
{
    sfConvexShape *shape = sfConvexShape_create();
    sfConvexShape_setTexture(shape, tileset, sfTrue);
    int heighest = get_heighest_point(_3dmap, x, y);

    if (shape == NULL)
        return NULL;
    sfConvexShape_setPointCount(shape, 4);
    sfConvexShape_setPoint(shape, 0, map[x][y]);
    sfConvexShape_setPoint(shape, 1, map[x + 1][y]);
    sfConvexShape_setPoint(shape, 2, map[x + 1][y + 1]);
    sfConvexShape_setPoint(shape, 3, map[x][y + 1]);
    if (heighest < 0) {
        sfConvexShape_setTextureRect(shape, (sfIntRect){64, 0, 64, 64});
    } else if (heighest < 3) {
        sfConvexShape_setTextureRect(shape, (sfIntRect){64, 64, 64, 64});
    } else if (heighest < 6)
        sfConvexShape_setTextureRect(shape, (sfIntRect){0, 64, 64, 64});
    else
        sfConvexShape_setTextureRect(shape, (sfIntRect){0, 0, 64, 64});
    return shape;
}

int draw_2d_map(sfRenderWindow *window, sfVector2f **map, int height, int width, sfVector2f translation, int **_3dmap, edit_mode_t edit_mode)
{
    sfConvexShape *shape;
    sfFloatRect bounds;
    bool click = sfMouse_isButtonPressed(sfMouseLeft);
    sfVector2i mouse_pos = {0, 0};
    if (click)
        mouse_pos = sfMouse_getPositionRenderWindow(window);

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width - 1; j++) {
            shape = create_convex_shape(map, i, j, translation, _3dmap);
            if (shape == NULL)
                return 1;
            if (click && mouse_pos.x > 300) {
                bounds = sfConvexShape_getGlobalBounds(shape);
                if (mouse_pos.x >= bounds.left && mouse_pos.x <= bounds.left + bounds.width &&
                    mouse_pos.y >= bounds.top && mouse_pos.y <= bounds.top + bounds.height) {
                    switch (edit_mode)
                    {
                    case raise_tile:
                        _3dmap[i][j] += 1;
                        _3dmap[i + 1][j] += 1;
                        _3dmap[i + 1][j + 1] += 1;
                        _3dmap[i][j + 1] += 1;
                        break;
                    case lower_tile:
                        _3dmap[i][j] -= 1;
                        _3dmap[i + 1][j] -= 1;
                        _3dmap[i + 1][j + 1] -= 1;
                        _3dmap[i][j + 1] -= 1;
                        break;
                    case reset_tile:
                        _3dmap[i][j] = 0;
                        _3dmap[i + 1][j] = 0;
                        _3dmap[i + 1][j + 1] = 0;
                        _3dmap[i][j + 1] = 0;
                        break;
                        
                    }
                }
            }

            sfRenderWindow_drawConvexShape(window, shape, NULL);
            sfConvexShape_destroy(shape);
        }
    }
    return 0;
}