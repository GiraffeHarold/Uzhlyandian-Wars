#include "hard_intellect.h"
#include "intellect.h"

bool chosen_to_build[100][100];
vector <third_regime_turn> moveNow;
int dist0[100][100], dist1[100][100], dist_from_town[100][100], current;
pii pred0[100][100];
const int inf = 1e9;
const ld priority_epsilon = 0.0;
vector <Squad*> ourSquads;
map <General*, Squad*> whatSquad;
ofstream debugger("chosen_cells.txt"), debug_in_train;

void init_distance(int color)
{
    int x, y;
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
        {
            if (Hexes[i][j].town != NULL && Hexes[i][j].color == color) x = i, y = j;
            dist_from_town[i][j] = inf;
        }
    dist_from_town[x][y] = 0;
    queue<pii> q;
    while (!q.empty())
        q.pop();
    q.push(mp(x, y));
    while (!q.empty())
    {
        pii current_queue_element = q.front();
        q.pop();
        int x = current_queue_element.fi, y = current_queue_element.se;
        for (auto w : moves[x%2])
        {
            int nx = x + w.fi, ny = y + w.se;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (Hexes[nx][ny].relief == MOUNTAIN) continue;
            if (dist_from_town[nx][ny] == inf)
                dist_from_town[nx][ny] = dist_from_town[x][y] + 1,
                q.push({nx, ny});
        }
    }
}

Squad :: Squad()
{
    this -> type = 0;
    this -> moving = 0;
    this -> build_here = {-1, -1};
    this -> members = *new vector<General*> (0);
}

Squad :: Squad(int type)
{
    this -> type = type;
    this -> moving = 0;
    this -> build_here = {-1, -1};
    this -> members = *new vector<General*> (0);
}

int Squad :: size()
{
    return this -> members.size();
}

void Squad :: add(General *to_add)
{
    this -> members.push_back(to_add);
    whatSquad[to_add] = this;
}

bool can_set(General *me, int x, int y)
{
    return (Hexes[x][y].relief == EMPTY
            && Hexes[x][y].town == NULL
            && Hexes[x][y].fort == NULL
            && (Hexes[x][y].general == NULL || Hexes[x][y].general == me));
}

void createMove(General *now, pii where, bool set_)
{
    now -> clicked();
    int x = where.fi, y = where.se;
    bool can = 0;
    if ((Hexes[x][y].shined == 2 || (now -> x == x && now -> y == y))
        && can_set(now, x, y)
        && set_) can = 1;
    moveNow.push_back(third_regime_turn(now, x, y, can));
    cout << " NEW MOVE CREATED "  << now -> x << " " << now -> y << " -> " << x << " " << y << " setting fort: " << can << "\n";
}

ld calc_attack_power(General *now, int cx, int cy)
{
    int x = now -> x, y = now -> y;
//    cerr << "         calcing attack power from " << x << " " << y << "\n";
    queue <pii> q;
    while (!q.empty())

        q.pop();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            dist1[i][j] = inf;
    dist1[x][y] = 0;
    q.push(mp(x, y));
    while (!q.empty())
    {
        pii now = q.front();
        q.pop();
        int x = now.fi, y = now.se;
        for (auto w : moves[x%2])
        {
            int nx = x + w.fi, ny = y + w.se;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (Hexes[nx][ny].relief == MOUNTAIN
                || Hexes[nx][ny].town != NULL
                || Hexes[nx][ny].general != NULL ) continue;
            if (dist1[nx][ny] == inf)
                dist1[nx][ny] = dist1[x][y] + 1,
                q.push({nx, ny});
        }
    }
    if (dist1[cx][cy] == inf) return 0;
//    cerr << "             distance " << dist1[cx][cy] << "\n";
    vector <ld> ranks(0);
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (dist1[i][j] != inf && dist1[i][j] != 0) ranks.push_back(priority(i, j, now->color) / dist1[i][j]);
    sort(ranks.begin(), ranks.end());
    int num = lower_bound(ranks.begin(),ranks.end(),priority(cx, cy, now->color)/dist1[cx][cy]) - ranks.begin() + 1;
    ld koeff = 2.0/(num - sqrt(num) + 1);
    return koeff * priority(cx, cy, now -> color) / dist1[cx][cy];
}

ld under_attack(int x, int y)
{
    int color = chosen_country[(cur_turn+1)%2];
    vector <General*> attacking(0);
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            if (Hexes[i][j].general != NULL && Hexes[i][j].general -> color == color)
                attacking.push_back(Hexes[i][j].general);
    ld ans = 0;
    for (auto w : attacking)
        ans += calc_attack_power(w, x, y);
    return ans;
}

ld calc_defence_power(Squad *cur_squad, int cx, int cy)
{
    ld ans = 0;
    for (auto wh : cur_squad -> members)
    {
        int x = wh -> x, y = wh -> y;
        queue <pii> q;
        while (!q.empty())
            q.pop();
        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++)
                dist1[i][j] = inf;
        dist1[x][y] = 0;
        q.push(mp(x, y));
        while (!q.empty())
        {
            pii now = q.front();
            q.pop();
            int x = now.fi, y = now.se;
            for (auto w : moves[x%2])
            {
                int nx = x + w.fi, ny = y + w.se;
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
                if (Hexes[nx][ny].relief == MOUNTAIN
                    || Hexes[nx][ny].town != NULL
                    || Hexes[nx][ny].general != NULL ) continue;
                if (dist1[nx][ny] == inf)
                    dist1[nx][ny] = dist1[x][y] + 1,
                    q.push({nx, ny});
            }
        }
        if (dist1[cx][cy] == inf) continue;
        ld d = dist1[cx][cy];
        ans += 10.0 / (1 + sqrt(d));
    }
    return ans;
}

ld under_our_defence(int x, int y)
{
    int color = chosen_country[cur_turn%2];
    ld ans = 0;
    for (auto w : ourSquads)
    {
        ld k;
        if (w -> type == DEFENCE) k = 2;
        if (w -> type == ATTACK) k = 0.7;
        if (w -> type == BUILDER) k = 0.2;
        ans += k * calc_defence_power(w, x, y);
    }
    return ans;
}

ld calc_priority_to_build(General* me, int x, int y)
{
//    cerr << "  calcing for " << x << " " << y << "\n";
    ld penalty = 0;
//    cerr << "   can we set here " << can_set(me, x, y)  << "\n";
    if (!can_set(me, x, y) && !Hexes[x][y].town) return -inf/10;
    else if (Hexes[x][y].town) return -inf;
    penalty += under_attack(x, y) * (cur_turn % 2 ? -1 : 1);
//    cerr << "     calced under attack\n";
//    penalty -= under_our_defence(x, y);
//    cerr << "     calced under defence\n";
    ld ans = 17.7 * (Hexes[x][y].color != chosen_country[cur_turn%2]);

    for (auto w : moves[x%2])
    {
        int nx = x + w.fi, ny = y + w.se;
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        ld koeff = 0;
        koeff += 12.4 * (Hexes[nx][ny].color != chosen_country[cur_turn%2]);
        koeff += 6.5 * (Hexes[nx][ny].relief != EMPTY);
        koeff += 6.5 * (Hexes[nx][ny].fort != NULL);
        koeff += 150 * (me -> id < 2 && Hexes[nx][ny].town != NULL && Hexes[nx][ny].color != me -> color);
        koeff -= 60 * (chosen_to_build[nx][ny]);
        koeff += 12 * (Hexes[nx][ny].general != NULL) * ((Hexes[nx][ny].general != NULL && Hexes[nx][ny].general -> color == me -> color) ? -1 : 1);
        for (auto ww : moves[nx%2])
        {
            int nnx = nx + ww.fi, nny = ny + ww.se;
            if (nnx < 0 || nnx >= N || nny < 0 || nny >= M) continue;
            ld koeff = 0;
            koeff += 1.4 * (Hexes[nnx][nny].color != chosen_country[cur_turn%2]);
            koeff -= 25 * (chosen_to_build[nnx][nny]);
            koeff += 5 * (Hexes[nx][ny].general != NULL) * ((Hexes[nx][ny].general != NULL && Hexes[nx][ny].general -> color == me -> color) ? -1 : 1);
        }
        ans += koeff * 0.5;

    }

    ld added = 0;
    int d = dist_from_town[x][y];
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
        {
            if (Hexes[i][j].general && Hexes[i][j].general -> color == me -> color && dist_from_town[i][j] < d)
                added++;
        }
    added -= cur_turn/2 - me -> id;
    added *= 15;
//    cerr << "       calced all " << ans - added - penalty << "\n";
    return ans - penalty;
}

ld calc_attack_prior(General *me, int x, int y)
{
    if (Hexes[x][y].town != NULL) return -inf;
    ld ans = -30 * sqrt(dist_from_town[x][y]);
    if (chosen_to_build[x][y]) ans -= inf;
    for (auto w : moves[x % 2])
    {
        int nx = x + w.fi, ny = y + w.se;
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        ans += Hexes[x][y].general != NULL;
        ans += 13 * (Hexes[x][y].relief == MOUNTAIN);
    }
    return ans;

}

void bfs(Squad *cur_squad, General *now)
{
//    cerr << "We are in BFS\n";
    int x = now -> x, y = now -> y;
    queue <pii> q;
    while (!q.empty())
        q.pop();
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            dist0[i][j] = inf, pred0[i][j] = {-1, -1};
    dist0[x][y] = 0;
    q.push(mp(x, y));
//    cerr << "We inited queue\n";
    while (!q.empty())
    {
        pii current_queue_element = q.front();
        q.pop();
        int x = current_queue_element.fi, y = current_queue_element.se;
//        cerr << x << " " << y << "\n";
        for (auto w : moves[x%2])
        {
            int nx = x + w.fi, ny = y + w.se;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
//            cerr << "    " << nx << " " << ny << "\n";
            if (Hexes[nx][ny].relief == MOUNTAIN
                || Hexes[nx][ny].town != NULL
                || (Hexes[nx][ny].general != NULL) ) continue;
            if (dist0[nx][ny] == inf)
                dist0[nx][ny] = dist0[x][y] + 1,
                pred0[nx][ny] = {x, y},
                q.push({nx, ny});
        }
    }
//    cerr << "BFS ended\n";
    int tx = cur_squad -> build_here.fi, ty = cur_squad -> build_here.se;
    if (tx != -1
        && (rand()%2 == 0 || !can_set(now, tx, ty)));
        chosen_to_build[tx][ty] = 0, tx = -1, ty = -1;
    vector<pair<ld, pii> > Rank(0), goodRank(0);
    pii choose = {-1, -1};
//    cerr << "cleared_chosen_if_needed\n";
    if (tx == -1)
        {
//            cerr << "finding_new_chosen\n";
            for (int i=0; i<N; i++)
                for (int j=0; j<M; j++)
                    if (dist0[i][j] != inf) Rank.push_back({(current == BUILDER?calc_priority_to_build(now, i, j):calc_attack_prior(now, i, j)), {i, j} });
//            cerr << "ranks are done\n";
            sort(Rank.begin(), Rank.end());
            reverse(Rank.begin(), Rank.end());
            for (int i=0; i<int(Rank.size()) && goodRank.size() < 3; i++)
            {
                int x = Rank[i].se.fi, y = Rank[i].se.se;
//                cerr << x << " " << y << " " << (dist0[x][y] + 2) / 2 << " " << Rank[i].fi << "\n";
                if ((dist0[x][y] + 2)/2 <= Turns - cur_turn / 2 && !chosen_to_build[x][y]) goodRank.push_back(Rank[i]);
            }
//            cerr << "goodRanks are done " << goodRank.size() << "\n";
            if (goodRank.size() == 3)
            {
//                cerr << " size is 3 \n";
                int diff = goodRank[0].fi - goodRank[1].fi;
//                cerr << "   diff " << diff << "\n";
                if (diff > priority_epsilon)
                    choose = goodRank[0].se;
                diff = rand()%11;
//                cerr << "   random " << diff << "\n";
                if (choose.fi == -1)
                {
                    if (diff < 7)
                        choose = goodRank[0].se;
                    else if (diff < 10)
                        choose = goodRank[1].se;
                    else choose = goodRank[2].se;
                }
                cur_squad -> build_here = choose;
            }
            else if (goodRank.size() == 2)
            {
                int diff = goodRank[0].fi - goodRank[1].fi;
                if (diff > priority_epsilon)
                    choose = goodRank[0].se;
                diff = rand()%11;
                if (choose.fi == -1)
                {
                    if (diff < 8)
                        choose = goodRank[0].se;
                    else
                        choose = goodRank[1].se;
                }
               cur_squad -> build_here = choose;
            }
            else if (goodRank.size())
                cur_squad -> build_here = goodRank[0].se;
            else return;
        }
    general_chosen -> clicked();
    pii pos = cur_squad -> build_here;
//    cerr << "   current pos " << pos.fi << " " << pos.se << "\n";
    chosen_to_build[pos.fi][pos.se] = 1;
    if (pos.fi == now -> x && pos.se == now -> y)
    {
        createMove(now, pos, (Turns - cur_turn/2 <= 1));
        return;
    }
    while (dist0[pos.fi][pos.se] > 2)
    {
//        cerr << "   current pos " << pos.fi << " " << pos.se << "\n";
        pii next = pred0[pos.fi][pos.se];
        pos = next;
    }
    if (Hexes[pos.fi][pos.se].general != NULL && Hexes[pos.fi][pos.se].general != now)
    {
        cur_squad -> moving--;
        swap(whatSquad[Hexes[pos.fi][pos.se].general] -> build_here, cur_squad -> build_here);
        whatSquad[Hexes[pos.fi][pos.se].general] -> move();
        return;
    }
    if (pred0[pos.fi][pos.se].fi != -1)
    {
        int nx = pred0[pos.fi][pos.se].fi, ny = pred0[pos.fi][pos.se].se;
        if (Hexes[nx][ny].general != NULL && Hexes[nx][ny].general != now)
        {
            cur_squad -> moving--;
            swap(whatSquad[Hexes[nx][ny].general] -> build_here, cur_squad -> build_here);
            whatSquad[Hexes[nx][ny].general] -> move();
            return;
        }
    }
    createMove(now, pos, (Turns - cur_turn/2 <= 1));
//    cerr << "created move\n";
}

void Squad :: move_builder()
{
    again1:
        for (int i=0; i<size(); i++)
        {
            if (members[i] -> x == -1)
            {
                members.erase(i + members.begin());
                goto again1;
            }
        }
    if (members.empty()) return;
    init_distance(chosen_country[(cur_turn+1) % 2]);

    current = BUILDER;
    general_chosen = members[moving];
    if (dist_from_town[general_chosen -> x][general_chosen -> y] < Turns - cur_turn*2 /*&& rand()%4*/)
    {
        current = ATTACK;
        convert(ATTACK);
    } else init_distance(chosen_country[cur_turn % 2]);
    bfs(this, general_chosen);
    moving++;
}

void Squad :: move_attack()
{
  again2:
    for (int i=0; i<size(); i++)
    {
        if (members[i] -> x == -1)
        {
            members.erase(i + members.begin());
            goto again2;
        }
    }

    if (members.empty()) return;
    init_distance(chosen_country[(cur_turn+1) % 2]);
    current = ATTACK;
    general_chosen = members[moving];
    bfs(this, general_chosen);
    moving++;

}

void Squad :: convert(int new_type)
{
    type = new_type;
}

int cnt_empty(General *me)
{

    int ans = 0;
    int x = me -> x, y = me -> y;
    for (auto w : moves[x % 2])
    {
        int nx = x + w.fi, ny = y + w.se;

        if (nx < 0 || nx >= N || ny < 0 || ny >= M)
            continue;

        if (Hexes[nx][ny].general && Hexes[nx][ny].general -> color != me -> color)
            continue;
        if (Hexes[nx][ny].general)
            if (whatSquad[Hexes[nx][ny].general] -> type == DEFENCE)
                continue;
        if (Hexes[nx][ny].relief == MOUNTAIN)
            continue;
        ans++;
    }
    return ans;
}

pii last_defender_pos = {-1, -1};

void Squad :: move_defence()
{
    again3:
    for (int i=0; i<size(); i++)
    {
        if (members[i] -> x == -1)
        {
            members.erase(i + members.begin());
            goto again3;
        }
    }

//    cout << "DEFENDERS: \n";
//    for (auto w : members)
//        cout << "        " << w -> x << " " << w -> y << "\n";
//    cout << "\n";
    init_distance(chosen_country[(cur_turn + 1) % 2]);
    if (members.empty()) return;
    General *last = members[0];

//    cout << "distance_inited ";
//    cout << cnt_empty(last) << "\n";
    if (cnt_empty(last) > 2 && !moving)
    {
//        cout << "!!!\n";
        members.erase(members.begin());
        ourSquads.pb(new Squad(BUILDER));
        ourSquads.back() -> add(last);
        ourSquads.back() -> move();
        return;
    }
    if (members.empty()) return;
    int x = members[0] -> x, y = members[0] -> y;
    if (!moving)
    {
        vector <pair <int, pii> > can_now(0);
        for (auto w : moves[x % 2])
        {
            int nx = x + w.fi, ny = y + w.se;
            if (nx < 0 || nx >= N || ny < 0 || ny >= M)
                continue;
            if (Hexes[nx][ny].general || Hexes[nx][ny].town)
                continue;
            if (Hexes[nx][ny].relief == MOUNTAIN)
                continue;
            can_now.pb({dist_from_town[nx][ny], {nx, ny} });
            moving++;
            last_defender_pos = {x, y};

        }
        if (!can_now.size())
        {
            members.erase(members.begin());
            ourSquads.pb(new Squad(BUILDER));
            ourSquads.back() -> add(last);
            ourSquads.back() -> move();
            return;
        }
        sort(can_now.begin(), can_now.end());
        int nx = can_now[0].se.fi, ny = can_now[0].se.se;
        createMove(members[0], {nx, ny}, Turns - cur_turn / 2 <= 1);
    } else
    {
        createMove(members[moving], last_defender_pos, Turns - cur_turn / 2 <= 1);
        last_defender_pos = {members[moving] -> x, members[moving] -> y};
        moving++;
        return;
    }
}

void Squad :: move()
{
    if (type == ATTACK)
        move_attack();
    if (type == DEFENCE)
        move_defence();
    if (type == BUILDER)
        move_builder();
}

