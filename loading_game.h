#ifndef LOADING_GAME_H_INCLUDED
#define LOADING_GAME_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"
    #include "global_vars.h"

    struct Turn
    {
        int who;
        vector <int> way;
        Turn();
    };

    extern vector<Turn> turn;
    extern Turn last_turn_made;

    void init_field(string, Town&, Town&, vector<vector <Cell> >&);
    void color_town(int, int, int, vector<vector<Cell> >&);
    void next_turn(vector<vector<Cell> >&);
    void play_a_turn_from_file();

#endif // LOADING_GAME_H_INCLUDED
