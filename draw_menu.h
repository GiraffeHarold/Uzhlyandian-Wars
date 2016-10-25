#ifndef DRAW_MENU_H_INCLUDED
#define DRAW_MENU_H_INCLUDED

    #include "textures.h"
    #include "all_includes.h"
    #include "Button.h"

    void draw_background();
    void black_fone(ld);
    void draw_cursor();
    void draw_start_menu();
    void draw_start_button();
    void draw_load_menu();
    void draw_check_country_menu();
    void draw_settings();
    void draw_pause_menu();
    void draw_standart_maps();
    void draw_buttons_pause();
    void draw_surrender_menu();
    int get_current_check_turns();
    string to_string(int);

#endif // DRAW_MENU_H_INCLUDED
