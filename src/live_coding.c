#include <stdio.h>
#include <stdlib.h>
#include "csfml.h"
#include "button.h"
#include "main.h"

static sfVector2f angle = {45, 35};
static sfVector2f translation = {300, 300};
int zoom = 64;

edit_mode_t edit_mode = raise_tile;

static void disable_edit_mode(Button_t **button_array, edit_mode_t edit_mode)
{
    if (edit_mode == raise_tile) {
        button_array[10]->disabled = true;
        button_array[11]->disabled = false;
        button_array[12]->disabled = false;
    }
    if (edit_mode == lower_tile) {
        button_array[10]->disabled = false;
        button_array[11]->disabled = true;
        button_array[12]->disabled = false;
    }
    if (edit_mode == reset_tile) {
        button_array[10]->disabled = false;
        button_array[11]->disabled = false;
        button_array[12]->disabled = true;
    }
}

int set_raise_tile()
{
    edit_mode = raise_tile;
    return 0;
}

int set_lower_tile()
{
    edit_mode = lower_tile;
    return 0;
}

int set_reset_tile()
{
    edit_mode = reset_tile;
    return 0;
}

int zoom_in()
{
    zoom += 1;
    return 0;
}

int zoom_out()
{
    zoom -= 1;
    return 0;
}

int translate_up()
{
    translation.y -= 1;
    return 0;
}

int translate_down()
{
    translation.y += 1;
    return 0;
}

int translate_left()
{
    translation.x -= 1;
    return 0;
}

int translate_right()
{
    translation.x += 1;
    return 0;
}

int rotate_left()
{
    angle.x -= 1;
    return 0;
}

int rotate_right()
{
    angle.x += 1;
    return 0;
}

int rotate_up()
{
    angle.y -= 1;
    return 0;
}

int rotate_down()
{
    angle.y += 1;
    return 0;
}

Button_t **set_all_buttons()
{
    Button_t **button_array = malloc(sizeof(Button_t *) * 14);
    button_array[0] = create_button((sfVector2f){100, 400}, (sfVector2f){100, 100}, "Up ^^", &translate_up);
    button_array[1] = create_button((sfVector2f){100, 500}, (sfVector2f){100, 100}, "Down v", &translate_down);
    button_array[2] = create_button((sfVector2f){0, 500}, (sfVector2f){100, 100}, "Left <", &translate_left);
    button_array[3] = create_button((sfVector2f){200, 500}, (sfVector2f){100, 100}, "Right >", &translate_right);
    button_array[4] = create_button((sfVector2f){0, 700}, (sfVector2f){100, 100}, "Rotate\nLeft", &rotate_left);
    button_array[5] = create_button((sfVector2f){200, 700}, (sfVector2f){100, 100}, "Rotate\nRight", &rotate_right);
    button_array[6] = create_button((sfVector2f){100, 600}, (sfVector2f){100, 100}, "Rotate\nUp", &rotate_up);
    button_array[7] = create_button((sfVector2f){100, 800}, (sfVector2f){100, 100}, "Rotate\nDown", &rotate_down);
    button_array[8] = create_button((sfVector2f){0, 400}, (sfVector2f){100, 100}, "Zoom\nIn", &zoom_in);
    button_array[9] = create_button((sfVector2f){200, 400}, (sfVector2f){100, 100}, "Zoom\nOut", &zoom_out);
    button_array[10] = create_button((sfVector2f){0, 0}, (sfVector2f){100, 100}, "Raise\nTile", &set_raise_tile);
    button_array[11] = create_button((sfVector2f){100, 0}, (sfVector2f){100, 100}, "Lower\nTile", &set_lower_tile);
    button_array[12] = create_button((sfVector2f){200, 0}, (sfVector2f){100, 100}, "Reset\nTile", &set_reset_tile);
    button_array[13] = NULL;
    return button_array;
}

void update_all_buttons(sfRenderWindow *window, Button_t **button_array)
{
    for (int i = 0; button_array[i] != NULL; i++) {
        get_button_status(window, button_array[i]);
    }
}

void draw_all_buttons(sfRenderWindow *window, Button_t **button_array)
{
    for (int i = 0; button_array[i] != NULL; i++) {
        draw_button(window, button_array[i]);
    }
}

void save_map(int **map, int height, int width)
{
    FILE *file = fopen("save.legend", "w");
    if (file == NULL)
        return;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(file, "%d", map[i][j]);
            if (j < width - 1)
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void load_map(int **map, int height, int width)
{
    FILE *file = fopen("save.legend", "r");
    if (file == NULL)
        return;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            fscanf(file, "%d", &map[i][j]);
    fclose(file);
}

int live_coding(void) {
    sfRenderWindow *window;
    sfVideoMode mode = {1200, 900, 32};
    window = sfRenderWindow_create(mode, "Live Coding", sfResize | sfClose, NULL);
    Button_t **button_array = set_all_buttons();
    sfEvent event;
    sfRectangleShape *leftOverlay = sfRectangleShape_create();
    sfRectangleShape_setSize(leftOverlay, (sfVector2f){300, 900});
    sfRectangleShape_setFillColor(leftOverlay, sfColor_fromRGB(50, 50, 50));
    sfSprite *logo = sfSprite_create();
    sfTexture *logo_texture = sfTexture_createFromFile("assets/terramorphus-logo.png", NULL);
    sfSprite_setTexture(logo, logo_texture, sfTrue);
    sfSprite_setPosition(logo, (sfVector2f){0, 100});
    sfSprite_setScale(logo, (sfVector2f){0.29, 0.29});
    
    sfRenderWindow_setFramerateLimit(window, 60);
    int **map = generate_map(WIDTH, HEIGHT);
    tileset = sfTexture_createFromFile("assets/tileset.png", NULL);
    sfVector2f **map_2d = allocate_2d_map(WIDTH, HEIGHT);
    if (!map || !map_2d || !window || !button_array || !tileset)
        return 1;

    map_2d = create_2d_map(map_2d, map, HEIGHT, WIDTH, angle, translation, zoom);
    printf("Press space to randomize the map\n");

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) sfRenderWindow_close(window);
            if (sfKeyboard_isKeyPressed(sfKeySpace))
                map = randomize_map(map, HEIGHT, WIDTH);
            if (sfKeyboard_isKeyPressed(sfKeyR)) {
                angle.x = 45;
                angle.y = 35;
                translation.x = 300;
                translation.y = 300;
                zoom = 64;
                for (int i = 0; i < HEIGHT; i++) {
                    for (int j = 0; j < WIDTH; j++) map[i][j] = 0;
                }
            }
            if (sfKeyboard_isKeyPressed(sfKeyS))
                save_map(map, HEIGHT, WIDTH);
            if (sfKeyboard_isKeyPressed(sfKeyL))
                load_map(map, HEIGHT, WIDTH);
            if (sfKeyboard_isKeyPressed(sfKeyUp))
                translate_up();
            if (sfKeyboard_isKeyPressed(sfKeyDown))
                translate_down();
            if (sfKeyboard_isKeyPressed(sfKeyLeft))
                translate_left();
            if (sfKeyboard_isKeyPressed(sfKeyRight))
                translate_right();
            if (event.type == sfEvtMouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    zoom_in();
                if (event.mouseWheelScroll.delta < 0)
                    zoom_out();
            }

        }
        angle.x = angle.x > 360 ? 0 : angle.x;
        angle.y = angle.y > 90 ? 90 : angle.y;
        angle.x = angle.x < 0 ? 360 : angle.x;
        angle.y = angle.y < 0 ? 0 : angle.y;
        zoom = zoom < 1 ? 1 : zoom;
        
        button_array[9]->disabled = zoom <= 1 ? true : false;
        button_array[6]->disabled = angle.y <= 1 ? true : false;
        button_array[7]->disabled = angle.y >= 89 ? true : false;
        
        disable_edit_mode(button_array, edit_mode);
        sfRenderWindow_clear(window, sfBlack);
        set_3dmap_limit(map, HEIGHT, WIDTH, LOWER_LIMIT, UPPER_LIMIT);
        create_2d_map(map_2d, map, HEIGHT, WIDTH, angle, translation, zoom);
        draw_2d_map(window, map_2d, HEIGHT, WIDTH, translation, map, edit_mode);
        sfRenderWindow_drawRectangleShape(window, leftOverlay, NULL);
        update_all_buttons(window, button_array);
        draw_all_buttons(window, button_array);
        sfRenderWindow_drawSprite(window, logo, NULL);
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < HEIGHT; i++) {
        free(map_2d[i]);
        free(map[i]);
    }
    free(map_2d);
    free(map);
    sfSprite_destroy(logo);
    sfTexture_destroy(logo_texture);
    sfRectangleShape_destroy(leftOverlay);
    sfTexture_destroy(tileset);
    sfRenderWindow_destroy(window);
    return 0;

}