#include "controller.h"
#include "loading_game.h"
#include "intellect.h"
#include "drawing.h"
#include "end_game.h"
#include "hard_intellect.h"

GLuint flag[10];
int now, where = 0;
pii asked_for_menu;
bool active_menu = false;
General *general_chosen = NULL;
pii _where = {-1, -1}, score;

bool can_not_make_a_turn(int color)
{
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (Hexes[i][j].color == color)
            {
                if (Hexes[i][j].relief == EMPTY && Hexes[i][j].fort == NULL && Hexes[i][j].town == NULL) return 0;
                for (auto x : moves[i])
                {
                    int nx = i + x.fi, ny = j + x.se;
                    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
                    if (Hexes[nx][ny].relief == EMPTY && Hexes[nx][ny].fort == NULL && Hexes[nx][ny].town == NULL) return 0;
                }
            }
    return 1;
}

void timer(int val)
{
//    cerr << cur_turn << " " << Turns << " " << mouse_not_gen_func << " " << mouse_gen_func << "\n";
    if (!in_main_menu && !pause && demo) next_turn(Hexes);
    if (Turns && cur_turn >= 2 * Turns)
    {
        display_field(Hexes);
        end_game();
        glutTimerFunc(1, timer, 1);
        return;
    }
    if (set_fort_now)
    {
//        cerr << "!\n";
        set_fort();
    }
    if (general_chosen != NULL && !general_chosen -> go.empty() && !pause)
    {
        general_chosen -> add_x += general_chosen -> go.front().fi * R/100;
        general_chosen -> add_y += general_chosen -> go.front().se * R/100;
        general_chosen -> go.pop();
        //cerr << general_chosen -> add_x << " " << general_chosen -> add_y << " " << general_chosen -> go.front().fi << " !\n";
        if (general_chosen -> go.empty())
        {
            //cerr << general_chosen -> fin_x << " " << general_chosen -> fin_y << " " << general_chosen -> x << " " << general_chosen -> y << "\n";
            int x = general_chosen -> x;
            int y = general_chosen -> y;
            int fin_x = general_chosen -> fin_x;
            int fin_y = general_chosen -> fin_y;

            general_chosen -> cur_move.pb(go_to_cell[mp(fin_x, fin_y)].fi);
            if (go_to_cell[mp(fin_x, fin_y)].se != 0)
                general_chosen -> cur_move.pb(go_to_cell[mp(fin_x, fin_y)].se);

            Hexes[fin_x][fin_y].general = Hexes[x][y].general;
            Hexes[x][y].general = NULL;
            general_chosen -> x = general_chosen -> fin_x;
            general_chosen -> y = general_chosen -> fin_y;
            general_chosen -> add_x = 0;
            general_chosen -> add_y = 0;
            if (set_fort_now)
                set_fort();
            //general_chosen -> turns_left -= Hexes[x][y].turn_waste - Hexes[x][y].water_waste;
            //general_chosen -> water_moving -= Hexes[x][y].water_waste;
            //cerr << general_chosen -> turns_left << " " << general_chosen -> water_moving << " " << Hexes[x][y].turn_waste << "\n";
            general_chosen = NULL;
            clear_shining();

        }
    }
    if (!in_main_menu && !demo && !just_moved && !(general_chosen != NULL && !general_chosen -> go.empty()))
    {
//        cerr << Mode << " ";
//        cerr << cur_turn << " " << player[0] << " " << player[1] << "\n";
        if (Mode != 3)
        {

            if (player[cur_turn%2] == HUMAN)
            {
                control_not_general(chosen_country[cur_turn%2]);
            } else
            {
                mouse_not_gen_func = false;
                do_intellectual_move(chosen_country[cur_turn%2]);
            }
        } else
        {
            if (player[cur_turn%2] == HUMAN)
            {
                control_general(chosen_country[cur_turn%2]);
            } else
            {
                mouse_gen_func = false;
                do_intellectual_move_with_general(chosen_country[cur_turn%2]);
            }
        }
    }
    if (!pause) just_moved = max(just_moved - 1, 0);
    glutTimerFunc(1, timer, 1);
}


void buftimer(int val)
{
    just_moved--;
    if (!just_moved)
        glutTimerFunc(1, timer, 1);
    else glutTimerFunc(1, buftimer, 1);
}

void set_fort()
{
//    cerr << "setting\n";
//    cerr << (general_chosen == NULL) << "\n";
    int x = general_chosen -> x, y = general_chosen -> y;
//    cerr << x << " " << y << "\n";

    if (!Hexes[x][y].village && Hexes[x][y].relief == EMPTY && Hexes[x][y].fort == NULL && Hexes[x][y].town == NULL)
    {
        Hexes[x][y].fort = new Fort(x, y, general_chosen -> color);
        Hexes[x][y].fort->first_color=general_chosen->color;
//        cerr << "setted\n";
        color_town(x, y, general_chosen -> color, Hexes);
        player_general[cur_turn%2].erase(general_chosen);
        log << general_chosen -> id;
        for (auto x : general_chosen -> cur_move)
            log << " " << x;
        log << " -1";
//        cerr << "logged\n";
        Hexes[x][y].general = NULL;
        general_chosen = NULL;
        chosen_to_build[x][y] = 0;
        clear_shining();
//        cerr << "cleaned\n";
    }
}

void control_not_general(Country q)
{
    now = q;
    mouse_not_gen_func = true;
}

void control_general(Country q)
{
    now = q;
    mouse_gen_func = true;
}


void do_context(int where, vector<vector <Cell> >& Hexes)
{
    if (where == -1) context_menu = NULL, clear_shining();
    if (where == 1 && context_menu -> active_fort)
    {
        log << context_menu -> x_cell + 1 << " " << context_menu -> y_cell + 1 << "\n";
        Hexes[context_menu -> x_cell][context_menu -> y_cell].fort = new Fort(context_menu -> x_cell, context_menu -> y_cell, now);
        color_town(context_menu -> x_cell, context_menu -> y_cell, now, Hexes);
        context_menu = NULL;
        cur_turn++;
        just_moved = 100;
        if (player[cur_turn % 2] != PC) just_moved = 0;
        clear_shining();

        mouse_not_gen_func = 0;
    }
    if (where == 2)
    {
        context_menu = NULL;
        clear_shining();
    }
}

ld eps_barika=1e-10;

ld sqr(ld a)
{
    return a*a;
}

ld dist(ld x1,ld y1,ld x2,ld y2)
{
    return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

ld area(ld a,ld b,ld c)
{
    ld p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

ld area(ld x1,ld y1,ld x2,ld y2,ld x3,ld y3)
{
    ld a=dist(x1,y1,x2,y2);
    ld b=dist(x1,y1,x3,y3);
    ld c=dist(x2,y2,x3,y3);
    return area(a,b,c);
}

bool in(ld c_x,ld c_y,ld R,ld xx,ld yy)
{
    ld pi=acos(-1);

    vector<pair<ld,ld>> vec;
    vec.clear();
    vec.pb(mp(c_x-R,c_y));
    vec.pb(mp(c_x-R/2,c_y-R*cos(pi/6)));
    vec.pb(mp(c_x+R/2,c_y-R*cos(pi/6)));
    vec.pb(mp(c_x+R,c_y));
    vec.pb(mp(c_x+R/2,c_y+R*cos(pi/6)));
    vec.pb(mp(c_x-R/2,c_y+R*cos(pi/6)));

    #define fir first
    #define sec second

    ld sum_s=0;
    for (int i=0;i<(int)vec.size();i++)
    {
        ld cur=area(vec[i].fir,vec[i].sec,vec[(i+1)%6].fir,vec[(i+1)%6].sec,xx,yy);
        //if (cur<eps_barika) return false;
        sum_s+=cur;
    }
    return abs(sum_s-3*cos(pi/6)*R*R)<1e-3;
}

pair<int,int> get(ld xx, ld yy, vector<vector<Cell>>& a)
{
    //swap(xx, yy);
    for (int i=0;i<(int)a.size();i++)
        for (int j=0;j<(int)a[i].size();j++)
        {
            ld r=R,r_=R*cos(PI/6);
            ld c_x=1.25*r+1.5*(r-2.5)*a[i][j].x-curl;
            ld c_y = 120 + (a[i][j].x%2) * R_ + R_ + (2*a[i][j].y) * R_ - curu;
            //cerr << i << " " << j << "   " << c_x << " " << c_y << "    " << xx << " " << yy << " " << in(c_x, c_y, r, xx, yy) << "\n";
            if (in(c_x,c_y,r,xx,yy)) return mp(i,j);
        }
    return mp(-1,-1); ///no pak! ya nichoho ne nashov
}

int ask_where(int x, int y)
{
    ContextMenu cur = *context_menu;
    pii now = get(x, y, Hexes);
    //cerr << cur.x_cell << " " << cur.y_cell << "  " << now.fi << " " << now.se << "\n";
    if (now.fi == cur.x_cell && now.se == cur.y_cell)
        return 1;
    else return -1;
}

void push_menu(int x, int y)
{
    pair <int, int> q = get(x, y, Hexes);
    if (q.fi != -1)
    {
        context_menu = new ContextMenu(q.fi, q.se, now, Hexes);
        Hexes[q.fi][q.se].shined = 1 + context_menu -> active_fort;
    }
}

void mouse_not_gen(int button, int state)
{
    POINT mouse;
    GetCursorPos(&mouse);
    int x = mouse.x;
    int y = mouse.y;
    //cout << x << " " << y << "\n";
    if (button == GLUT_LEFT_BUTTON)
    {
        if (context_menu != NULL)
        {
            if (state == GLUT_DOWN)
                where = ask_where(x, y);
            if (state == GLUT_UP && where)
                if (ask_where(x, y) == where)
                    do_context(where, Hexes);
        } else
        {
            if (state == GLUT_DOWN)
            {
                asked_for_menu = get(x, y, Hexes);
            }
            else if (get(x, y, Hexes) == asked_for_menu) push_menu(x, y);
        }
    }
}

void clear_shining()
{
    for (int i=0; i<Hexes.size(); i++)
        for (int j=0; j<Hexes[i].size(); j++)
            Hexes[i][j].shined = 0,
            Hexes[i][j].turn_waste = 0,
            Hexes[i][j].water_waste = 0;
}

void general_move(pair <int, int> where)
{
    if (where.fi == -1)
    {
        general_chosen = NULL;
        clear_shining();
    }
    Cell *cur = &Hexes[where.fi][where.se];
    if (cur -> shined == 0)
    {
        general_chosen = NULL;
        clear_shining();
    } else
    {
        for (auto q : vectors_for_cell[where])
            general_chosen -> go.push(q);
        general_chosen -> fin_x = where.fi;
        general_chosen -> fin_y = where.se;
        int fin_x = general_chosen -> fin_x, fin_y = general_chosen -> fin_y;
        general_chosen -> turns_left -= Hexes[fin_x][fin_y].turn_waste + Hexes[fin_x][fin_y].water_waste;
        general_chosen -> water_moving += Hexes[fin_x][fin_y].water_waste;
        general_moving_left = vectors_for_cell[where].size();
    }
}

void mouse_gen(int button, int state)
{
    if (general_chosen != NULL && !general_chosen -> go.empty())
        return;
    POINT mouse;
    GetCursorPos(&mouse);
    int x = mouse.x;
    int y = mouse.y;
    if (button == GLUT_LEFT_BUTTON)
    {
        //cerr << _where.fi << " " << _where.se << " " << x << " " << y << "\n";
        if (general_chosen != NULL)
        {
            if (state == GLUT_DOWN)
                _where = get(x, y, Hexes);
            if (state == GLUT_UP && _where == get(x, y, Hexes) && _where.fi != -1)
                general_move(_where);
        } else
        {
            if (state == GLUT_DOWN)
                _where = get(x, y, Hexes);
            if (state == GLUT_UP && _where.fi != -1 && _where == get(x, y, Hexes))
                if (Hexes[_where.fi][_where.se].general != NULL && Hexes[_where.fi][_where.se].general -> color == cur_country)
                {
                    general_chosen = Hexes[_where.fi][_where.se].general;
                    general_chosen -> clicked();
                }
        }
    }
}
