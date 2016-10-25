#ifndef LEVELS_INTELLECT_H_INCLUDED
#define LEVELS_INTELLECT_H_INCLUDED

    #include "all_includes.h"
    #include "drawing.h"
    #include "textures.h"
    #include "basic_classes.h"
    #include "loading_game.h"
    #include "menu_mouse.h"
    #include "draw_menu.h"
    #include "Button.h"
    #include "controller.h"
    #include "intellect.h"
    #include "map_generator.h"
    #include "end_game.h"

    pii Easy(int, int);
    pii Medium(int, int);
    pii Hard(int, int);
    void init_new_general(General*);
    bool goodThird(int);
#endif // LEVELS_INTELLECT_H_INCLUDED
