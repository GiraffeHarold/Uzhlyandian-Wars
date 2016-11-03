#ifndef HARD_INTELLECT_H_INCLUDED
#define HARD_INTELLECT_H_INCLUDED

    #include "global_vars.h"

    #define DEFENCE 0
    #define ATTACK 1
    #define BUILDER 2

    struct Squad
    {
        int type, moving;
        vector <General*> members;
        pii build_here;

        int size();
        void add(General*);
        void move();
        void move_builder();
        void move_attack();
        void move_defence();
        void convert(int);

        Squad(int);
        Squad();
    };

    void init_distance(int);
    bool can_set(General*, int, int);
    void createMove(General*, pii, bool);

    extern bool chosen_to_build[100][100];
    extern vector <third_regime_turn> moveNow;
    extern vector <Squad*> ourSquads;
    extern map <General*, Squad*> whatSquad;
#endif // HARD_INTELLECT_H_INCLUDED
