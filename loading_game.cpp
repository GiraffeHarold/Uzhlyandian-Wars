#include "loading_game.h"
#include "global_vars.h"
#include "drawing.h"
#include "controller.h"
#include "basic_classes.h"
#include "intellect.h"
#include "draw_menu.h"
#include "Levels_intellect.h"

int cur_turn, Round, cur;
bool demo = false;
vector <Turn> turn;
Turn last_turn_made;
ofstream buf;

Turn :: Turn()
{
    this -> who = -1;
    this -> way = *new vi(0);
}

void init_field(string s, Town& pl1, Town& pl2, vector<vector<Cell> >& field)
{
    chosen_country[0] = UKRAINE;
    chosen_country[1] = FRANCE;
    ifstream fin(s.data());
    fin >> N >> M >> Turns >> Mode;
    buf << N << " " << M << " " << Turns << " " << Mode << "\n";
    int X, Y;
    field.resize(N);
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            field[i].pb(Cell(i, j, EMPTY));
    fin >> X >> Y;
    buf << X << " " << Y << " ";
    X--, Y--;
    pl1 = Town(X, Y, chosen_country[0]);
    field[X][Y].town = &pl1;
    color_town(X, Y, chosen_country[0], field);

    fin >> X >> Y;
    buf << X << " " << Y << "\n";
    X--, Y--;
    pl2 = Town(X, Y, chosen_country[1]);
    field[X][Y].town = &pl2;
    color_town(X, Y, chosen_country[1], field);

    if (Mode > 1)
    {
        int q;
        fin >> q;
        buf << q << " ";
        for (int i=0; i<q; i++)
        {
            int x, y;
            fin >> x >> y;
            buf << x << " " << y << " ";
            x--, y--;
            field[x][y].relief = MOUNTAIN;
        }
        buf << "\n";
        fin >> q;
        buf << q << " ";
        for (int i=0; i<q; i++)
        {
            int x, y;
            fin >> x >> y;
            buf << x << " " << y << " ";
            x--, y--;
            field[x][y].relief = RIVER;
        }
        buf << "\n";
    }

    fin >> Round;
    buf << (Round == 2*Turns - 1 ? "" : to_string(Round+1) + "\n");
    for (int i=0; i<Round; i++)
    {
        Turn cur_turn;
        cur_turn.who = i % 2;
        if (Mode != 3)
        {
            int x, y;
            fin >> x >> y;
            buf << x << " " << y << "\n";
            x--, y--;
            cur_turn.way.pb(x);
            cur_turn.way.pb(y);
            turn.pb(cur_turn);
        } else
        {
            string cur = "", s;
            if (!i) getline(fin, s);
            getline(fin, s);
            buf << s << "\n";
            vector <int> nums(0);
            for (int i=0; i<s.length(); i++)
                if (s[i] == ' ') nums.pb(atoi(cur.data())), cur = ""; else cur += s[i];
            if (cur != "")
                nums.pb(atoi(cur.data()));

            int pos = 0;

            while (pos < nums.size())
            {
                Turn cur_turn = *new Turn();
                cur_turn.who = i % 2;
                int x = nums[pos], y = nums[++pos];
                x--;
                cur_turn.way.pb(x);
                cur_turn.way.pb(y);
                if (y > 0)
                {
                    y = nums[++pos];
                    cur_turn.way.pb(y);
                }
                turn.pb(cur_turn);
                pos++;
            }
        }
    }
    fin.close();
}

void move_from_file(int dir)
{
    int x = general_chosen -> x;
    if (x % 2 == 0)
    {
        Hexes[general_chosen -> x][general_chosen -> y].general = NULL;
        if (dir == 1) general_chosen -> y--;
        if (dir == 2) general_chosen -> y--, general_chosen -> x++;
        if (dir == 3) general_chosen -> x++;
        if (dir == 4) general_chosen -> y++;
        if (dir == 5) general_chosen -> x--;
        if (dir == 6) general_chosen -> y--, general_chosen -> x--;
        Hexes[general_chosen -> x][general_chosen -> y].general = general_chosen;
    } else
    {
        Hexes[general_chosen -> x][general_chosen -> y].general = NULL;
        if (dir == 1) general_chosen -> y--;
        if (dir == 2) general_chosen -> x++;
        if (dir == 3) general_chosen -> x++, general_chosen -> y++;
        if (dir == 4) general_chosen -> y++;
        if (dir == 5) general_chosen -> x--, general_chosen -> y++;
        if (dir == 6) general_chosen -> x--;
        Hexes[general_chosen -> x][general_chosen -> y].general = general_chosen;
    }
}

void next_turn(vector<vector<Cell> >& field)
{
    if (Mode < 3)
    {
        int color = chosen_country[turn[cur].who];
        int x = turn[cur].way[0], y = turn[cur].way[1];
        Hexes[x][y].fort = new Fort(x, y, color);
        color_town(x, y, color, Hexes);
    } else
    {
        int color = chosen_country[turn[cur].who], who = turn[cur].who;
        int x = turn[cur].way[0];

        General* current_general = what_general[who][x];

        general_chosen = current_general;
        int y = turn[cur].way[1];
        if (y == -1)
            set_fort();
        if (y > 0)
        {
            move_from_file(y);
            y = turn[cur].way[2];
            if (y == -1)
                set_fort();
            if (y > 0)
                move_from_file(y);
        }
    }
}

Town pl1, pl2;

void play_a_turn_from_file()
{
    remove("log.txt");
    remove("buf.txt");
    buf.open("buf.txt", ios :: app | ios :: in);
    buf.clear();
    log.clear();
    log.open("log.txt", ios :: app);

    difficulty = HARD;
    init_field("TUI.dat", pl1, pl2, Hexes);
    town[0] = &pl1;
    town[1] = &pl2;
    int our_color = 1 - turn.back().who;

    player[0] = -1;
    player[our_color] = PC;
    player[1 - our_color] = HUMAN;

    cur_turn = 0;
    cur = 0;
    if (cur_turn != Turns*2)
    {
        Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
        player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);

        if (player[cur_turn%2] == PC)
            init_new_general(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
        what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
    }

    for (int i=0; i<turn.size(); i++)
    {
        next_turn(Hexes);
        int q = 0;
        try_move_cam(q, 0, curl, curr, curd, curu);
        cur++;
        if (i == turn.size() - 1 || turn[i].who != turn[i+1].who)
        {
            //printf("cur_turn %d\n", cur_turn + 1);
            cur_turn++;
            if (cur_turn != Turns*2)
            {
                Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
                player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
                if (player[cur_turn%2] == PC)
                    init_new_general(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
                what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
            }
        }
        display_field(Hexes);
    }
    if (Mode < 3)
    {
        do_intellectual_move(chosen_country[our_color]);
        buf << last_turn_made.way[0] << " " << last_turn_made.way[1] << "\n";
        buf.close();
        buf.clear();
        ifstream fin("buf.txt");
        ofstream answer("TUI.dat");
        answer.clear();
        fin.clear();
        string s;
        getline(fin, s);
        while (!fin.eof())
        {
            answer << s << "\n";
            getline(fin, s);
        }
        in_main_menu = false;
        int q = 0;
        try_move_cam(q, 0, curl, curr, curd, curu);
        display_field(Hexes);
        fin.close();
        answer.close();
    } else
    {
        do_intellectual_move_with_general(chosen_country[our_color]);
        /*log.close();

        ifstream from_log("log.txt");
        getline(from_log, s);
        //from_log.seekg(from_log.beg);
        //cout << from_log.eof() << " " << from_log.gcount() << "\n";
        while (!from_log.eof())
        {
            //cout << (s == "") << "\n";
            buf << s << "\n";
            getline(from_log, s);
        }
        from_log.close();
        log.open("log.txt", ios :: app);*/

        string s;
        ifstream fin;
        remove("TUI.dat");
        ofstream answer;
        answer.open("TUI.dat", ios :: app);
        answer << buf.rdbuf();
        in_main_menu = false;
        int q = 0;
        try_move_cam(q, 0, curl, curr, curd, curu);
        display_field(Hexes);
        fin.close();
        answer.close();
    }
}

void color_town(int X, int Y, int color, vector<vector<Cell> >& field)
{
    field[X][Y].color = color;
    for (int i=0; i<6; i++)
    {
        int nx = X + moves[X%2][i].fi, ny = Y + moves[X%2][i].se;
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && field[nx][ny].town == NULL)
            field[nx][ny].color = color;
    }
}

/*
8 5 3 3
3 2 6 5
3 7 1 8 2 6 3
5 2 2 3 4 5 4 7 2 7 5
2
1 4 3
1 6 6
*/
