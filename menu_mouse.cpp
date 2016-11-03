#include "menu_mouse.h"
#include "textures.h"
#include "save_game.h"
#include "drawing.h"
#include "save_game.h"
#include "draw_menu.h"
#include "map_generator.h"
#include "end_game.h"
#include "loading_game.h"
#include "hard_intellect.h"

int last_menu;
int last_check;
int last_load;
int last_standart;
vector<string> last_checked={"","small","mainland","mountainous","first"};
vector<string> last_checked1={"","","","","","",""};
string last_checked2;
map<string,Button> remember;
int type,size,relief,difficulty;
int pointer;
bool pause_load_menu=false;
bool surrender_menu=false;

void remember_it()
{
    remember=menu;
}

void get_remember()
{
    menu=remember;
}

void all_check_clear()
{
    /*menu["usa1"].pressed=false;
    menu["france1"].pressed=false;
    menu["england1"].pressed=false;
    menu["ukraine1"].pressed=false;
    menu["germany1"].pressed=false;
    menu["russia1"].pressed=false;

    menu["usa2"].pressed=false;
    menu["france2"].pressed=false;
    menu["england2"].pressed=false;
    menu["ukraine2"].pressed=false;
    menu["germany2"].pressed=false;
    menu["russia2"].pressed=false;*/

    menu["start"].pressed=false;
    menu["cancel"].pressed=false;

    /*
    menu["player_vs_player"].pressed=false;
    menu["player_vs_pc"].pressed=false;

    menu["but1"].pressed=false;
    menu["but2"].pressed=false;
    menu["but3"].pressed=false;
    */

    /*menu["small"].pressed=true;
    menu["medium"].pressed=false;
    menu["big"].pressed=false;
    menu["giant"].pressed=false;

    menu["mainland"].pressed=true;
    menu["continents"].pressed=false;
    menu["islands"].pressed=false;

    menu["mountainous"].pressed=true;
    menu["piedmont"].pressed=false;
    menu["plain"].pressed=false;

    menu["first"].pressed=true;
    menu["second"].pressed=false;
    menu["third"].pressed=false;*/

    //last_checked={"","small","mainland","mountainous","first"};
    //last_checked1={"","","","","","",""};

    /*last_check=0;
    last_menu=0;
    last_load=0;*/

    pointer=0;

    for (auto &i:listik)
        i.first.pressed=false;

    menu["save_load"].pressed=false;
    menu["cancel2"].pressed=false;

    menu["back_to_game(pause)"].pressed=false;
    menu["save_game(pause)"].pressed=false;
    menu["load(pause)"].pressed=false;
    menu["back_to_main_menu(pause)"].pressed=false;
    menu["exit(pause)"].pressed=false;

    pause_load_menu=false;

    menu["point"].pressed=false;

    menu["Earth"].pressed=false;
    menu["BigBattle"].pressed=false;
    menu["Caribians"].pressed=false;
    menu["Gorge"].pressed=false;
    menu["Snake"].pressed=false;

    menu["start3"].pressed=false;
    menu["cancel3"].pressed=false;

    last_checked2="";

    menu["yes"].pressed=false;
    menu["no"].pressed=false;
    menu["pause22"].pressed=false;
    menu["surrender"].pressed=false;
}

void mouse_empty_load_menu(int state)
{
    if (state==GLUT_DOWN)
    {
        if (menu["play_dermo"].on_click())
            menu["play_dermo"].pressed=true;
        if (menu["cancel2"].on_click())
            menu["cancel2"].pressed=true;
    }
    if (state==GLUT_UP)
    {
        if (menu["cancel2"].pressed&&!menu["cancel2"].on_click())
            menu["cancel2"].pressed=false;

        if (menu["play_dermo"].pressed&&!menu["play_dermo"].on_click())
            menu["play_dermo"].pressed=false;

        if (menu["cancel2"].pressed)
        {
            menu["cancel2"].pressed=false;
            type_of_menu="Start_menu";
        }

        if (menu["play_dermo"].pressed)
        {
            menu["play_dermo"].pressed=false;
            play_a_turn_from_file();
            //exit(0);
        }
    }
}

void mouse_empty_pause_load_menu(int state)
{
    if (state==GLUT_DOWN)
        if (menu["cancel2"].on_click())
            menu["cancel2"].pressed=true;
    if (state==GLUT_UP)
    {
        if (menu["cancel2"].pressed&&!menu["cancel2"].on_click())
            menu["cancel2"].pressed=false;
        if (menu["cancel2"].pressed)
        {
            menu["cancel2"].pressed=false;
            pause_load_menu=false;
        }
    }
}

void mouse_load_menu(int state)
{
    if (listik.size()==0)
        return void(mouse_empty_load_menu(state));

    if (state==GLUT_DOWN)
    {
        bool prec_ok=false;
        for (auto i:listik)
            prec_ok|=(i.first.pressed);


        bool ok;

        ok=false;

        for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
            ok|=listik[i].first.on_click();

        if (ok)
        {
            for (auto &i:listik)
                i.first.pressed=false;
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                listik[i].first.click();
            last_load=1;
        }
        else if (listik.size()>4&&pointer!=0&&menu["arrow_up"].on_click())
        {
            menu["arrow_up"].pressed=true;
            last_load=2;
        }
        else if (listik.size()>4&&pointer+4!=listik.size()&&menu["arrow_down"].on_click())
        {
            menu["arrow_down"].pressed=true;
            last_load=3;
        }
        else if (prec_ok&&menu["save_load"].on_click())
        {
            menu["save_load"].pressed=true;
            last_load=4;
        }
        else if (menu["cancel2"].on_click())
        {
            menu["cancel2"].pressed=true;
            last_load=5;
        }
        else if (prec_ok&&menu["delete"].on_click())
        {
            menu["delete"].pressed=true;
            last_load=6;
        }
        else if (menu["play_dermo"].on_click())
        {
            menu["play_dermo"].pressed=true;
            last_load=7;
        }
        else last_load=0;
    }

    if (state==GLUT_UP)
    {
        if (last_load==0) return;

        bool ok;

        ok=true;

        for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
            ok&=(!(listik[i].first.pressed&&listik[i].first.on_click()));

        if (last_load==1)
        if (ok)
        {
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                listik[i].first.pressed=false;
        }

        if (last_load==2)
        if (!(menu["arrow_up"].pressed&&menu["arrow_up"].on_click()))
        {
            menu["arrow_up"].pressed=false;
        }

        if (last_load==3)
        if (!(menu["arrow_down"].pressed&&menu["arrow_down"].on_click()))
        {
            menu["arrow_down"].pressed=false;
        }

        if (last_load==4)
        if (!(menu["save_load"].pressed&&menu["save_load"].on_click()))
        {
            menu["save_load"].pressed=false;
        }

        if (last_load==5)
        if (!(menu["cancel2"].pressed&&menu["cancel2"].on_click()))
        {
            menu["cancel2"].pressed=false;
        }

        if (last_load==6)
        if (!(menu["delete"].pressed&&menu["delete"].on_click()))
        {
            menu["delete"].pressed=false;
        }

        if (last_load==7)
        if (!(menu["play_dermo"].pressed&&menu["play_dermo"].on_click()))
        {
            menu["play_dermo"].pressed=false;
        }

        if (menu["play_dermo"].pressed)
        {
            menu["play_dermo"].pressed=false;
            ourSquads.clear();
            play_a_turn_from_file();
            //exit(0);
        }

        if (menu["delete"].pressed)
        {
            menu["delete"].pressed=false;
            delete_pressed_file();
        }

        if (menu["arrow_down"].pressed)
        {
            menu["arrow_down"].pressed=false;
            pointer=min(pointer+1,int(listik.size())-4);
        }

        if (menu["arrow_up"].pressed)
        {
            menu["arrow_up"].pressed=false;
            pointer=max(pointer-1,0);
        }

        if (menu["cancel2"].pressed)
        {
            menu["cancel2"].pressed=false;
            all_check_clear();
            type_of_menu="Start_menu";
        }

        if (menu["save_load"].pressed)
        {
            menu["save_load"].pressed=false;
            string res="bleat";
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                if (listik[i].first.pressed)
                    res=listik[i].second;
            load_game(res);
            in_main_menu = 0;
            init_game_now = 0;
            ourSquads.clear();
            if (player[1] == PC)
                for (int i=0; i<N; i++)
                    for (int j=0; j<M; j++)
                    {
                        if (Hexes[i][j].general && Hexes[i][j].general -> color == chosen_country[1])
                        {
                            ourSquads.push_back(new Squad(BUILDER));
                            ourSquads.back() -> add(Hexes[i][j].general);
                        }
                    }
            try_move_cam(state,0,curl,curr,curd,curu);
            all_check_clear();
        }
    }
}

void mouse_start_menu(int state)
{
    if (state==GLUT_DOWN)
    {
        menu["play"].click();
        menu["load"].click();
        menu["quit"].click();
    }

    if (state==GLUT_UP)
    {
        if (menu["play"].pressed&&menu["play"].click())
        {
            type_of_menu="Check_country";
            all_check_clear();
            last_menu=0;
            is_black_fone=true;
        }
        else if (menu["load"].pressed&&menu["load"].click())
        {
            type_of_menu="Load_menu";
            //init_remember1();
            init_listik();
        }
        else if (menu["quit"].pressed&&menu["quit"].click()) exit(0);
        else
        {
            menu["play"].pressed=false;
            menu["load"].pressed=false;
            menu["quit"].pressed=false;
        }
    }
}

bool check_bad_line()
{
    Button dop=Button(200.0*width/1366,600.0*height/768,500.0*width/1366,50.0*height/768,-1,-1,-1);
    if (dop.on_click()) return true;
    return false;
}

void mouse_settings(int state)
{
    if (state==GLUT_DOWN)
    {
        if (menu["small"].on_click()||menu["medium"].on_click()||menu["big"].on_click()||menu["giant"].on_click())
        {
            menu["small"].pressed=false;
            menu["medium"].pressed=false;
            menu["big"].pressed=false;
            menu["giant"].pressed=false;
            menu["small"].click();
            menu["medium"].click();
            menu["big"].click();
            menu["giant"].click();
            last_check=1;
        }
        else if ((!menu["but1"].pressed)&&(menu["mainland"].on_click()||menu["continents"].on_click()||(!menu["but2"].pressed&&menu["islands"].on_click())))
        {
            menu["mainland"].pressed=false;
            menu["continents"].pressed=false;
            menu["islands"].pressed=false;
            menu["mainland"].click();
            menu["continents"].click();
            menu["islands"].click();
            last_check=2;
        }
        else if ((!menu["but1"].pressed)&&(menu["mountainous"].on_click()||menu["piedmont"].on_click()||menu["plain"].on_click()))
        {
            menu["mountainous"].pressed=false;
            menu["piedmont"].pressed=false;
            menu["plain"].pressed=false;
            menu["mountainous"].click();
            menu["piedmont"].click();
            menu["plain"].click();
            last_check=3;
        }
        else if ((!menu["player_vs_player"].pressed)&&(menu["first"].on_click()||menu["second"].on_click()||menu["third"].on_click()))
        {
            menu["first"].pressed=false;
            menu["second"].pressed=false;
            menu["third"].pressed=false;
            menu["first"].click();
            menu["second"].click();
            menu["third"].click();
            last_check=4;
        }
        else if (menu["cancel1"].on_click())
        {
            menu["cancel1"].click();
            last_check=5;
        }
        else if (menu["save"].on_click())
        {
            menu["save"].click();
            last_check=6;
        }
        else if (check_bad_line())
        {
            menu["point"].pressed=true;
            last_check=0;
        }
        else if (menu["game_with_features"].on_all_click())
        {
            last_check=7;
        }
        else if (menu["Standart_maps"].on_click())
        {
            menu["Standart_maps"].click();
            last_check=8;
        }
        else last_check=0;
    }

    if (state==GLUT_UP)
    {
        menu["point"].pressed=false;
        if (last_check==0) return;

        bool ok;

        ok=false;

        if (last_check==1)
        if (!(menu["small"].pressed&&menu["small"].on_click()))
        if (!(menu["medium"].pressed&&menu["medium"].on_click()))
        if (!(menu["big"].pressed&&menu["big"].on_click()))
        if (!(menu["giant"].pressed&&menu["giant"].on_click()))
        {
            menu["small"].pressed=false;
            menu["medium"].pressed=false;
            menu["big"].pressed=false;
            menu["giant"].pressed=false;
            menu[last_checked[1]].pressed=true;
            ok=true;
        }
        if (!ok)
        {
            if (menu["small"].pressed) last_checked[1]="small";
            if (menu["medium"].pressed) last_checked[1]="medium";
            if (menu["big"].pressed) last_checked[1]="big";
            if (menu["giant"].pressed) last_checked[1]="giant";
        }

        ok=false;

        if (last_check==2)
        if (!(menu["mainland"].pressed&&menu["mainland"].on_click()))
        if (!(menu["continents"].pressed&&menu["continents"].on_click()))
        if (!(menu["islands"].pressed&&menu["islands"].on_click()))
        {
            menu["mainland"].pressed=false;
            menu["continents"].pressed=false;
            menu["islands"].pressed=false;
            menu[last_checked[2]].pressed=true;
            ok=true;
        }
        if (!ok)
        {
            if (menu["mainland"].pressed) last_checked[2]="mainland";
            if (menu["continents"].pressed) last_checked[2]="continents";
            if (menu["islands"].pressed) last_checked[2]="islands";
        }

        ok=false;

        if (last_check==3)
        if (!(menu["mountainous"].pressed&&menu["mountainous"].on_click()))
        if (!(menu["piedmont"].pressed&&menu["piedmont"].on_click()))
        if (!(menu["plain"].pressed&&menu["plain"].on_click()))
        {
            menu["mountainous"].pressed=false;
            menu["piedmont"].pressed=false;
            menu["plain"].pressed=false;
            menu[last_checked[3]].pressed=true;
            ok=true;
        }
        if (!ok)
        {
            if (menu["mountainous"].pressed) last_checked[3]="mountainous";
            if (menu["piedmont"].pressed) last_checked[3]="piedmont";
            if (menu["plain"].pressed) last_checked[3]="plain";
        }

        ok=false;

        if (last_check==4)
        if (!(menu["first"].pressed&&menu["first"].on_click()))
        if (!(menu["second"].pressed&&menu["second"].on_click()))
        if (!(menu["third"].pressed&&menu["third"].on_click()))
        {
            menu["first"].pressed=false;
            menu["second"].pressed=false;
            menu["third"].pressed=false;
            menu[last_checked[4]].pressed=true;
            ok=true;
        }
        if (!ok)
        {
            if (menu["first"].pressed) last_checked[4]="first";
            if (menu["second"].pressed) last_checked[4]="second";
            if (menu["third"].pressed) last_checked[4]="third";
        }

        if (last_check==5)
        if (!(menu["cancel1"].pressed&&menu["cancel1"].on_click()))
        {
            menu["cancel1"].pressed=false;
        }

        if (last_check==6)
        if (!(menu["save"].pressed&&menu["save"].on_click()))
        {
            menu["save"].pressed=false;
        }

        if (last_check==7)
        if (!menu["player_vs_pc"].pressed)
        if (menu["game_with_features"].on_all_click())
        {
            menu["game_with_features"].all_click();
        }

        if (last_check==8)
        if (!(menu["Standart_maps"].pressed&&menu["Standart_maps"].on_click()))
        {
            menu["Standart_maps"].pressed=false;
        }

        if (menu["cancel1"].pressed)
        {
            get_remember();
            menu["cancel1"].pressed=false;
            type_of_menu="Check_country";
        }

        if (menu["Standart_maps"].pressed)
        {
            type_of_menu="Standart_maps";
            menu["Standart_maps"].pressed=false;
        }

        if (menu["save"].pressed)
        {
            menu["save"].pressed=false;
            type_of_menu="Check_country";
        }
    }
}

void mouse_check_country(int state)
{

    if (state==GLUT_DOWN)
    {
        if (menu["usa1"].on_click()||menu["france1"].on_click()||menu["england1"].on_click()||menu["ukraine1"].on_click()||menu["germany1"].on_click()||menu["russia1"].on_click())
        {
            if (menu["usa2"].pressed&&menu["usa1"].on_click()) return void(last_menu=0);
            if (menu["france2"].pressed&&menu["france1"].on_click()) return void(last_menu=0);
            if (menu["england2"].pressed&&menu["england1"].on_click()) return void(last_menu=0);
            if (menu["ukraine2"].pressed&&menu["ukraine1"].on_click()) return void(last_menu=0);
            if (menu["germany2"].pressed&&menu["germany1"].on_click()) return void(last_menu=0);
            if (menu["russia2"].pressed&&menu["russia1"].on_click()) return void(last_menu=0);
            menu["usa1"].pressed=false;
            menu["france1"].pressed=false;
            menu["england1"].pressed=false;
            menu["ukraine1"].pressed=false;
            menu["germany1"].pressed=false;
            menu["russia1"].pressed=false;
            menu["usa1"].click();
            menu["france1"].click();
            menu["england1"].click();
            menu["ukraine1"].click();
            menu["germany1"].click();
            menu["russia1"].click();
            last_menu=1;
        }
        else if (menu["usa2"].on_click()||menu["france2"].on_click()||menu["england2"].on_click()||menu["ukraine2"].on_click()||menu["germany2"].on_click()||menu["russia2"].on_click())
        {
            if (menu["usa1"].pressed&&menu["usa2"].on_click()) return void(last_menu=0);
            if (menu["france1"].pressed&&menu["france2"].on_click()) return void(last_menu=0);
            if (menu["england1"].pressed&&menu["england2"].on_click()) return void(last_menu=0);
            if (menu["ukraine1"].pressed&&menu["ukraine2"].on_click()) return void(last_menu=0);
            if (menu["germany1"].pressed&&menu["germany2"].on_click()) return void(last_menu=0);
            if (menu["russia1"].pressed&&menu["russia2"].on_click()) return void(last_menu=0);
            menu["usa2"].pressed=false;
            menu["france2"].pressed=false;
            menu["england2"].pressed=false;
            menu["ukraine2"].pressed=false;
            menu["germany2"].pressed=false;
            menu["russia2"].pressed=false;
            menu["usa2"].click();
            menu["france2"].click();
            menu["england2"].click();
            menu["ukraine2"].click();
            menu["germany2"].click();
            menu["russia2"].click();
            last_menu=2;
        }
        else if (menu["player_vs_player"].on_click()||menu["player_vs_pc"].on_click())
        {
            menu["player_vs_player"].pressed=false;
            menu["player_vs_pc"].pressed=false;
            menu["player_vs_player"].click();
            menu["player_vs_pc"].click();
            last_menu=3;
        }
        else if (menu["start"].on_click())
        {
            menu["start"].click();
            last_menu=4;
        }
        else if (menu["cancel"].on_click())
        {
            menu["cancel"].click();
            last_menu=5;
        }
        else if (menu["but1"].on_click()||menu["but2"].on_click()||menu["but3"].on_click())
        {
            menu["but1"].pressed=false;
            menu["but2"].pressed=false;
            menu["but3"].pressed=false;
            menu["but1"].click();
            menu["but2"].click();
            menu["but3"].click();
            last_menu=6;
        }
        else if (menu["settings"].on_click())
        {
            menu["settings"].pressed=true;
            last_menu=7;
        }
        else last_menu=0;
    }

    if (state==GLUT_UP)
    {
        if (last_menu==0) return;

        bool ok;

        ok=false;

        if (last_menu==1)
        if (!(menu["usa1"].pressed&&menu["usa1"].on_click()))
        if (!(menu["france1"].pressed&&menu["france1"].on_click()))
        if (!(menu["england1"].pressed&&menu["england1"].on_click()))
        if (!(menu["ukraine1"].pressed&&menu["ukraine1"].on_click()))
        if (!(menu["germany1"].pressed&&menu["germany1"].on_click()))
        if (!(menu["russia1"].pressed&&menu["russia1"].on_click()))
        {
            menu["usa1"].pressed=false;
            menu["france1"].pressed=false;
            menu["england1"].pressed=false;
            menu["ukraine1"].pressed=false;
            menu["germany1"].pressed=false;
            menu["russia1"].pressed=false;
            ok=true;
            menu[last_checked1[1]].pressed=true;
        }
        if (!ok)
        {
            if (menu["usa1"].pressed) last_checked1[1]="usa1";
            if (menu["france1"].pressed) last_checked1[1]="france1";
            if (menu["england1"].pressed) last_checked1[1]="england1";
            if (menu["ukraine1"].pressed) last_checked1[1]="ukraine1";
            if (menu["germany1"].pressed) last_checked1[1]="germany1";
            if (menu["russia1"].pressed) last_checked1[1]="russia1";
        }

        ok=false;

        if (last_menu==2)
        if (!(menu["usa2"].pressed&&menu["usa2"].on_click()))
        if (!(menu["france2"].pressed&&menu["france2"].on_click()))
        if (!(menu["england2"].pressed&&menu["england2"].on_click()))
        if (!(menu["ukraine2"].pressed&&menu["ukraine2"].on_click()))
        if (!(menu["germany2"].pressed&&menu["germany2"].on_click()))
        if (!(menu["russia2"].pressed&&menu["russia2"].on_click()))
        {
            menu["usa2"].pressed=false;
            menu["france2"].pressed=false;
            menu["england2"].pressed=false;
            menu["ukraine2"].pressed=false;
            menu["germany2"].pressed=false;
            menu["russia2"].pressed=false;
            ok=true;
            menu[last_checked1[2]].pressed=true;
        }
        if (!ok)
        {
            if (menu["usa2"].pressed) last_checked1[2]="usa2";
            if (menu["france2"].pressed) last_checked1[2]="france2";
            if (menu["england2"].pressed) last_checked1[2]="england2";
            if (menu["ukraine2"].pressed) last_checked1[2]="ukraine2";
            if (menu["germany2"].pressed) last_checked1[2]="germany2";
            if (menu["russia2"].pressed) last_checked1[2]="russia2";
        }

        ok=false;

        if (last_menu==3)
        if (!(menu["player_vs_player"].pressed&&menu["player_vs_player"].on_click()))
        if (!(menu["player_vs_pc"].pressed&&menu["player_vs_pc"].on_click()))
        {
            menu["player_vs_player"].pressed=false;
            menu["player_vs_pc"].pressed=false;
            ok=true;
            menu[last_checked1[3]].pressed=true;
        }

        if (menu["player_vs_pc"].pressed)
            menu["game_with_features"].pressed=false;

        if (!ok)
        {
            if (menu["player_vs_player"].pressed) last_checked1[3]="player_vs_player";
            if (menu["player_vs_pc"].pressed) last_checked1[3]="player_vs_pc";
        }

        if (last_menu==4)
        if (!(menu["start"].pressed&&menu["start"].on_click()))
        {
            menu["start"].pressed=false;
        }

        if (last_menu==5)
        if (!(menu["cancel"].pressed&&menu["cancel"].on_click()))
        {
            menu["cancel"].pressed=false;
        }

        ok=false;

        if (last_menu==6)
        if (!(menu["but1"].pressed&&menu["but1"].on_click()))
        if (!(menu["but2"].pressed&&menu["but2"].on_click()))
        if (!(menu["but3"].pressed&&menu["but3"].on_click()))
        {
            menu["but1"].pressed=false;
            menu["but2"].pressed=false;
            menu["but3"].pressed=false;
            ok=true;
            menu[last_checked1[6]].pressed=true;
        }
        if (!ok)
        {
            if (menu["but1"].pressed) last_checked1[6]="but1";
            if (menu["but2"].pressed) last_checked1[6]="but2";
            if (menu["but3"].pressed) last_checked1[6]="but3";
        }

        if (last_menu==7)
        if (!(menu["settings"].pressed&&menu["settings"].on_click()))
        {
            menu["settings"].pressed=false;
        }

        if (menu["start"].pressed)
        {
            start_play_game();
        }

        if (menu["cancel"].pressed)
        {
            type_of_menu="Start_menu";
            is_black_fone=false;
        }

        if (menu["settings"].pressed)
        {
            menu["settings"].pressed=false;
            remember_it();
            type_of_menu="Settings";
        }

        if (menu["but2"].pressed)
            if (menu["islands"].pressed)
            {
                menu["islands"].pressed=false;
                menu["mainland"].pressed=true;
            }
    }
}

///-------------------------------------------

void start_play_game()
{
//    cerr << "\n\nSTARTED NEW GAME\n";

    game_ending_menu = false;
    if (menu["usa1"].pressed) chosen_country[0] = USA;
    if (menu["ukraine1"].pressed) chosen_country[0] = UKRAINE;
    if (menu["russia1"].pressed) chosen_country[0] = RUSSIA;
    if (menu["germany1"].pressed) chosen_country[0] = GERMANY;
    if (menu["france1"].pressed) chosen_country[0] = FRANCE;
    if (menu["england1"].pressed) chosen_country[0] = ENGLAND;

    if (menu["usa2"].pressed) chosen_country[1] = USA;
    if (menu["ukraine2"].pressed) chosen_country[1] = UKRAINE;
    if (menu["russia2"].pressed) chosen_country[1] = RUSSIA;
    if (menu["germany2"].pressed) chosen_country[1] = GERMANY;
    if (menu["france2"].pressed) chosen_country[1] = FRANCE;
    if (menu["england2"].pressed) chosen_country[1] = ENGLAND;

    if (menu["player_vs_player"].pressed) player[1] = HUMAN;
    if (menu["player_vs_pc"].pressed) player[1] = PC;
    player[0] = HUMAN;


    cnt_killed = 0;
//    cout << "Players: " << player[0] << " " << player[1] << "\n";
    cur_turn = 0;
    log.clear();

    if(menu["but1"].pressed) Mode = 1;
    else if(menu["but2"].pressed) Mode = 2;
    else Mode = 3;

    if (menu["small"].pressed) size = SMALL;
    if (menu["medium"].pressed) size = MIDDLE;
    if (menu["big"].pressed) size = LARGE;
    if (menu["giant"].pressed) size = GREAT;

    if (menu["mainland"].pressed) type = MAINLAND;
    if (menu["continents"].pressed) type = CONTINENTS;
    if (menu["islands"].pressed) type = ISLANDS;

    if (menu["mountainous"].pressed) relief = MOUNTIANOUS;
    if (menu["piedmont"].pressed) relief = PIEDMONT;
    if (menu["plain"].pressed) relief = VALLEY;

    if (menu["first"].pressed) difficulty = EASY;
    if (menu["second"].pressed) difficulty = MEDIUM;
    if (menu["third"].pressed) difficulty = HARD;

    game_with_features=menu["but3"].pressed&&menu["game_with_features"].pressed;

    Turns = get_current_check_turns();

    in_main_menu = 0;
    init_game_now = 1;
    all_check_clear();
}

///-------------------------------------------

void mouse_pause_load_menu(int state)
{
    if (listik.size()==0)
        return void(mouse_empty_pause_load_menu(state));

    if (state==GLUT_DOWN)
    {
        bool prec_ok=false;
        for (auto i:listik)
            prec_ok|=(i.first.pressed);


        bool ok;

        ok=false;

        for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
            ok|=listik[i].first.on_click();

        if (ok)
        {
            for (auto &i:listik)
                i.first.pressed=false;
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                listik[i].first.click();
            last_load=1;
        }
        else if (listik.size()>4&&pointer!=0&&menu["arrow_up"].on_click())
        {
            menu["arrow_up"].pressed=true;
            last_load=2;
        }
        else if (listik.size()>4&&pointer+4!=listik.size()&&menu["arrow_down"].on_click())
        {
            menu["arrow_down"].pressed=true;
            last_load=3;
        }
        else if (prec_ok&&menu["save_load"].on_click())
        {
            menu["save_load"].pressed=true;
            last_load=4;
        }
        else if (menu["cancel2"].on_click())
        {
            menu["cancel2"].pressed=true;
            last_load=5;
        }
        else if (prec_ok&&menu["delete"].on_click())
        {
            menu["delete"].pressed=true;
            last_load=6;
        }
        else last_load=0;
    }

    if (state==GLUT_UP)
    {
        if (last_load==0) return;

        bool ok;

        ok=true;

        for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
            ok&=(!(listik[i].first.pressed&&listik[i].first.on_click()));

        if (last_load==1)
        if (ok)
        {
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                listik[i].first.pressed=false;
        }

        if (last_load==2)
        if (!(menu["arrow_up"].pressed&&menu["arrow_up"].on_click()))
        {
            menu["arrow_up"].pressed=false;
        }

        if (last_load==3)
        if (!(menu["arrow_down"].pressed&&menu["arrow_down"].on_click()))
        {
            menu["arrow_down"].pressed=false;
        }

        if (last_load==4)
        if (!(menu["save_load"].pressed&&menu["save_load"].on_click()))
        {
            menu["save_load"].pressed=false;
        }

        if (last_load==5)
        if (!(menu["cancel2"].pressed&&menu["cancel2"].on_click()))
        {
            menu["cancel2"].pressed=false;
        }

        if (last_load==6)
        if (!(menu["delete"].pressed&&menu["delete"].on_click()))
        {
            menu["delete"].pressed=false;
        }

        if (menu["delete"].pressed)
        {
            menu["delete"].pressed=false;
            delete_pressed_file();
        }

        if (menu["arrow_down"].pressed)
        {
            menu["arrow_down"].pressed=false;
            pointer=min(pointer+1,int(listik.size())-4);
        }

        if (menu["arrow_up"].pressed)
        {
            menu["arrow_up"].pressed=false;
            pointer=max(pointer-1,0);
        }

        if (menu["cancel2"].pressed)
        {
            menu["cancel2"].pressed=false;
            all_check_clear();
            pause_load_menu = 0;
        }

        if (menu["save_load"].pressed)
        {
            menu["save_load"].pressed=false;
            string res="bleat";
            for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
                if (listik[i].first.pressed)
                    res=listik[i].second;
            load_game(res);
            in_main_menu = 0;
            pause = 0;
            init_game_now = 0;
            ourSquads.clear();
            if (player[1] == PC)
                for (int i=0; i<N; i++)
                    for (int j=0; j<M; j++)
                    {
                        if (ourSquads.empty())
                            ourSquads.push_back(new Squad(DEFENCE));
                        if (Hexes[i][j].general && Hexes[i][j].general -> color == chosen_country[1])
                        {
                            ourSquads.push_back(new Squad(BUILDER));
                            ourSquads.back() -> add(Hexes[i][j].general);
                        }
                    }
            all_check_clear();
            try_move_cam(state,0,curl,curr,curd,curu);
        }
    }
}

bool I_check_all()
{
    bool is_check1=false;
    bool is_check2=false;
    bool is_check3=false;
    bool is_check4=false;

    is_check1|=menu["usa1"].pressed;
    is_check2|=menu["usa2"].pressed;

    is_check1|=menu["france1"].pressed;
    is_check2|=menu["france2"].pressed;

    is_check1|=menu["england1"].pressed;
    is_check2|=menu["england2"].pressed;

    is_check1|=menu["ukraine1"].pressed;
    is_check2|=menu["ukraine2"].pressed;

    is_check1|=menu["germany1"].pressed;
    is_check2|=menu["germany2"].pressed;

    is_check1|=menu["russia1"].pressed;
    is_check2|=menu["russia2"].pressed;

    is_check3|=menu["player_vs_player"].pressed;
    is_check3|=menu["player_vs_pc"].pressed;

    is_check4|=menu["but1"].pressed;
    is_check4|=menu["but2"].pressed;
    is_check4|=menu["but3"].pressed;

    if (!is_check1) return false;
    if (!is_check2) return false;
    if (!is_check3) return false;
    if (!is_check4) return false;
    return true;
}

void mouse_standart_maps(int state)
{
    if (state==GLUT_DOWN)
    {
        string g="bleat";
        if (menu["Earth"].pressed) g="Earth";
        if (menu["BigBattle"].pressed) g="BigBattle";
        if (menu["Caribians"].pressed) g="Caribians";
        if (menu["Gorge"].pressed) g="Gorge";
        if (menu["Snake"].pressed) g="Snake";

        if ((menu["Earth"].on_click()&&menu["but3"].pressed&&menu["game_with_features"].pressed)||menu["BigBattle"].on_click()||(menu["Caribians"].on_click()&&menu["but3"].pressed&&menu["game_with_features"].pressed)||menu["Gorge"].on_click()||menu["Snake"].on_click())
        {
            menu["Earth"].pressed=false;
            menu["BigBattle"].pressed=false;
            menu["Caribians"].pressed=false;
            menu["Gorge"].pressed=false;
            menu["Snake"].pressed=false;

            menu["Earth"].click();
            menu["BigBattle"].click();
            menu["Caribians"].click();
            menu["Gorge"].click();
            menu["Snake"].click();
            last_standart=1;
        }
        else if (menu["start3"].on_click()&&g!="bleat"&&I_check_all())
        {
            menu["start3"].pressed=true;
            last_standart=2;
        }
        else if (menu["cancel3"].on_click())
        {
            menu["cancel3"].pressed=true;
            last_standart=3;
        }
        else last_standart=0;
    }
    if (state==GLUT_UP)
    {
        string g="bleat";
        if (menu["Earth"].pressed) g="Earth";
        if (menu["BigBattle"].pressed) g="BigBattle";
        if (menu["Caribians"].pressed) g="Caribians";
        if (menu["Gorge"].pressed) g="Gorge";
        if (menu["Snake"].pressed) g="Snake";

        bool ok=false;

        if (last_standart==1)
        if (!(menu["Earth"].pressed&&menu["Earth"].on_click()))
        if (!(menu["BigBattle"].pressed&&menu["BigBattle"].on_click()))
        if (!(menu["Caribians"].pressed&&menu["Caribians"].on_click()))
        if (!(menu["Gorge"].pressed&&menu["Gorge"].on_click()))
        if (!(menu["Snake"].pressed&&menu["Snake"].on_click()))
        {
            menu["Earth"].pressed=false;
            menu["BigBattle"].pressed=false;
            menu["Caribians"].pressed=false;
            menu["Gorge"].pressed=false;
            menu["Snake"].pressed=false;
            menu[last_checked2].pressed=true;
            ok=true;
        }
        if (!ok)
        {
            if (menu["Earth"].pressed) last_checked2="Earth";
            if (menu["BigBattle"].pressed) last_checked2="BigBattle";
            if (menu["Caribians"].pressed) last_checked2="Caribians";
            if (menu["Gorge"].pressed) last_checked2="Gorge";
            if (menu["Snake"].pressed) last_checked2="Snake";
        }

        if (last_standart==2)
        if (!(menu["start3"].pressed&&menu["start3"].on_click()))
            menu["start3"].pressed=false;

        if (last_standart==3)
        if (!(menu["cancel3"].pressed&&menu["cancel3"].on_click()))
            menu["cancel3"].pressed=false;

        if (menu["start3"].pressed)
        {
            menu["Earth"].pressed=false;
            menu["BigBattle"].pressed=false;
            menu["Caribians"].pressed=false;
            menu["Gorge"].pressed=false;
            menu["Snake"].pressed=false;

            menu["start3"].pressed=false;
            menu["cancel3"].pressed=false;

            if (menu["usa1"].pressed) chosen_country[0] = USA;
            if (menu["ukraine1"].pressed) chosen_country[0] = UKRAINE;
            if (menu["russia1"].pressed) chosen_country[0] = RUSSIA;
            if (menu["germany1"].pressed) chosen_country[0] = GERMANY;
            if (menu["france1"].pressed) chosen_country[0] = FRANCE;
            if (menu["england1"].pressed) chosen_country[0] = ENGLAND;

            if (menu["usa2"].pressed) chosen_country[1] = USA;
            if (menu["ukraine2"].pressed) chosen_country[1] = UKRAINE;
            if (menu["russia2"].pressed) chosen_country[1] = RUSSIA;
            if (menu["germany2"].pressed) chosen_country[1] = GERMANY;
            if (menu["france2"].pressed) chosen_country[1] = FRANCE;
            if (menu["england2"].pressed) chosen_country[1] = ENGLAND;

            if (menu["player_vs_player"].pressed) player[1] = HUMAN;
            if (menu["player_vs_pc"].pressed) player[1] = PC;
            player[0] = HUMAN;

            if(menu["but1"].pressed) Mode = 1;
            else if(menu["but2"].pressed) Mode = 2;
            else Mode = 3;

            if (menu["first"].pressed) difficulty = EASY;
            if (menu["second"].pressed) difficulty = MEDIUM;
            if (menu["third"].pressed) difficulty = HARD;

            game_with_features=menu["but3"].pressed&&menu["game_with_features"].pressed;

            string wh=g;
            if (wh=="Earth") wh="World";
            if (wh=="Snake") wh="Spiral";

            Hexes=parse_map_from_file("Maps\\"+wh+".txt");

            if (Mode == 3)
            {
                Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
                player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
            }
            try_move_cam(state, 0, curl, curr, curd, curu);

            in_main_menu = 0;
            all_check_clear();
        }

        if (menu["cancel3"].pressed)
        {
            menu["Earth"].pressed=false;
            menu["BigBattle"].pressed=false;
            menu["Caribians"].pressed=false;
            menu["Gorge"].pressed=false;
            menu["Snake"].pressed=false;

            menu["start3"].pressed=false;
            menu["cancel3"].pressed=false;

            type_of_menu="Settings";
            all_check_clear();
        }
    }
}

void mouse_buttons_pause(int state)
{
    POINT mouse;
    GetCursorPos(&mouse);
    if (state==GLUT_DOWN)
    {
        if (menu["pause22"].on_click()&&mouse.y<=80.0*height/768)
        {
            menu["pause22"].click();
            last_dermo=1;
        }
        else if (menu["surrender"].on_click())
        {
            menu["surrender"].click();
            last_dermo=2;
        }
        else last_dermo=3;
    }
    if (state==GLUT_UP)
    {
        if (last_dermo==1)
        if (!(menu["pause22"].pressed&&(menu["pause22"].on_click()&&mouse.y<=80.0*height/768)))
            menu["pause22"].pressed=false;

        if (last_dermo==2)
        if (!(menu["surrender"].pressed&&menu["surrender"].on_click()))
            menu["surrender"].pressed=false;

        if (menu["pause22"].pressed)
        {
            menu["pause22"].pressed=false;
            pause=true;
        }

        if (menu["surrender"].pressed)
        {
            menu["surrender"].pressed=false;
            surrender_menu=true;
            pause=true;
        }
    }
}

void mouse_surrender_menu(int state)
{
    if (!surrender_menu) return;

    if (state==GLUT_DOWN)
    {
        if (menu["yes"].on_click())
            menu["yes"].click();
        if (menu["no"].on_click())
            menu["no"].click();
    }
    if (state==GLUT_UP)
    {
        if (!(menu["yes"].on_click()&&menu["yes"].pressed))
            menu["yes"].pressed=false;
        if (!(menu["no"].on_click()&&menu["no"].pressed))
            menu["no"].pressed=false;

        if (menu["yes"].pressed)
        {
            pause=false;
            surrender_menu=false;
            all_check_clear();
            surrender();
        }

        if (menu["no"].pressed)
        {
            pause=false;
            surrender_menu=false;
            all_check_clear();
        }
    }
}
