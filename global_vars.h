
#ifndef GLOBAL_VARS
    #define GLOBAL_VARS

    #include "all_includes.h"
    #include "Button.h"
    #include "basic_classes.h"

    extern bool game_with_features;
    extern std::ofstream log, buf;
    extern std::vector<std::string> name[200];
    extern GLuint fort_sprite, town_sprite[20][3], get_info_button, fortex_active, fortex_passive, menu_background;
    extern GLuint flag[10], logo, logo_team;
    extern int used_generals[200];
    extern std::map <std::string, GLuint> general_sprite;
    extern int N, M, Turns, Mode;
    extern GLuint relief_texture[10][10][3];
    extern int chosen_country[2];
    extern int width, height;
    extern std::string type_of_menu;
    extern bool is_black_fone, active_menu;
    extern std::map<std::string, Button> menu;
    extern int cursor,ramka,type,size,relief,difficulty;
    extern int width,height;
    extern std::vector<texture> start_back;
    extern std::vector<std::pair<Button,std::string>> listik;
    extern std::vector<texture> start_button;
    extern int in_main_menu;
    extern texture no_save;
    extern int curl, curr, curd, curu, pause;
    extern int pointer;
    extern int init_game_now;
    extern std::pair<int,int> moves[2][6];
    extern int player[2];
    extern bool demo, mouse_not_gen_func, mouse_gen_func, game_ending_menu;
    extern int just_moved;
    extern  std::map<std::pair<int, int>, std::vector<std::pair<long double, long double> > > vectors_for_cell;
    extern  std::map<std::pair<int, int>, std::pair<int, int> > go_to_cell;
    extern long double R;
    extern int general_moving_left;
    extern std::vector<std::string> remember1;
    extern pii score;
    extern bool pause_load_menu, set_fort_now;
    extern texture bad_line,ramka_for_score;
    extern texture village_texture[3];
    extern std :: string last[10];
    extern int loading_now;
    extern texture fone;
    extern int cur_turn;
    extern bool surrender_menu;
    extern int last_dermo;
    extern bool surrendered[2];
    extern vector<pair<int,int>> vec1;

    struct third_regime_turn
    {
        General *general;
        int x, y;
        bool must_set_a_fort;
        third_regime_turn();
        third_regime_turn(General *general, int x, int y, bool must_set_a_fort);
    };

    extern third_regime_turn cur_third_turn;

#endif // GLOBAL_VARS
