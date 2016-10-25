#include "all_includes.h"
#include "basic_classes.h"
#include "global_vars.h"
#include "generals.h"

std::vector<std::string> name[200];
GLuint fort_sprite, town_sprite[20][3];
vector <vector <Cell > > Hexes;
int used_generals[200];
map <string, GLuint> general_sprite;
int N, M, Turns, Mode;

/// ìåòîä äëÿ ãåíåðàö³¿ íàñòóïíîãî ãåíåðàëà ³ç ñïèñêó

/// êëàñ ì³ñòà
Town :: Town() {}

Town :: Town(int x, int y, Country color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = town_sprite[color][0];
}

/// êëàñ ãåíåðàëà
General :: General() {}

General :: General(int id, Town town)
{
    this->id = id;
    this->cur_move = *new vi(0);
    this->x = town.x;
    this->y = town.y;
    this->water_moving = 1;
    this->add_x = 0;
    this->add_y = 0;
    this->color = town.color;
    this->name = next_gen(x, y, color) -> name;
    this->sprite = general_sprite[this->name];
    this->turns_left = 2;
}

General :: General(int id, int x, int y, string name)
{
    this->id = id;
    this->cur_move = *new vi(0);
    this->x = x;
    this->y = y;
    this->water_moving = 1;
    this->color = NONE;
    this->name = name;
    this->sprite = general_sprite[this->name];
    this->add_x = 0;
    this->add_y = 0;
    this->turns_left = 2;
}

General :: General(int id, int x, int y, string name,int color,int turns_left,int water_moving)
{
    this->id = id;
    this->cur_move = *new vi(0);
    this->x = x;
    this->y = y;
    this->water_moving = 1;
    this->add_x = 0;
    this->add_y = 0;
    this->color = color;
    this->name = name;
    this->sprite = general_sprite[this->name];
    this->turns_left = turns_left;
    this->water_moving = water_moving;

}

bool operator < (const General& q, const General& w)
{
    return (q.x < w.x || (q.x == w.x && q.y < w.y));
}

/// êëàñ ôîðòåö³
Fort :: Fort() {}

Fort :: Fort(General gen)
{
    this->x = gen.x;
    this->y = gen.y;
    this->color = gen.color;
    this->sprite = fort_sprite;
    this->first_color=6;
    this->use_partizan=false;
    // TODO: çíèùóâàòè ãåíåðàëà ï³ñëÿ ïîáóäîâè ôîðòåö³
}

// êîíñòðóêòîð â³ä êîîðäèíàò êë³òèíêè òà êîëüîðó íàö³¿
Fort :: Fort(int x, int y, Country color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = fort_sprite;
    this->first_color=6;
    this->use_partizan=false;
}

Fort :: Fort(int x,int y,Country color,int first_color,bool use_partizan)
{
    this->x=x;
    this->y=y;
    this->color=color;
    this->first_color=first_color;
    this->use_partizan=use_partizan;
    this->sprite = fort_sprite;
}

/// êëàñ êë³òèíêè


Cell :: Cell()
{
    this->color = NONE;
    this->general = NULL;
    this->fort = NULL;
    this->town = NULL;
    this->x = 0;
    this->y = 0;
    this->relief = EMPTY;
    this->shined = 0;
    this->turn_waste = 0;
    this->water_waste = 0;
    this->village=false;
    this->snow=false;
}

Cell :: Cell(int x, int y, Relief q)
{
    this->color = NONE;
    this->general = NULL;
    this->fort = NULL;
    this->town = NULL;
    this->x = x;
    this->y = y;
    this->relief = q;
    this->shined = 0;
    this->turn_waste = 0;
    this->water_waste = 0;
    this->village=false;
    this->snow=false;
}

ContextMenu :: ContextMenu(int x_, int y_, int col, vector<vector<Cell> >& Hexes)
{
    active_fort = 0;
    for (int i=0; i<6; i++)
    {
        int nx = x_ + moves[x_%2][i].fi, ny = y_ + moves[x_%2][i].se;
        if (nx >= 0 && nx < N && ny >= 0 && ny < M)
        {
            if (Hexes[nx][ny].color == col) active_fort = 1;
        }
    }
    if (Hexes[x_][y_].color == col) active_fort = 1;
    if (Hexes[x_][y_].relief != EMPTY || Hexes[x_][y_].town != NULL || Hexes[x_][y_].fort != NULL) active_fort = 0;
    if (active_fort) fortex_button = fortex_active;
        else fortex_button = fortex_passive;
    info_button = get_info_button;
    ld r = R, r_ = cos(PI/6) * r;
    x = 1.25 * r + 1.5 * (r - 2.5) * x_ - curl;
    y = (x_%2) * r_ + r + (2*y_) * r_ - curu - 100;
    x_cell = x_;
    y_cell = y_;
}

