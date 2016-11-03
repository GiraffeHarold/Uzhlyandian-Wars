#include "Levels_intellect.h"
#include "hard_intellect.h"

using namespace  std;

pii Easy(int color,int regime)
{
    if(regime == 1 || regime == 2)
    {
        for (int coordinate_1(0);coordinate_1<N;coordinate_1++)
        {
            for (int coordinate_2(0);coordinate_2<M;coordinate_2++)
            {
                if(canGo(coordinate_1,coordinate_2,color))
                    return (make_pair(coordinate_1,coordinate_2));
            }
        }
    }
    return mp(-1 ,-1);
}

pii Medium(int color,int regime)
{
    if(regime == 1 || regime == 2)
    {
        return getBestCell(color);
    }
}

pii Hard(int color,int regime)
{
    if(regime == 1 || regime == 2)
        return getAlmostBestCell(color);
}

bool Middle_third(int color)
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

    general_for_turn -> clicked();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (Hexes[i][j].shined)
            {
                Ranks.pb(mp(priority_for_third(i, j, color), mp(i, j)));
            }

//    if(Ranks.empty()) {cerr << "bug with shining";return false;}

    pii xy = min_element(Ranks.begin(), Ranks.end())->se;

    cur_third_turn = third_regime_turn(general_for_turn, xy.fi, xy.se, false);

    return true;

}

bool Easy_third(int color)
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

    general_for_turn -> clicked();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (Hexes[i][j].shined)
            {
                Ranks.pb(mp(priority(i, j, color), mp(i, j)));
            }

//    if(Ranks.empty()) {cerr << "bug with shining";return false;}

    pii xy = min_element(Ranks.begin(), Ranks.end())->se;

    bool is_set_fort = (dst(general_for_turn->x,general_for_turn->y, xy.fi,xy.se) < 2 ? rand() % 3 : 0);
    cur_third_turn = third_regime_turn(general_for_turn, xy.fi, xy.se, is_set_fort);

    return true;

}

void init_new_general(General *now)
{
//    cerr << "\n\n\n\n                  " << cur_turn/2 << " TURN\n";
    if (ourSquads.empty())
        ourSquads.push_back(new Squad(DEFENCE));
    ourSquads[0] -> add(now);
    init_distance(now -> color);
    /*ourSquads.push_back(new Squad(BUILDER));
    ourSquads.back() -> add(now);
    init_distance(now -> color);*/
}

bool goodThird(int color)
{
    init_distance(color);
    for (auto q : ourSquads)
        if (q -> moving < q -> size())
        {
            q -> move();
            cur_third_turn = moveNow.back();
            return 1;
        }

//    cout << "Pushed squads on turn: " << cur_turn/2 << "\n";
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
        {
            if (Hexes[i][j].town && Hexes[i][j].general && Hexes[i][j].general -> turns_left > 0)
                {
                    general_chosen = Hexes[i][j].general;
                    general_chosen -> clicked();
//                    cout << general_chosen -> turns_left << "    !!!!!!!!!\n";
                    for (int ii=0; ii<N; ii++)
                        for (int jj=0; jj<M; jj++)
                            if (Hexes[ii][jj].shined && Hexes[ii][jj].general == NULL)
                            {
//                                cout << ii << " " << jj << "\n";
                                createMove(general_chosen, {ii, jj}, 0);
                                cur_third_turn = moveNow.back();
                                return 1;
                            }
                }
            if (Hexes[i][j].town && Hexes[i][j].general)
                for (int ii=0; ii<N; ii++)
                    for (int jj=0; jj<M; jj++)
                    {
                        if (Hexes[ii][jj].general && Hexes[ii][jj].general -> color == color && Hexes[ii][jj].general -> turns_left && can_set(Hexes[ii][jj].general, ii, jj))
                        {
//                            cout << ii << " " << jj << " " << Hexes[ii][jj].general -> color << "\n";
                            createMove(Hexes[ii][jj].general, {ii, jj}, 1);
                            cur_third_turn = moveNow.back();
                            return 1;
                        }
                    }
            if (Hexes[i][j].town && Hexes[i][j].general)
            {
                surrender();
                return 0;
            }
        }
    return 0;
}
