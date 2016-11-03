#include "generals.h"
#include "global_vars.h"
#include "loading_game.h"
#include "Levels_intellect.h"
#include "hard_intellect.h"

int general_moving_left = 0;
string last[10];

string next_gen(int color)
{
    vector<string> *q = &name[color];
    while (last[color] == q -> front())
        random_shuffle(q -> begin(), q -> end());
    last[color] = q -> front();
    return q -> front();
}

General* next_gen(int x, int y, int color)
{
    return new General(cur_turn/2 + 1, x, y, next_gen(color));
}

bool good_usa(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= M) return 0;
    if (Hexes[x][y].general != NULL || (Hexes[x][y].town && Hexes[x][y].town -> color != chosen_country[cur_turn%2])) return 0;
    return 1;
}

bool good(int x, int y)
{
    if (x < 0 || y < 0 || x >= N || y >= M) return 0;
    if (Hexes[x][y].general != NULL || Hexes[x][y].relief == MOUNTAIN || (Hexes[x][y].town && Hexes[x][y].town -> color != chosen_country[cur_turn%2])) return 0;
    return 1;
}

vector<pair<ld, ld> > operator +(const vector<pair<ld, ld> >& q, const vector<pair<ld, ld> >& w)
{
    vector<pair<ld, ld> > ans;
    for (int i=0; i<(int)q.size(); i++)
        ans.pb(q[i]);
    for (int i=0; i<(int)w.size(); i++)
        ans.pb(w[i]);
    return ans;
}

vector<pair<ld, ld> > up_right()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(1.5*R/40.0, -2*R_/40*sin(PI/6)));
    return q;
}

vector<pair<ld, ld> > down_right()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(1.5*R/40.0, 2*R_/40*sin(PI/6)));
    return q;
}

vector<pair<ld, ld> > up_left()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(-1.5*R/40.0, -2*R_/40*sin(PI/6)));
    return q;
}

vector<pair<ld, ld> > down_left()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(-1.5*R/40.0, 2*R_/40*sin(PI/6)));
    return q;
}

vector<pair<ld, ld> > up()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(0, -2*R_/20*sin(PI/6)));
    return q;
}

vector<pair<ld, ld> > down()
{
    ld R = 100;
    vector <pair <ld, ld> > q(0);
    for (int i=0; i<40; i++)
        q.pb(mp(0, 2*R_/20*sin(PI/6)));
    return q;
}

bool ok(int a,int b)
{
    return a>=0&&a<N&&b>=0&&b<M;
}

struct node
{
    int turns, wat, x, y;
    node() : turns(1000000), wat(1000000), x(-1), y(-1) {}
    node(int turns, int wat, int x, int y) : turns(turns), wat(wat), x(x), y(y) {}
};

bool operator < (const node& q, const node& w)
{
    return (q.turns < w.turns
            || (q.turns == w.turns && q.wat < w.wat)
            || (q.turns == w.turns && q.wat == w.wat && q.x < w.x)
            || (q.turns == w.turns && q.wat == w.wat && q.x == w.x && q.y < w.y));
}

set <node> queue_for_dijkstra;
pii pred[100][100];
node dist[100][100];

void add_path(int nx, int ny)
{
    if (!vectors_for_cell[mp(nx, ny)].empty())
        return;
    if (pred[nx][ny].fi == -1)
        return;
    int xx = pred[nx][ny].fi, yy = pred[nx][ny].se;
    add_path(xx, yy);
    if (nx%2 == 0 && nx != xx)
    {
        if (nx > xx)
        {
            if (ny == yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_right(),
                go_to_cell[mp(nx, ny)].se = 2;
            if (ny > yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_right(),
                go_to_cell[mp(nx, ny)].se = 3;
        }
        else if (nx < xx)
        {
            if (ny == yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_left(),
                go_to_cell[mp(nx, ny)].se = 6;
            if (ny > yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_left(),
                go_to_cell[mp(nx, ny)].se = 5;
        }
    }
    else if (nx == xx)
    {
        if (ny > yy) vectors_for_cell[mp(nx, ny)] = vectors_for_cell[mp(xx, yy)] + down(),
            go_to_cell[mp(nx, ny)].se = 4;
        else vectors_for_cell[mp(nx, ny)] = vectors_for_cell[mp(xx, yy)] + up(),
            go_to_cell[mp(nx, ny)].se = 1;
    }
    else
    {
        if (nx > xx)
        {
            if (ny < yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_right(),
                go_to_cell[mp(nx, ny)].se = 2;
            if (ny == yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_right(),
                go_to_cell[mp(nx, ny)].se = 3;
        }
        else
        {
            if (ny < yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_left(),
                go_to_cell[mp(nx, ny)].se = 6;
            if (ny == yy)
                vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_left(),
                go_to_cell[mp(nx, ny)].se = 5;
        }
    }
}

void shine_england(General *qq)
{
    int x = qq -> x, y = qq -> y, turns_left = qq -> turns_left, water_moving = qq -> water_moving;
    queue_for_dijkstra.clear();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            dist[i][j] = node(),
            pred[i][j] = mp(-1, -1);
    dist[x][y] = node(0, 0, x, y);
    queue_for_dijkstra.insert(dist[x][y]);
    while (!queue_for_dijkstra.empty())
    {
        node Q = *queue_for_dijkstra.begin();
        //cerr << Q.x << " " << Q.y << "\n";
        queue_for_dijkstra.erase(queue_for_dijkstra.begin());
        if (Q.turns + Q.wat > turns_left) continue;
        for (auto wh : moves[Q.x % 2])
        {
            int nx = Q.x + wh.fi, ny = Q.y + wh.se;
            if (!good(nx, ny) || Hexes[nx][ny].village)
                continue;
            node new_dist = Q;
            new_dist.turns++;
            new_dist.x = nx;
            new_dist.y = ny;
            if (!good(nx, ny)) continue;
            if (!Q.wat && qq -> water_moving == 1 && Hexes[nx][ny].relief == RIVER)
                new_dist.wat--;
            if (new_dist < dist[nx][ny])
            {
                queue_for_dijkstra.erase(dist[nx][ny]);
                dist[nx][ny] = new_dist;
                pred[nx][ny] = mp(Q.x, Q.y);
                queue_for_dijkstra.insert(dist[nx][ny]);
            }
        }
    }
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
        {
            if (qq -> x == i && qq -> y == j) continue;
            if (turns_left > dist[i][j].turns + dist[i][j].wat)
                Hexes[i][j].shined = 2;
            else if (dist[i][j].turns + dist[i][j].wat == turns_left)
                if (Hexes[i][j].town == NULL) Hexes[i][j].shined = 1;
                    else continue;
            Hexes[i][j].turn_waste = dist[i][j].turns;
            Hexes[i][j].water_waste = dist[i][j].wat;
            add_path(i, j);
        }
}


void shine_usa(General *qq)
{
    int x = qq -> x, y = qq -> y, turns_left = qq -> turns_left, water_moving = qq -> water_moving;
    queue_for_dijkstra.clear();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            dist[i][j] = node(),
            pred[i][j] = mp(-1, -1);
    dist[x][y] = node(0, 0, x, y);
    queue_for_dijkstra.insert(dist[x][y]);
    while (!queue_for_dijkstra.empty())
    {
        node Q = *queue_for_dijkstra.begin();
        //cerr << Q.x << " " << Q.y << "\n";
        queue_for_dijkstra.erase(queue_for_dijkstra.begin());
        if (Q.turns + Q.wat > turns_left) continue;
        for (auto wh : moves[Q.x % 2])
        {
            int nx = Q.x + wh.fi, ny = Q.y + wh.se;
            if (!good_usa(nx, ny) || Hexes[nx][ny].village)
                continue;
            node new_dist = Q;
            new_dist.turns++;
            new_dist.x = nx;
            new_dist.y = ny;
            if (new_dist < dist[nx][ny])
            {
                queue_for_dijkstra.erase(dist[nx][ny]);
                dist[nx][ny] = new_dist;
                pred[nx][ny] = mp(Q.x, Q.y);
                queue_for_dijkstra.insert(dist[nx][ny]);
            }
        }
    }
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
        {
            if (qq -> x == i && qq -> y == j) continue;
            if (turns_left > dist[i][j].turns + dist[i][j].wat)
                Hexes[i][j].shined = 2;
            else if (dist[i][j].turns + dist[i][j].wat == turns_left)
                if (Hexes[i][j].town == NULL) Hexes[i][j].shined = 1;
                    else continue;
            Hexes[i][j].turn_waste = dist[i][j].turns;
            Hexes[i][j].water_waste = dist[i][j].wat;
            add_path(i, j);
        }
}

void General :: clicked()
{
    vii now(0);
    vectors_for_cell.clear();
    go_to_cell.clear();
    if (color == ENGLAND && game_with_features)
    {
        shine_england(this);
        return;
    }
    else if (color == USA && game_with_features)
    {
        shine_usa(this);
        return;
    }
    for (int i=0; i<6; i++)
    {
        int nx = x + moves[x%2][i].fi, ny = y + moves[x%2][i].se;
        if (good(nx, ny) && chosen_country[cur_turn%2] != UKRAINE && Hexes[nx][ny].village)
            continue;
        if (!good(nx, ny) || (turns_left == 1 && Hexes[nx][ny].town != NULL)) continue;
        now.pb({nx, ny});
        Hexes[nx][ny].shined = turns_left;
        Hexes[nx][ny].turn_waste = 1;
        if (nx%2 == 0 && nx != x)
        {
            if (nx > x)
            {
                if (ny == y)
                    vectors_for_cell[mp(nx,ny)] = up_right(), go_to_cell[mp(nx, ny)].fi = 2;
                if (ny > y)
                    vectors_for_cell[mp(nx,ny)] = down_right(), go_to_cell[mp(nx, ny)].fi = 3;
            }
            else if (nx < x)
            {
                if (ny == y)
                    vectors_for_cell[mp(nx,ny)] = up_left(), go_to_cell[mp(nx, ny)].fi = 6;
                if (ny > y)
                    vectors_for_cell[mp(nx,ny)] = down_left(), go_to_cell[mp(nx, ny)].fi = 5;
            }
        }
        else if (nx == x)
        {
            if (ny > y) vectors_for_cell[mp(nx, ny)] = down(), go_to_cell[mp(nx, ny)].fi = 4;
                else vectors_for_cell[mp(nx, ny)] = up(), go_to_cell[mp(nx, ny)].fi = 1;
        }
        else
        {
            if (nx > x)
            {
                if (ny < y)
                    vectors_for_cell[mp(nx,ny)] = up_right(), go_to_cell[mp(nx, ny)].fi = 2;
                if (ny == y)
                    vectors_for_cell[mp(nx,ny)] = down_right(), go_to_cell[mp(nx, ny)].fi = 3;
            }
            else
            {
                if (ny < y)
                    vectors_for_cell[mp(nx,ny)] = up_left(), go_to_cell[mp(nx, ny)].fi = 6;
                if (ny == y)
                    vectors_for_cell[mp(nx,ny)] = down_left(), go_to_cell[mp(nx, ny)].fi = 5;
            }
        }
    }
    if (turns_left > 1)
    {
        for (int i=0; i<now.size(); i++)
        {
            int xx = now[i].fi, yy = now[i].se;
            for (int j=0; j<6; j++)
            {
                int nx = xx + moves[xx%2][j].fi, ny = yy + moves[xx%2][j].se;
                if (good(nx, ny) && chosen_country[cur_turn%2] != UKRAINE && Hexes[nx][ny].village)
                    continue;
                if (!good(nx, ny) || Hexes[nx][ny].town != NULL || vectors_for_cell[mp(nx, ny)].size()) continue;
                Hexes[nx][ny].shined = 1;
                Hexes[nx][ny].turn_waste = 2;
                go_to_cell[mp(nx, ny)].fi = go_to_cell[mp(xx,yy)].fi;
                if (nx%2 == 0 && nx != xx)
                {
                    if (nx > xx)
                    {
                        if (ny == yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_right(),
                            go_to_cell[mp(nx, ny)].se = 2;
                        if (ny > yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_right(),
                            go_to_cell[mp(nx, ny)].se = 3;
                    }
                    else if (nx < xx)
                    {
                        if (ny == yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_left(),
                            go_to_cell[mp(nx, ny)].se = 6;
                        if (ny > yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_left(),
                            go_to_cell[mp(nx, ny)].se = 5;
                    }
                }
                else if (nx == xx)
                {
                    if (ny > yy) vectors_for_cell[mp(nx, ny)] = vectors_for_cell[mp(xx, yy)] + down(),
                        go_to_cell[mp(nx, ny)].se = 4;
                    else vectors_for_cell[mp(nx, ny)] = vectors_for_cell[mp(xx, yy)] + up(),
                        go_to_cell[mp(nx, ny)].se = 1;
                }
                else
                {
                    if (nx > xx)
                    {
                        if (ny < yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_right(),
                            go_to_cell[mp(nx, ny)].se = 2;
                        if (ny == yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_right(),
                            go_to_cell[mp(nx, ny)].se = 3;
                    }
                    else
                    {
                        if (ny < yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + up_left(),
                            go_to_cell[mp(nx, ny)].se = 6;
                        if (ny == yy)
                            vectors_for_cell[mp(nx,ny)] = vectors_for_cell[mp(xx, yy)] + down_left(),
                            go_to_cell[mp(nx, ny)].se = 5;
                    }
                }
            }
        }
    }
}

void renew_turns()
{
    for (auto x : player_general[0])
        x -> turns_left = 2,
        x -> water_moving = 1,
        x -> cur_move.clear();
    for (auto x : player_general[1])
        x -> turns_left = 2,
        x -> water_moving = 1,
        x -> cur_move.clear();
    for (auto x : ourSquads)
        x -> moving = 0;
}

void log_generals(int who)
{
    buf.close();
    buf.clear();
    buf.open("buf.txt", ios :: app | ios :: in);
//    cout << buf.good() << " !\n";
    log << "\n";
    for (auto x : player_general[who])
    {
        log << x -> id;
        buf << x -> id;
        if (x -> cur_move.empty())
            log << " " << 0,
            buf << " " << 0;
        for (auto y : x -> cur_move)
            log << " " << y,
            buf << " " << y;
        if (x -> cur_move.size() == 1 && x -> cur_move[0] > 0)
            log << " " << 0,
            buf << " " << 0;
        log << " ";
        buf << " ";
    }
    if (player[who] == PC) log << "\n";
    buf.close();
}

map <General*, bool> used;

void log_generals_file(int who)
{
    used.clear();
    buf.close();
    buf.clear();
    buf.open("buf.txt", ios :: app | ios :: in);
//    cout << buf.good() << " !\n";
    log << "\n";
    for (auto x : vecans)
    {
        if (used[x]) continue;
        used[x] = 1;
        log << x -> id;
        buf << x -> id;
        if (x -> cur_move.empty())
            log << " " << 0,
            buf << " " << 0;
        for (auto y : x -> cur_move)
            log << " " << y,
            buf << " " << y;
        if (x -> cur_move.size() == 1 && x -> cur_move[0] > 0)
            log << " " << 0,
            buf << " " << 0;
        log << " ";
        buf << " ";
    }
    for (auto x : player_general[who])
    {
        if (used[x]) continue;
        used[x] = 1;
        log << x -> id;
        buf << x -> id;
        if (x -> cur_move.empty())
            log << " " << 0,
            buf << " " << 0;
        for (auto y : x -> cur_move)
            log << " " << y,
            buf << " " << y;
        if (x -> cur_move.size() == 1 && x -> cur_move[0] > 0)
            log << " " << 0,
            buf << " " << 0;
        log << " ";
        buf << " ";
    }
    if (player[who] == PC) log << "\n";
    buf.close();
}
