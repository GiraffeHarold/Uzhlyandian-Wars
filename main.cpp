#include "all_includes.h"
#include "drawing.h"
#include "textures.h"
#include "basic_classes.h"
#include "loading_game.h"
#include "menu_mouse.h"
#include "draw_menu.h"
#include "Button.h"
#include "controller.h"
#include "intellect.h"
#include "map_generator.h"
#include "save_game.h"
#include "generals.h"
#include "end_game.h"
#include "pause_menu.h"
#include "Levels_intellect.h"

map<string,texture> killed_array;
General *what_general[2][500];
ofstream log("log.txt");
int player[2];
int width, height, curl, curr, curd, curu, state = -1, in_main_menu = 1, pause = 0, loading_now = 300;
int init_game_now = 0;
ld R = 100;
string type_of_menu="Start_menu";
bool is_black_fone, mouse_not_gen_func = false, mouse_gen_func = false, game_ending_menu = false;
int just_moved = 0;
map<string,Button> menu;
map<pii, vector<pair<ld, ld> > > vectors_for_cell;
map<pii, pii > go_to_cell;
multiset <General*> player_general[2];
bool game_with_features;

int cursor;
vector<texture> start_back;
vector<texture> start_button;
pair<int,int> moves[2][6] =
    {
        {
            {-1, -1}, {0, -1}, {1, -1},
            {-1, 0},          {1,  0},
                      {0, 1}
        },
        {
                      {0, -1},
            {-1 , 0},          {1,  0},
            {-1,  1}, {0,  1}, {1,  1}
        }
    };

ContextMenu *context_menu = NULL;


GLuint tex;
vector<General> Generals;
Town pl[2];
Country chosen_country[2];
GLuint relief_texture[10][10][3];

void Init();

void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    curr = w;
    curd = h;
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    init_surrender_menu();
    LoadAll();
}

void Display()
{
    if (loading_now>0)
    {
//        cerr << loading_now << "\n";
        draw_big_logotype();
        loading_now--;
        return;
    }
    if (init_game_now)
    {
        //init_field("data\\start_data.txt", pl[0], pl[1], Hexes);
        Hexes = (Mode == 1 ? generate_empty_map(size) : generate_map(size, type, relief));
        init_game_now = 0;
        give_log(log);
        if (Mode == 3)
        {
            Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
            player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
            what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
        }
        try_move_cam(state, 0, curl, curr, curd, curu);
    }

    if (in_main_menu)
        display_menu();
    else
        display_field(Hexes);

}

bool can_end_turn()
{
    for (auto q : Hexes)
        for (auto x : q)
            if (x.town != NULL && x.general != NULL) return 0;
    return (general_chosen == NULL || general_chosen -> go.empty());
}

void Keyboard(unsigned char key,int x,int y)
{
    switch (key)
    {
        case 27:
        {
            if (!in_main_menu&&!surrender_menu)
            {
                if (pause_load_menu)
                    pause_load_menu = 0; else
                pause ^= 1;
            }
            else if (surrender_menu)
            {
                pause=false;
                surrender_menu=false;
            }
            else if (type_of_menu=="Check_country"||type_of_menu=="Load_menu")
            {
                type_of_menu="Start_menu";
                all_check_clear();
            }
            else if (type_of_menu=="Settings")
            {
                type_of_menu="Check_country";
                get_remember();
                all_check_clear();
            }
            else if (type_of_menu=="Standart_maps")
            {
                type_of_menu="Settings";
                all_check_clear();
            }
            break;
        }
        case ' ':
            if (mouse_gen_func && can_end_turn())
            {
                log_generals(cur_turn%2);
                cur_turn++;

                if (game_with_features)
                {
                    /// France feature
                    if (chosen_country[cur_turn%2]==FRANCE)
                    {
                        vector<Cell*> where;
                        where.clear();
                        map<int,map<int,bool>> use;
                        use.clear();
                        for (int i=0;i<N;i++)
                            for (int j=0;j<M;j++)
                            {
                                if (Hexes[i][j].color==FRANCE)
                                    for (auto wh:moves[i%2])
                                        if (i+wh.fi>=0&&i+wh.fi<N)
                                            if (j+wh.se>=0&&j+wh.se<M)
                                                if (Hexes[i+wh.fi][j+wh.se].color==6)
                                                    if (!use[i+wh.fi][j+wh.se])
                                                        use[i+wh.fi][j+wh.se]=true,
                                                        where.pb(&Hexes[i+wh.fi][j+wh.se]);
                            }
                        bool ok=true;
                        if (where.empty())
                            ok=false;
                        if (rand()%2!=0)
                            ok=false;
                        if (ok)
                        {
                            Cell* what=where[rand()%int(where.size())];
                            what->color=FRANCE;
                        }
                    }

                    /// Germany feature
                    if (chosen_country[(cur_turn+1)%2]==GERMANY)
                    {
                        for (int i=0;i<N;i++)
                            for (int j=0;j<M;j++)
                            {
                                if (Hexes[i][j].general==NULL) continue;
                                if (Hexes[i][j].general->color!=GERMANY) continue;
                                vector<pii> where;
                                where.clear();
                                for (auto wh:moves[i%2])
                                    if (i+wh.fi>=0&&i+wh.fi<N)
                                        if (j+wh.se>=0&&j+wh.se<M)
                                            if (Hexes[i+wh.fi][j+wh.se].general!=NULL&&Hexes[i+wh.fi][j+wh.se].general->color!=GERMANY)
                                                if (Hexes[i+wh.fi][j+wh.se].fort==NULL||Hexes[i+wh.fi][j+wh.se].color==GERMANY)
                                                    if (Hexes[i+wh.fi][j+wh.se].town==NULL||Hexes[i+wh.fi][j+wh.se].color==GERMANY)
                                                        where.pb(mp(i+wh.fi,j+wh.se));
                                if (where.empty()) continue;
                                if (rand()%3!=0) continue;

                                /// And then Fuhrer say:
                                /// "KILL that whore".
                                /// General William Gott do that.
                                /// Russia will be destroyed !!!
                                /// Hail Hydra !!!
                                /// Hail Fuhrer !!!

                                pii what=where[rand()%int(where.size())];
                                player_general[cur_turn%2].erase(Hexes[what.fi][what.se].general);
                                Hexes[what.fi][what.se].general -> is_killed=true;
                                cnt_killed = 300;
                                //Hexes[what.fi][what.se].general=NULL;
                            }
                    }

                    /// Russia feature
                    if (cur_turn!=Turns*2&&chosen_country[cur_turn%2]==RUSSIA)
                    {
                        vector<pii> where;
                        where.clear();
                        for (int i=0;i<N;i++)
                            for (int j=0;j<M;j++)
                            {
                                if (Hexes[i][j].fort==NULL) continue;
                                if (Hexes[i][j].color==RUSSIA) continue;
                                if (Hexes[i][j].general!=NULL) continue;
                                if (Hexes[i][j].fort->first_color!=RUSSIA) continue;
                                if (Hexes[i][j].fort->use_partizan) continue;
                                where.pb(mp(i,j));
                        }
                        bool ok=true;
                        if (where.empty()) ok=false;
                        if (rand()%3!=0) ok=false;

                        /// And then Stalin say:
                        /// "GET UP my brother".
                        /// Marshal Zhukov do that.
                        /// Partizan get up.
                        /// Russia will win !!!
                        /// NOT
                        /// Russia will be destroyed !!!
                        /// Hail Hydra !!!
                        /// Hail Fuhrer !!!

                        if (ok)
                        {
                            pii what=where[rand()%int(where.size())];
                            Hexes[what.fi][what.se].fort->use_partizan=true;
                            Hexes[what.fi][what.se].general=new General(47,what.fi,what.se,"Partizan",RUSSIA,2,1);
                            player_general[cur_turn%2].insert(Hexes[what.fi][what.se].general);
                        }
                    }
                }
                if (cur_turn != Turns*2)
                {
                    Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
                    player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
                    if (player[cur_turn%2] == PC)
                        init_new_general(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
                    what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
                }
                renew_turns();
                general_chosen = NULL;
                clear_shining();
            }
            break;
        case 43:
            if (R < 200)
            {
                maximize();
            }
            break;
        case 45:
            if (R > max((ld)30, min((ld)width/(2*M) - 3, (ld)height/(2*N) - 3)))
            {
                R-=2;
                curl -= min((ld)M, (width/R));
                curr += min((ld)M, (width/R));
                curu -= min((ld)N, (height/R));
                curd += min((ld)N, (height/R));
                try_move_cam(state, 0, curl, curr, curd, curu);
            }
            try_move_cam(state, 0, curl, curr, curd, curu);
            break;
        case ('f'):
            if (context_menu != NULL)
            {
                if (context_menu -> active_fort)
                {
                    log << "\n" << context_menu -> x_cell + 1 << " " << context_menu -> y_cell + 1;
                    Hexes[context_menu -> x_cell][context_menu -> y_cell].fort = new Fort(context_menu -> x_cell, context_menu -> y_cell, now);
                    color_town(context_menu -> x_cell, context_menu -> y_cell, now, Hexes);
                    context_menu = NULL;
                    cur_turn++;
                    just_moved = 100;
                    if (player[cur_turn % 2] != PC) just_moved = 0;
                    clear_shining();

                    mouse_not_gen_func = 0;
                }
            }
            if (general_chosen != NULL && general_chosen -> go.empty() && general_chosen -> turns_left)
            {
                int x = general_chosen -> x, y = general_chosen -> y;
                if (!Hexes[x][y].village&&Hexes[x][y].relief == EMPTY && Hexes[x][y].fort == NULL && Hexes[x][y].town == NULL)
                {
                    Hexes[x][y].fort = new Fort(x, y, general_chosen -> color);
                    if (game_with_features && (general_chosen -> name == "Ivan_Mazepa" || general_chosen -> name == "Bohdan_Hmelnitskiy"))
                        Hexes[x][y].village = 1;
                    color_town(x, y, general_chosen -> color, Hexes);
                    player_general[cur_turn%2].erase(general_chosen);
                    log << "\n" << general_chosen -> id;
                    for (auto x : general_chosen -> cur_move)
                        log << " " << x;
                    log << " -1";
                    Hexes[x][y].general = NULL;
                    Hexes[x][y].fort->first_color=general_chosen->color;
                    general_chosen = NULL;
                    clear_shining();
                }
            }
            break;
        case 's': /// save_current_game
            save_game();
            break;
    }
}

void Mouse(int button,int state,int x,int y)
{
    if (loading_now>0) return;

    if (button!=GLUT_LEFT_BUTTON) return;

    if (in_main_menu)
    {
        if (type_of_menu=="Start_menu")
        {
            mouse_start_menu(state);
        }
        else if (type_of_menu=="Load_menu")
        {
            mouse_load_menu(state);
        }
        else if (type_of_menu=="Check_country")
        {
            mouse_check_country(state);
        }
        else if (type_of_menu=="Settings")
        {
            mouse_settings(state);
        }
        else if (type_of_menu=="Standart_maps")
        {
            mouse_standart_maps(state);
        }
    }
    else if (surrender_menu)
    {
        last_dermo=0;
        mouse_surrender_menu(state);
    }
    else if (y >= 120 || (pause))
    {
        menu["yes"].pressed=false;
        menu["no"].pressed=false;
        menu["pause22"].pressed=false;
        menu["surrender"].pressed=false;

        if (pause_load_menu)
            mouse_pause_load_menu(state);
        else if (pause)
            mouse_pause_menu(state);
        else if (game_ending_menu)
            mouse_end(state);
        else if (mouse_not_gen_func)
            mouse_not_gen(button, state);
        else if (mouse_gen_func)
            mouse_gen(button, state);
        last_dermo=0; /// by barik
    }
    else
    {
        mouse_buttons_pause(state);
    }
}

void Idle()
{

    glutPostRedisplay();
}

void Special_keyboard(int key, int x, int y)
{
    try_move_cam(state, key, curl, curr, curd, curu);
}

void Special_keyboard_up(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN || key == GLUT_KEY_UP || key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT)
        state = -1;
}



int main(int argc, char **argv)
{
    srand(time(NULL));
    freopen("debugerr.txt", "w", stderr);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Uzhlyandian Wars");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);

    glutTimerFunc(1, timer, 1);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special_keyboard);
    glutSpecialUpFunc(Special_keyboard_up);
    glutMouseFunc(Mouse);

    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);

    glutFullScreen();

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();

    return 0;
}

