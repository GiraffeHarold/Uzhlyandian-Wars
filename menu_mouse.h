#ifndef MENU_MOUSE_H_INCLUDED
#define MENU_MOUSE_H_INCLUDED

    #include "all_includes.h"
    extern int last_menu;

    void start_play_game();
    void all_check_clear();
    void mouse_start_menu(int state);
    void mouse_check_country(int state);
    void mouse_settings(int state);
    void mouse_load_menu(int state);
    void mouse_pause_menu(int state);
    void mouse_pause_load_menu(int state);
    void mouse_standart_maps(int state);
    void mouse_buttons_pause(int state);
    void mouse_surrender_menu(int state);
    bool I_check_all();
    void get_remember();
    void remember_it();

#endif // MENU_MOUSE_H_INCLUDED
