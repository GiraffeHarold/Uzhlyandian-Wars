#include "pause_menu.h"
#include "global_vars.h"
#include "draw_menu.h"
#include "Button.h"
#include "loading_game.h"
#include "save_game.h"
#include "menu_mouse.h"
#include "hard_intellect.h"

void get_back_to_game()
{
    menu["back_to_game(pause)"].pressed=false;
    menu["save_game(pause)"].pressed=false;
    menu["load(pause)"].pressed=false;
    menu["back_to_main_menu(pause)"].pressed=false;
    menu["exit(pause)"].pressed=false;
    all_check_clear();
    pause ^= 1;
}

void get_back_to_main_menu()
{
    game_ending_menu = false;
    all_check_clear();
    in_main_menu = true;
    Hexes.clear();
    player[0] = -1;
    player[1] = -1;

    player_general[0].clear();
    player_general[1].clear();
    cur_turn = 0;
    pause = 0;
    R = 100;
    for (int i=0; i<10; i++)
        last[i] = "";
    general_chosen = NULL;
    just_moved = 0;
    general_moving_left = 0;
    type_of_menu = "Start_menu";
    mouse_gen_func = 0;
    mouse_not_gen_func = 0;
    ourSquads.clear();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            chosen_to_build[i][j] = 0;
}

void mouse_pause_menu(int state)
{
    if (state==GLUT_DOWN)
    {
        if (menu["back_to_game(pause)"].on_click())
            menu["back_to_game(pause)"].pressed=true;
        if (menu["save_game(pause)"].on_click())
            menu["save_game(pause)"].pressed=true;
        if (menu["load(pause)"].on_click())
            menu["load(pause)"].pressed=true;
        if (menu["back_to_main_menu(pause)"].on_click())
            menu["back_to_main_menu(pause)"].pressed=true;
        if (menu["exit(pause)"].on_click())
            menu["exit(pause)"].pressed=true;
    }
    if (state==GLUT_UP)
    {
        if (!(menu["back_to_game(pause)"].pressed&&menu["back_to_game(pause)"].on_click()))
        if (!(menu["save_game(pause)"].pressed&&menu["save_game(pause)"].on_click()))
        if (!(menu["load(pause)"].pressed&&menu["load(pause)"].on_click()))
        if (!(menu["back_to_main_menu(pause)"].pressed&&menu["back_to_main_menu(pause)"].on_click()))
        if (!(menu["exit(pause)"].pressed&&menu["exit(pause)"].on_click()))
        {
            menu["back_to_game(pause)"].pressed=false;
            menu["save_game(pause)"].pressed=false;
            menu["load(pause)"].pressed=false;
            menu["back_to_main_menu(pause)"].pressed=false;
            menu["exit(pause)"].pressed=false;
        }

        bool ok=false;

        if (menu["back_to_game(pause)"].pressed)
        {
            get_back_to_game();
        }
        if (menu["save_game(pause)"].pressed)
        {
            save_game();
            get_back_to_game();
        }
        if (menu["load(pause)"].pressed)
        {
            //init_remember1();
            init_listik();
            pause_load_menu=true;
        }
        if (menu["back_to_main_menu(pause)"].pressed)
        {
            get_back_to_main_menu();
        }
        if (menu["exit(pause)"].pressed)
        {
            exit(0);
            /// and not get back !!!
        }
        menu["back_to_game(pause)"].pressed=false;
        menu["save_game(pause)"].pressed=false;
        menu["load(pause)"].pressed=false;
        menu["back_to_main_menu(pause)"].pressed=false;
        menu["exit(pause)"].pressed=false;
    }
}

void draw_pause_menu()
{
    black_fone(0.9);
    menu["back_to_game(pause)"].draw(!pause_load_menu);
    menu["save_game(pause)"].draw(!pause_load_menu);
    menu["load(pause)"].draw(!pause_load_menu);
    menu["back_to_main_menu(pause)"].draw(!pause_load_menu);
    menu["exit(pause)"].draw(!pause_load_menu);
}
