#ifndef INTELLECT_H_INCLUDED
#define INTELLECT_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"
    #include "global_vars.h"
    #include "loading_game.h"
    #include "controller.h"

    void do_intellectual_move(int);
    bool canGo(int, int, int);
    void do_intellectual_move_with_general(int);
    int priority(int, int, int);
    pii getBestCell(int);
    pii getAlmostBestCell(int);
    double priority_for_third(int x, int y, int color);

#endif // INTELLECT_H_INCLUDED
