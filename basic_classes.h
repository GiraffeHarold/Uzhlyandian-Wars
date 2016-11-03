#ifndef CLASSES_H

    #define CLASSES_H
    #include "all_includes.h"


    //void init(vector<string> name[200], map<string, Sprite>& general_sprite);
    string new_name(int);

    class Town
    {
    public:
        int x, y;
        Sprite sprite;
        Country color;


        // êîíñòðóêòîð ì³ñòà â³ä êîîðäèíàò êë³òèíêè òà êîëüîðó íàö³¿
        Town(int, int, Country);
        Town();
    };

    extern Town *town[2];

    class General
    {
    public:
        int x, y, fin_x, fin_y, turns_left, id;
        vi cur_move;
        string name;
        GLfloat add_x, add_y;
        Sprite sprite;
        Sprite killed;
        bool is_killed;
        Country color;

        int water_moving;

        General();
        General(int, Town);
        General(int, int, int, string);
        void clicked();
        void draw(ld, ld);
        queue<pair<ld, ld> > go;

        General(int, int x, int y, string name,int color,int turns_left,int);
    };

    extern int cnt_killed;
    extern General *general_chosen;

    bool operator <(const General&, const General&);

    extern multiset <General*> player_general[2];
    extern General *what_general[2][500];


    class Fort
    {
    public:
        int x, y;
        Country color;
        Sprite sprite;
        int first_color;
        bool use_partizan;

        Fort();
        // êîíñòðóêòîð â³ä ãåíåðàëà, ÿêèé ïîáóäóâàâ ôîðòåöþ
        Fort(General);
        // êîíñòðóêòîð â³ä êîîðäèíàò êë³òèíêè òà êîëüîðó íàö³¿
        Fort(int, int, Country);
        Fort(int,int,Country,int,bool);
    };

    class Cell
    {
    public:
        int x, y;
        Country color;
        General *general;
        Fort *fort;
        Town *town;
        Relief relief;

        int shined, turn_waste, water_waste;
        bool village, snow;


        // àâòîìàòè÷íèé êîíñòðóêòîð ïóñòî¿ êë³òèíêè
        Cell();

        // êîíñòðóêòîð â³ä ïîçèö³¿ ³ òèïó ðåëüºôó
        Cell(int, int, Relief);
        void draw(int, int);
    };

    extern vector<vector< Cell> > Hexes;

    class ContextMenu
    {
    public:
        int x, y, x_cell, y_cell, active_fort;
        texture fortex_button, info_button;

        ContextMenu(int, int, int, vector<vector<Cell> >&);
        void draw();
    };

    extern ContextMenu *context_menu;

#endif // CLASSES_H
