#include "save_game.h"
#include "loading_game.h"
#include "global_vars.h"
#include "textures.h"
#include "save_game.h"

string get_current_time()
{
    time_t now=time(NULL);
    stringstream stt;
    stt<<ctime(&now);
    string s=stt.str();
    string res="";
    res+=s[8];
    res+=s[9];
    res+='.';
    if (s.substr(4,3)=="Jan")
        res+="01";
    if (s.substr(4,3)=="Feb")
        res+="02";
    if (s.substr(4,3)=="Mar")
        res+="03";
    if (s.substr(4,3)=="Apr")
        res+="04";
    if (s.substr(4,3)=="May")
        res+="05";
    if (s.substr(4,3)=="Jun")
        res+="06";
    if (s.substr(4,3)=="Jul")
        res+="07";
    if (s.substr(4,3)=="Aug")
        res+="08";
    if (s.substr(4,3)=="Sep")
        res+="09";
    if (s.substr(4,3)=="Oct")
        res+="10";
    if (s.substr(4,3)=="Nov")
        res+="11";
    if (s.substr(4,3)=="Dec")
        res+="12";
    res+='.';
    res+=s.substr(s.length()-5,4);
    res+='_';
    res+=s.substr(11,8);
    return res;
}

void save_game()
{
    string where="Save_"+get_current_time();
    auto dop0=remember1;
    dop0.clear();
    dop0.pb(where);
    for (auto i:remember1)
        dop0.pb(i);
    remember1=dop0;

    remove("load_data.txt");
    ofstream load_data("load_data.txt");
    for (auto i:remember1)
        load_data<<i<<"\n";

    load_data.close();
    for (auto &i:where)
        if (i=='.'||i==':') i='_';
    string way=where;
    way="saves\\"+way+".txt";
    ofstream fout;
    fout.open(way.data());

    /// game_with_features
    /// chosen_country[0] chosen_country[1]
    /// N M all_turns cur_turns mode difficulty
    /// Player1 Player2
    /// matrix of relief
    /// matrix of color
    /// in N*M lines :: forts
        /// first_color use_partizan
    /// in N*M lines :: general
        /// id name color turns_left water_moving
    /// matrix of village
    /// Town1 Town2

    fout<<game_with_features<<"\n";
    fout<<chosen_country[0] << " " << chosen_country[1] << "\n";
    fout<<N<<" "<<M<<" "<<Turns<<" "<<cur_turn<<" "<<Mode<< " " << difficulty << "\n";
    fout<<player[0]<<" "<<player[1]<<"\n";

    pii ans1,ans2;
    for (auto i:Hexes)
        for (auto j:i)
            if (j.town!=NULL)
                if (j.color==chosen_country[0])
                    ans1=mp(j.x,j.y);
                else
                    ans2=mp(j.x,j.y);

    for (auto i:Hexes)
    {
        for (auto j:i)
            fout<<j.relief<<" ";
        fout<<"\n";
    }

    for (auto i:Hexes)
    {
        for (auto j:i)
            fout<<j.color<<" ";
        fout<<"\n";
    }

    for (auto i:Hexes)
    {
        for (auto j:i)
        {
            if (j.fort==NULL)
            {
                fout<<0<<"\n";
                continue;
            }
            fout<<1<<" ";
            fout<<j.fort -> first_color<<" "<<j.fort -> use_partizan<<"\n";
        }
    }

    for (auto i:Hexes)
        for (auto j:i)
            if (j.general!=NULL)
                fout<<1<<" "<<j.general->id <<" "<<j.general->name<<" "<<j.general->color<<" "<<j.general->turns_left<<" "<<j.general->water_moving<<"\n";
            else
                fout<<0<<"\n";

    for (auto i:Hexes)
    {
        for (auto j:i)
            fout<<j.village<<" ";
        fout<<"\n";
    }

    fout<<ans1.first<<" "<<ans1.second<<"\n";
    fout<<ans2.first<<" "<<ans2.second<<"\n";

    fout.close();
}

void load_game(string s)
{
    //cerr<<"loading... "<<s<<"\n";
    string way=s;
    for (auto &i:way)
        if (i=='.'||i==':') i='_';
    way="saves\\"+way+".txt";
    ifstream fin(way.data());

    fin>>game_with_features;
    fin>>chosen_country[0]>>chosen_country[1];
    fin>>N>>M>>Turns>>cur_turn>>Mode>>difficulty;
    fin>>player[0]>>player[1];

    vector<vector<Cell>> result;
    result.resize(N);
    for (int i=0;i<N;i++)
        result[i].resize(M);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            result[i][j] = *(new Cell(i, j, EMPTY));

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            fin>>result[i][j].relief;

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            fin>>result[i][j].color;

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
        {
            bool is_fort;
            fin>>is_fort;
            if (!is_fort) continue;
            int first_color_,use_partizan_;
            fin>>first_color_>>use_partizan_;
            result[i][j].fort=new Fort(i,j,result[i][j].color,first_color_,use_partizan_);
        }

    player_general[0].clear();
    player_general[1].clear();

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
        {
            bool is_general;
            fin>>is_general;
            if (is_general==0) continue;
            string name_;
            int color_,turns_left_,id_,water_moving_;
            fin>>id_>>name_>>color_>>turns_left_>>water_moving_;
            result[i][j].general=new General(id_,i,j,name_,color_,turns_left_,water_moving_);
            if (color_ == chosen_country[0]) player_general[0].insert(result[i][j].general);
            if (color_ == chosen_country[1]) player_general[1].insert(result[i][j].general);
        }

    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            fin>>result[i][j].village;

    int xx,yy;

    fin>>xx>>yy;
    result[xx][yy].town=new Town(xx,yy,result[xx][yy].color);
    town[0] = result[xx][yy].town;

    fin>>xx>>yy;
    result[xx][yy].town=new Town(xx,yy,result[xx][yy].color);
    town[1] = result[xx][yy].town;

    fin.close();

    /// if it's will work
    Hexes=result;
}

void load_last_game()
{
    if (remember1.empty()) return;
    load_game(remember1.front());
}

void delete_pressed_file()
{
    string s;
    for (auto i:listik)
        if (i.first.pressed)
        {
            s=i.second;
            i.first.pressed=false;
        }
    if (s==remember1.back())
        pointer=max(pointer-1,0);
    vector<string> dop0;
    dop0.clear();
    for (auto i:remember1)
        if (i!=s)
            dop0.pb(i);
    remember1=dop0;
    for (auto &i:s)
        if (i=='.'||i==':')
            i='_';
    s="saves\\"+s+".txt";
    remove(s.data());
    remove("load_data.txt");
    freopen("load_data.txt","w",stdout);
    for (auto i:remember1)
        cout<<i<<"\n";
    init_listik();
}
