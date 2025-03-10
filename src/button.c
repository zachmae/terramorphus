#include <stdlib.h>
#include "button.h"

Button_t *create_button(sfVector2f pos, sfVector2f size, char *title, int (*callback)())
{
    Button_t *button = malloc(sizeof(Button_t));

    if (button == NULL)
        return NULL;
    button->rect = sfRectangleShape_create();
    button->size = size;
    sfRectangleShape_setSize(button->rect, button->size);
    button->pos = pos;
    sfRectangleShape_setPosition(button->rect, button->pos);
    button->color[COLOR_IDLE] = sfWhite;
    button->color[COLOR_HOVER] = sfRed;
    button->color[COLOR_PRESSED] = sfGreen;
    button->color[COLOR_DISABLED] = sfBlue;

    button->text = sfText_create();
    sfText_setString(button->text, title);
    sfText_setColor(button->text, sfBlack);

    button->font = sfFont_createFromFile("assets/font.ttf");
    sfText_setFont(button->text, button->font);
    sfText_setScale(button->text, (sfVector2f){0.5, 0.5});
    sfText_setPosition(button->text, button->pos);

    button->callback = callback;
    button->disabled = false;
    button->status = COLOR_IDLE;
    return button;
}

int get_button_status(sfRenderWindow *window, Button_t *button)
{  
    if (button->disabled == true) {
        button->status = COLOR_DISABLED;
        return 0;
    }
    button->status = COLOR_IDLE;
    
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
        if (mouse_pos.x >= button->pos.x && mouse_pos.x <= button->pos.x + button->size.x &&
            mouse_pos.y >= button->pos.y && mouse_pos.y <= button->pos.y + button->size.y) {
            button->status = COLOR_PRESSED;
            return 0;
        }
    }

    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    if (mouse_pos.x >= button->pos.x && mouse_pos.x <= button->pos.x + button->size.x &&
        mouse_pos.y >= button->pos.y && mouse_pos.y <= button->pos.y + button->size.y) {
        button->status = COLOR_HOVER;
        return 0;
    }
    return 0;

}


int draw_button(sfRenderWindow *window, Button_t *button)
{
    sfRectangleShape_setFillColor(button->rect, button->color[button->status]);
    if (button->status == COLOR_PRESSED) {
        button->callback();
    }

    sfRenderWindow_drawRectangleShape(window, button->rect, NULL);
    sfRenderWindow_drawText(window, button->text, NULL);
    return 0;
}