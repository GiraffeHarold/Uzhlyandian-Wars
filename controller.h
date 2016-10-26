#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"


    extern int now;

    void clear_shining();
    void control_not_general(Country q);
    void set_fort();
    void timer(int);
    void mouse_not_gen(int, int);
    void mouse_gen(int, int);
    void control_general(int);
    void general_move(pii);
    void general_move_from_file(pii);
    pii get(ld, ld, vector<vector<Cell> >&);

#endif // CONTROLLER_H_INCLUDED
