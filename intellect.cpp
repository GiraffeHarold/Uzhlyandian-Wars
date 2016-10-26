
#include "intellect.h"
#include "Levels_intellect.h"
#include "generals.h"
#include "drawing.h"
#include "end_game.h"
#include "basic_classes.h"

third_regime_turn :: third_regime_turn() {}
third_regime_turn :: third_regime_turn(General * general, int x, int y, bool must_set_a_fort) :
    general(general), x(x), y(y), must_set_a_fort(must_set_a_fort) {}

third_regime_turn cur_third_turn;

ofstream deb("general_intellect_debug.txt");
/// START INTELECT METHODS
int distOfBfs[100][100];
bool vis[100][100], set_fort_now = 0;
queue< pii > q;
// нвхярйю люяхбс дхярюмж╡и
void clrDist()
{
    for (int i(0); i < 100; i++)
        for (int j(0); j < 100; j++)
            distOfBfs[i][j] = INF;
}
// нвхярйю люяхбс б╡дб╡дюмху бепьхм
void clrVisit()
{
    for (int i(0); i<100; i++)
        for (int j(0); j<100; j++)
            vis[i][j] = false;
}

// нвхярйю вепцх
void clrQ()
{
    while(!q.empty())
    {
        q.pop();
    }
}

bool isEmpty(Cell c)
{
     if(c.town != NULL || c.fort != NULL || c.relief != EMPTY||c.village)
        return false;
     return true;
}

bool canGo(int x, int y, int color)
{
    if(Hexes[x][y].fort != nullptr) return false;
    if(Hexes[x][y].town != nullptr) return false;
    if(Hexes[x][y].relief != EMPTY) return false;
    if(Hexes[x][y].village) return false;

    if(Hexes[x][y].color == color)
        return true;
   for(auto turn : moves[x % 2])
    {
        pii to = mp(x + turn.fi, y + turn.se);

        if(to.fi < 0 || to.fi >= N || to.se < 0 || to.se >= M) continue;

        if(Hexes[to.fi][to.se].color == color)
            return true;
    }
    return false;
}

///hueta (c) Barik

// о╡дпюусмнй оп╡нпхрерс йк╡рхмйх
int priority(int x, int y, int color)
{
    Cell c = Hexes[x][y];
    if(!isEmpty(c))
        return 0;
    int priorityEmpty = 5;
    int priorityFull = 60;
    int penalty = -5;
    int total = 0;
    for(auto turn : moves[x % 2])
    {
        pii to = mp(x + turn.fi, y + turn.se);

        if(to.fi < 0 || to.fi >= N || to.se < 0 || to.se >= M) continue;


        Cell v = Hexes[to.fi][to.se];
        if(v.fort != nullptr || v.relief ==  MOUNTAIN)
            total += priorityFull *(color != v.color);
        else total += priorityEmpty *(color != v.color);
    }
    return total;
}

// о╡дпюунбселн б╡дярюмэ дн бепьхм
void bfs(int x, int y)
{
    pii s = mp(x, y);
    clrQ();
    q.push(s);
    clrDist();
    distOfBfs[s.fi][s.se] = 0;
    while(!q.empty())
    {
        pii v = q.front();
        for(auto turn : moves[v.fi % 2])
        {
            pii to = mp(v.fi + turn.fi, v.se + turn.se);

            if(to.fi < 0 || to.fi >= N || to.se < 0 || to.se >= M) continue;

            if(Hexes[to.fi][to.se].relief == MOUNTAIN) continue;

            if(distOfBfs[to.fi][to.se] > distOfBfs[v.fi][v.se] + 1)
            {
                q.push(to);
                distOfBfs[to.fi][to.se] = distOfBfs[v.fi][v.se] + 1;
            }
        }
        q.pop();
    }
}


pii getBestCell(int color)
{
    vector < pair < double, pii > > Ranks;
    for (int i(0); i < N;i++)
        for (int j(0); j < M;j++)
            if(canGo(i, j, color))
                Ranks.pb(mp(priority(i, j, color), mp(i, j)));
    if(Ranks.size() == 0) return mp(-1, -1);
    return max_element(Ranks.begin(), Ranks.end()) -> second;
}

double  scrumble(int old, double k = 1.5){
    return old*( 1 + rand()/RAND_MAX);

}
pii getAlmostBestCell(int color)
{
    vector < pair < double, pii > > Ranks;
    for (int i(0); i < N;i++)
        for (int j(0); j < M;j++)
            if(canGo(i, j, color))
                Ranks.pb(mp(scrumble(priority(i, j, color)), mp(i, j)));
    if(Ranks.size() == 0) return mp(-1, -1);
    return max_element(Ranks.begin(), Ranks.end()) -> second;
}

// START INTELLECT FOR 3 RGIME

int dist_in_intellect(int sx, int sy, int x, int y)
{
    bfs(sx, sy);
    return distOfBfs[x][y];///ця хуєта пригодилася!!!
}

double priority_for_third(int x, int y, int color)
{
    double result = INF;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(Hexes[i][j].general != nullptr && Hexes[i][j].general->color != color)
            result = min(result,(double)dist_in_intellect(x, y, i, j));
    return result;
}


bool do_third_regime_turn(int color)
{

    General * general_for_turn = nullptr;

    if(Turns * 2 - cur_turn <= 2)
    {
        int turn_x = -1, turn_y = -1;


        if(general_for_turn == nullptr)
        {
            for(int i = 0; i < N; i++)
                for(int j = 0; j < M; j++)
                    if(Hexes[i][j].general != nullptr
                        && Hexes[i][j].general->color == color &&
                        Hexes[i][j].general->turns_left != 0 && Hexes[i][j].relief == EMPTY
                        && Hexes[i][j].town == nullptr
                        && Hexes[i][j].fort == nullptr)
                    {
                        general_for_turn = Hexes[i][j].general;
                        goto end_of_operation;
                    }
            end_of_operation : {}
        }

        if(general_for_turn == nullptr)
        {
            for(int i = 0; i < N; i++)
                for(int j = 0; j < M; j++)
                    if(Hexes[i][j].town != nullptr && Hexes[i][j].color == color && Hexes[i][j].general != nullptr)
                    {

                        Hexes[i][j].general->clicked();


                        for(int i = 0; i < N; i++)
                            for(int j = 0; j < M; j++)
                                if(Hexes[i][j].shined && Hexes[i][j].town == nullptr)
                                    turn_x = i, turn_y = j;
                        clear_shining();
                        if(turn_x == -1)
                        {
                            end_game();
                            return 0;
                        }
                        general_for_turn = Hexes[i][j].general;
                    }
        }

        if(general_for_turn == nullptr) return false;


        if(turn_x == -1)
            cur_third_turn = third_regime_turn(general_for_turn, general_for_turn->x, general_for_turn->y, true);
        else
            cur_third_turn = third_regime_turn(general_for_turn, turn_x, turn_y, false);
        return true;
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(Hexes[i][j].town != nullptr && Hexes[i][j].color == color && Hexes[i][j].general != nullptr)
            {

                Hexes[i][j].general->clicked();
                //cout << "TRY FIND NEW GENERAL\n";

                bool have_any_turn = false;
                for(int i = 0; i < N; i++)
                    for(int j = 0; j < M; j++)
                        if(Hexes[i][j].shined) have_any_turn = true;

                clear_shining();
                if(!have_any_turn) continue;

                //cout << "FOUND FIRST GENERAL\n";
                general_for_turn = Hexes[i][j].general;
            }

    if(general_for_turn == nullptr)
    {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                if(Hexes[i][j].general != nullptr && Hexes[i][j].general->color == color && Hexes[i][j].general->turns_left == 2)
                {
                    //cout << "TRY FIND NEW GENERAL\n";
                    Hexes[i][j].general->clicked();

                    bool have_any_turn = false;
                    for(int i = 0; i < N; i++)
                        for(int j = 0; j < M; j++)
                            if(Hexes[i][j].shined) have_any_turn = true;

                    clear_shining();
                    if(!have_any_turn) continue;

                    //cout << "FOUND OTHER GENERAL\n";
                    general_for_turn = Hexes[i][j].general;
                    goto end_of_operation1;
                }
        end_of_operation1 : {}
    }

    if(general_for_turn == nullptr) return false;

    vector< pair<double, pii> > Ranks(0);
    set<double> hueta;

    general_for_turn -> clicked();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (Hexes[i][j].shined)
            {
                hueta.insert(priority_for_third(i, j, color));
                Ranks.pb(mp(priority_for_third(i, j, color), mp(i, j)));
            }

    //for(auto x : hueta)
      //  cout << fixed << setprecision(5) << x << "\n";


    if(Ranks.empty()) {cerr << "bug with shining";return false;}

    pii xy = min_element(Ranks.begin(), Ranks.end())->se;

    cur_third_turn = third_regime_turn(general_for_turn, xy.fi, xy.se, false);

    return true;

}

bool do_intellectual_move_with_general(int color)
{
    bool p;
    if (difficulty == HARD) p = goodThird(color);
    else p = do_third_regime_turn(color);
    cout << p << " " << cur_third_turn.x << " " << cur_third_turn.y << " " << cur_third_turn.general -> x << " " << cur_third_turn.general -> y << " " << cur_third_turn.must_set_a_fort << "\n";
    if (!p)
    {
        log_generals(cur_turn%2);
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
            {
                if (Hexes[i][j].town != NULL && Hexes[i][j].general != NULL)
                {
                    display_field(Hexes);
                    surrender();
                    cur_turn = 2 * Turns;
                    return 1;
                }
            }

        cur_turn++;
        if (cur_turn != Turns*2)
        {
            Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
            player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
            what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
        }
        renew_turns();
        general_chosen = NULL;
        set_fort_now = 0;
        clear_shining();
        return 1;
    }
    general_chosen = cur_third_turn.general;
    general_chosen -> clicked();
    general_move(mp(cur_third_turn.x, cur_third_turn.y));
    set_fort_now = cur_third_turn.must_set_a_fort;
    if (set_fort_now)
        general_chosen = cur_third_turn.general;
    return 0;
}


bool do_intellectual_move_with_general_from_file(int color)
{
    bool p;
    if (difficulty == HARD) p = goodThird(color);
    else p = do_third_regime_turn(color);
    cout << p << " " << cur_third_turn.x << " " << cur_third_turn.y << " " << cur_third_turn.general -> x << " " << cur_third_turn.general -> y << " " << cur_third_turn.must_set_a_fort << "\n";
    if (!p)
    {
        log_generals(cur_turn%2);
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
            {
                if (Hexes[i][j].town != NULL && Hexes[i][j].general != NULL)
                {
                    display_field(Hexes);
                    surrender();
                    cur_turn = 2 * Turns;
                    return 1;
                }
            }

        cur_turn++;
        if (cur_turn != Turns*2)
        {
            Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general = new General(cur_turn/2 + 1, *town[cur_turn%2]);
            player_general[cur_turn%2].insert(Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general);
            what_general[cur_turn%2][cur_turn/2] = Hexes[town[cur_turn%2] -> x][town[cur_turn%2] -> y].general;
        }
        renew_turns();
        general_chosen = NULL;
        set_fort_now = 0;
        clear_shining();
        return 1;
    }
    general_chosen = cur_third_turn.general;
    general_chosen -> clicked();
    general_move_from_file(mp(cur_third_turn.x, cur_third_turn.y));
    set_fort_now = cur_third_turn.must_set_a_fort;
    if (set_fort_now)
        general_chosen = cur_third_turn.general;
    return 0;
}

// FINISH

void do_intellectual_move(int color)
{
    pii q;
    if(difficulty == EASY)
        q = Easy(color, Mode);
    else if(difficulty == MEDIUM)
        q = Medium(color, Mode);
    else
        q = Hard(color, Mode);

    if (q.fi == -1)
    {
        display_field(Hexes);
        surrender();
//        cout << "SURRENDERED !!!!!!!!!!!!!\n";
        cur_turn = 2*Turns;
        return;
    }
    Hexes[q.fi][q.se].fort = new Fort(q.fi, q.se, color);
    log << q.fi + 1 << " " << q.se + 1 << "\n";

    last_turn_made = *new Turn;
    last_turn_made.who = cur_turn % 2;
    last_turn_made.way.pb(q.fi+1);
    last_turn_made.way.pb(q.se+1);

    color_town(q.fi, q.se, color, Hexes);
    cur_turn++;
    just_moved = 100;
    if (player[cur_turn % 2] == HUMAN) just_moved = 0;
}
