/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** button
*/

#ifndef BUTTON_H_
    #define BUTTON_H_

    #include "csfml.h"
    #include <stdbool.h>

typedef enum {
    COLOR_IDLE,
    COLOR_HOVER,
    COLOR_PRESSED,
    COLOR_DISABLED
} ButtonColorType;

typedef struct Button_s{
    sfRectangleShape *rect;
    sfColor color[4];
    int status;
    bool disabled;
    sfText *text;
    sfFont *font;
    sfVector2f pos;
    sfVector2f size;
    int (*callback)();
} Button_t;

Button_t *create_button(sfVector2f pos, sfVector2f size, char *title, int (*callback)());
int get_button_status(sfRenderWindow *window, Button_t *button);
int draw_button(sfRenderWindow *window, Button_t *button);

#endif /* !BUTTON_H_ */
