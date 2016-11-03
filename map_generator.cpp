
#include "map_generator.h"
#include "loading_game.h"
#include "global_vars.h"

queue< pii > q_for_bfs;
bool visited[100][100];
int d[100][100];
Town *town[2];

int rand_in_range(int l, int r)
{
    return l + rand() % (r - l + 1);
}

int dst(int sx, int sy, int fx, int fy)
{

    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            d[i][j] = INF;

    d[sx][sy] = 0;
    q_for_bfs.push(mp(sx, sy));
    while(!q_for_bfs.empty())
    {
        pii v = q_for_bfs.front();
        q_for_bfs.pop();
        int x = v.fi, y = v.se;

        for(auto move : moves[x % 2])
        {
            int to_x = x + move.fi, to_y = y + move.se;

            if(to_x < 0 || to_x >= N || to_y < 0 || to_y >= M) continue;

            if(d[to_x][to_y] > d[x][y] + 1)
            {
                q_for_bfs.push(mp(to_x, to_y));
                d[to_x][to_y] = d[x][y] + 1;
            }
        }
    }
    return (d[fx][fy] == INF ? -1 : d[fx][fy]);
}




bool havent_any_turn(vector< vector<Cell> > field, int color)
{
    bool have_turn = true;
    if(Mode == 3)
    {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                if(field[i][j].color == color && field[i][j].general != nullptr)
                {
                    for(auto move : moves[i % 2])
                    {
                        int to_x = i + move.fi, to_y = j + move.se;
                        if(to_x < 0 || to_x >= N || to_y < 0 || to_y >= M) continue;

                        if(field[to_x][to_y].relief != MOUNTAIN && field[to_x][to_y].general == nullptr)
                            have_turn = true;

                    }
                }
    }
    else
    {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                if(field[i][j].color == color)
                {
                    for(auto move : moves[i % 2])
                    {
                        int to_x = i + move.fi, to_y = j + move.se;
                        if(to_x < 0 || to_x >= N || to_y < 0 || to_y >= M) continue;

                        for(auto move2 : moves[to_x % 2])
                        {
                            int to2_x = to_x + move2.fi, to2_y = to_y + move2.se;
                            if(to2_x < 0 || to2_x >= N || to2_y < 0 || to2_y >= M) continue;

                            if(field[to2_x][to2_y].relief != MOUNTAIN && field[to2_x][to2_y].fort == nullptr)
                                have_turn = true;
                        }

                        if(field[to_x][to_y].relief != MOUNTAIN && field[to_x][to_y].fort == nullptr)
                            have_turn = true;

                    }
                }
    }
    return have_turn;
}

bool is_consecutive_without_point(vector< vector< Cell > > field, int not_free_x, int not_free_y)
{
    int sx = 0, sy = 0;
    if(not_free_x == 0 && not_free_y == 0)
    {
        for(int i = 0; i < field.size(); i++)
            for(int j = 0; j < field[0].size(); j++)
                if(field[i][j].relief == EMPTY && i != not_free_x && j != not_free_y)
        {
            sx = i;
            sy = j;
            goto start;
        }
    }

    start :

    for(int i = 0; i < field.size(); i++)
        for(int j = 0; j < field[0].size(); j++)
            visited[i][j] = false;

    while(!q_for_bfs.empty()) q_for_bfs.pop();

    q_for_bfs.push(mp(sx, sy));

    visited[sx][sy] = true;

    while(!q_for_bfs.empty())
    {
        pii v = q_for_bfs.front();
        q_for_bfs.pop();
        int x = v.fi, y = v.se;

        if(x == not_free_x && y == not_free_y) continue;

        for(auto move : moves[x % 2])
        {
            int to_x = x + move.fi, to_y = y + move.se;

            if(to_x < 0 || to_x >= N || to_y < 0 || to_y >= M) continue;

            if(field[to_x][to_y].relief == MOUNTAIN)  continue;

            if(to_x == not_free_x && to_y == not_free_y) continue;

            if(! visited[to_x][to_y])
            {
                q_for_bfs.push(mp(to_x, to_y));
                visited[to_x][to_y] = true;
            }
        }
    }

    for(int i = 0; i < field.size(); i++)
        for(int j = 0; j < field[0].size(); j++)
        {
            if(i == not_free_x && j == not_free_y) continue;
            if(field[i][j].relief == MOUNTAIN) continue;
            if(!visited[i][j]) return false;
        }

    return true;

}

bool at_other_sides(vector< vector< Cell > > field, int sx, int sy, int fx, int fy)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            d[i][j] = INF, visited[i][j] = false;

    d[sx][sy] = 0;
    while(q_for_bfs.size()) q_for_bfs.pop();
    q_for_bfs.push(mp(sx, sy));
    visited[sx][sy] = true;
    while(!q_for_bfs.empty())
    {
        pii v = q_for_bfs.front();
        q_for_bfs.pop();
        int x = v.fi, y = v.se;

        for(int i = 0; i < 6; i++)
        {
            pii move = moves[x % 2][i];
            int to_x = x + move.fi, to_y = y + move.se;
            if(to_x < 0 || to_x >= N || to_y < 0 || to_y >= M) continue;
            int cost = (field[to_x][to_y].relief == RIVER);


            if(!visited[to_x][to_y])
            {
                q_for_bfs.push(mp(to_x, to_y));
                visited[to_x][to_y] = true;
                d[to_x][to_y] = d[x][y] + cost;
            }
        }
    }

    return (d[fx][fy] > 0);



}

vector< vector< Cell > >  set_towns_at_map(vector< vector<Cell> > result)
{

    vector< pii > empty_cells;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(result[i][j].relief == EMPTY)
                empty_cells.pb(mp(i, j));


    int town1X, town1Y, town2X, town2Y;

    int id1 = rand() % empty_cells.size();

    town1X = empty_cells[id1].fi;
    town1Y = empty_cells[id1].se;



    vector< pii > so_far_empty_cells;
    for(auto town2 : empty_cells)
        if(dst(town1X, town1Y, town2.fi, town2.se) >= min(N, M))
        {
            if(type == CONTINENTS && !at_other_sides(result, town1X, town1Y, town2.fi, town2.se)) continue;
            so_far_empty_cells.pb(town2);
        }

    if(!so_far_empty_cells.empty())
    {
        int id2 = rand() % so_far_empty_cells.size();

        town2X = so_far_empty_cells[id2].fi;
        town2Y = so_far_empty_cells[id2].se;
    }
    else
    {
        bool found_at_other_side = false;
        int id2 = 0;
        for(int i = 0; i < empty_cells.size(); i++)
            if(dst(town1X, town1Y, empty_cells[id2].fi, empty_cells[id2].se) <
               dst(town1X, town1Y, empty_cells[i].fi, empty_cells[i].se))
                {
                    if(type == CONTINENTS &&
                       !at_other_sides(result, town1X, town1Y, empty_cells[id2].fi, empty_cells[id2].se)) continue;
                    found_at_other_side = true;
                    id2 = i;
                }
            if(type == CONTINENTS && !found_at_other_side)
            {
                for(int i = 0; i < empty_cells.size(); i++)
                    if(dst(town1X, town1Y, empty_cells[id2].fi, empty_cells[id2].se) <
                       dst(town1X, town1Y, empty_cells[i].fi, empty_cells[i].se))
                            id2 = i;
            }

        town2X = empty_cells[id2].fi;
        town2Y = empty_cells[id2].se;
    }

    if(dst(town1X, town1Y, town2X, town2Y) < 3)
        return set_towns_at_map(result);

    result[town1X][town1Y].town = new Town(town1X, town1Y, chosen_country[0]);
    town[0] = result[town1X][town1Y].town;

    result[town2X][town2Y].town = new Town(town2X, town2Y, chosen_country[1]);
    town[1] = result[town2X][town2Y].town;

    color_town(town1X, town1Y, chosen_country[0], result);
    color_town(town2X, town2Y, chosen_country[1], result);


    return result;
}

vector< vector< Cell > > generate_map(int size, int type, int relief)
{
    srand(time(NULL));
    vector< vector< Cell > > result;

    /// work with size
        if(size == SMALL)
            N = rand_in_range(5, 8), M = rand_in_range(5, 8);
        else if(size == MIDDLE)
            N = rand_in_range(10, 20), M = rand_in_range(10, 20);
        else if(size == LARGE)
            N = rand_in_range(21, 35), M = rand_in_range(21, 35);
        else
            N = rand_in_range(36, 50), M = rand_in_range(36, 50);

        result.resize(N);
        for(int i = 0; i < N; i++)
            result[i].resize(M);
    ///

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                result[i][j] = *(new Cell(i, j, EMPTY));

    ///work with type
        if(type == MAINLAND)
        {
            for(int i = 0; i < N; i++)
                for(int j = 0; j < M; j++)
                    result[i][j].relief = EMPTY;

            int lakes_cnt = min(N, M) - rand() % 3;
            for(int i = 0; i < lakes_cnt; i++)
            {
                int x, y;
                do
                {
                    x = rand() % N;
                    y = rand() % M;
                } while(result[x][y].relief != EMPTY);
                result[x][y].relief = RIVER;
            }
        }
        else if(type ==  CONTINENTS)
        {
            if(size > SMALL)
            {
                for(int i = 0; i < N; i++)
                    result[i][0].relief = result[i][M - 1].relief = RIVER;
                for(int i = 0; i < M; i++)
                    result[0][i].relief = result[N - 1][i].relief = RIVER;
            }
            int river_y = rand_in_range(max(2, M / 2), min(M - 1, M / 2 + 1));
            for(int i = 0; i < N; i++)
                for(int j = river_y; j < river_y + 1 + (Mode == 3 ? rand() % max(1,int( M * 0.2)) : 0); j++)
                    result[i][j].relief = RIVER;
        }
        else
        {
            for(int i = 0; i < N; i++)
                for(int j = 0; j < M; j++)
                    result[i][j].relief = RIVER;

            for(int i = 0; i < N * M / 3; i++)
                result[rand() % N][rand() % M].relief = EMPTY;
        }
    ///

    ///work with relief
        vector< pii > empty_cells;
        int cnt_empty = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                if(result[i][j].relief == EMPTY)
                {
                    empty_cells.pb(mp(i, j));
                    cnt_empty++;
                }


        int mountains_cnt = 0;
        if(relief == VALLEY)
            mountains_cnt = cnt_empty / 100;
        else if(relief == PIEDMONT)
            mountains_cnt = max(2, cnt_empty / 20) + rand() % 3;
        else
            mountains_cnt = max(6, cnt_empty / 3) + rand() % 3;

        random_shuffle(empty_cells.begin(), empty_cells.end());

        for(int i = 0; i < mountains_cnt; i++)
        {
            int x = empty_cells[i].fi, y = empty_cells[i].se;
            if(is_consecutive_without_point(result, x, y))
                result[x][y].relief = MOUNTAIN;
        }
    ///


    result = set_towns_at_map(result);

    return result;
}

vector< vector< Cell > > generate_empty_map(int size)
{
    srand(time(NULL));
    vector< vector< Cell > > result;

    /// work with size
        if(size == SMALL)
            N = rand_in_range(5, 8), M = rand_in_range(5, 8);
        else if(size == MIDDLE)
            N = rand_in_range(10, 20), M = rand_in_range(10, 20);
        else if(size == LARGE)
            N = rand_in_range(21, 35), M = rand_in_range(21, 35);
        else
            N = rand_in_range(36, 50), M = rand_in_range(36, 50);

        result.resize(N);
        for(int i = 0; i < N; i++)
            result[i].resize(M);
    ///

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                result[i][j] = *(new Cell(i, j, EMPTY));

    ///

    result = set_towns_at_map(result);

    return result;
}

vector < vector < Cell > > parse_map_from_file(string File_Name)
{
    ifstream ifs(File_Name);

    ifs >> N >> M >> Turns;
    swap(N,M);
    vector < vector < Cell > > res(N);

    for (int i(0);i<N;i++)
        res[i].resize(M);

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            res[i][j]=*(new Cell(i,j,EMPTY));

    int cnt_T=0;

    for (int j(0);j<M;j++)
    {
        for (int i(0);i<N;i++)
        {
            char x;
            ifs >> x;
            if(x=='0')
                res[i][j].relief = RIVER;

            if(x=='1')
                res[i][j].relief = EMPTY;

            if(x=='2')
                res[i][j].relief = MOUNTAIN;

            if(x=='3')
                res[i][j].relief = EMPTY,
                res[i][j].snow = true;

            if(x=='T')
            {
                res[i][j].town=new Town(i,j,chosen_country[cnt_T]);
                town[cnt_T]=res[i][j].town;
                color_town(i,j,chosen_country[cnt_T],res);
                cnt_T++;
            }
        }
    }

    ifs.close();

    if (cnt_T) return res;

    return set_towns_at_map(res);
}

void give_log(ofstream& log)
{
    log << Hexes.size() << " " << Hexes[0].size() << " " << Turns << " " << Mode;
    log << "\n" << town[0] -> x + 1 << " " << town[0] -> y + 1 << " " << town[1] -> x + 1 << " " << town[1] -> y + 1;
    if (Mode != 1)
    {
        vii mount(0), water(0);
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
            {
                if (Hexes[i][j].relief == MOUNTAIN) mount.pb(mp(i+1, j+1));
                if (Hexes[i][j].relief == RIVER) water.pb(mp(i+1, j+1));
            }
        log << "\n" << mount.size();
        for (auto q : mount)
            log << " " << q.fi << " " << q.se;
        log << "\n" << water.size();
        for (auto q : water)
            log << " " << q.fi << " " << q.se;
    }
}
