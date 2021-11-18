#pragma once

#include "em.h"
#include <stdbool.h>

void menu_init();
void menu_handle_scroll(bool down);
void menu_handle_select();
// void menu_handle_event(EmEvent event);
void menu_update();
void menu_update_highscores();