#include "textures.h"
#include "basic_classes.h"

GLuint get_info_button, fortex_active, fortex_passive, menu_background, logo, logo_team;
int ramka;
vector<string> remember1;
texture no_save,fone;
texture ramka_for_score;
texture village_texture[3];

GLuint Load(GLuint& temp, std::string b)
{
    temp = ilLoadImage(b.data());
    glGenTextures(1, &temp);
    glBindTexture (GL_TEXTURE_2D, temp);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //cout << b + " loaded as number " << temp << "\n";
    return temp;
}

GLuint Load(std::string b)
{
    GLuint temp = ilLoadImage(b.data());
    glGenTextures(1, &temp);
    glBindTexture (GL_TEXTURE_2D, temp);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //cout << b + " loaded as number " << temp << "\n";
    return temp;
}

void LoadCountries()
{

    Load(relief_texture[EMPTY][FRANCE][0], "textures\\relief\\france\\grass_france.png");
    Load(relief_texture[EMPTY][FRANCE][1], "textures\\relief\\france\\grass_france_navedeno.png");
    Load(relief_texture[EMPTY][FRANCE][2], "textures\\relief\\france\\grass_france_pr.png");
    Load(relief_texture[MOUNTAIN][FRANCE][0], "textures\\relief\\france\\rock_france.png");
    Load(relief_texture[MOUNTAIN][FRANCE][1], "textures\\relief\\france\\rock_france_navedeno.png");
    Load(relief_texture[MOUNTAIN][FRANCE][2], "textures\\relief\\france\\rock_france_pr.png");
    Load(relief_texture[RIVER][FRANCE][0], "textures\\relief\\france\\RIVER_france.png");
    Load(relief_texture[RIVER][FRANCE][1], "textures\\relief\\france\\RIVER_france_navedeno.png");
    Load(relief_texture[RIVER][FRANCE][2], "textures\\relief\\france\\RIVER_france_pr.png");
    Load(relief_texture[FORT][FRANCE][0], "textures\\relief\\france\\Fort_france.png");
    Load(relief_texture[FORT][FRANCE][1], "textures\\relief\\france\\Fort_france_navedeno.png");
    Load(relief_texture[FORT][FRANCE][2], "textures\\relief\\france\\Fort_france_pr.png");
    Load(relief_texture[SNOW][FRANCE][0], "textures\\relief\\france\\snow_france.png");
    Load(relief_texture[SNOW][FRANCE][1], "textures\\relief\\france\\snow_france_navedeno.png");
    Load(relief_texture[SNOW][FRANCE][2], "textures\\relief\\france\\snow_france_pr.png");


    Load(relief_texture[EMPTY][ENGLAND][0], "textures\\relief\\britain\\grass_britain.png");
    Load(relief_texture[EMPTY][ENGLAND][1], "textures\\relief\\britain\\grass_britain_navedeno.png");
    Load(relief_texture[EMPTY][ENGLAND][2], "textures\\relief\\britain\\grass_britain_pr.png");
    Load(relief_texture[MOUNTAIN][ENGLAND][0], "textures\\relief\\britain\\rock_britain.png");
    Load(relief_texture[MOUNTAIN][ENGLAND][1], "textures\\relief\\britain\\rock_britain_navedeno.png");
    Load(relief_texture[MOUNTAIN][ENGLAND][2], "textures\\relief\\britain\\rock_britain_pr.png");
    Load(relief_texture[RIVER][ENGLAND][0], "textures\\relief\\britain\\RIVER_britain.png");
    Load(relief_texture[RIVER][ENGLAND][1], "textures\\relief\\britain\\RIVER_britain_navedeno.png");
    Load(relief_texture[RIVER][ENGLAND][2], "textures\\relief\\britain\\RIVER_britain_pr.png");
    Load(relief_texture[FORT][ENGLAND][0], "textures\\relief\\britain\\Fort_britain.png");
    Load(relief_texture[FORT][ENGLAND][1], "textures\\relief\\britain\\Fort_britain_navedeno.png");
    Load(relief_texture[FORT][ENGLAND][2], "textures\\relief\\britain\\Fort_britain_pr.png");
    Load(relief_texture[SNOW][ENGLAND][0], "textures\\relief\\britain\\snow_britain.png");
    Load(relief_texture[SNOW][ENGLAND][1], "textures\\relief\\britain\\snow_britain_navedeno.png");
    Load(relief_texture[SNOW][ENGLAND][2], "textures\\relief\\britain\\snow_britain_pr.png");


    Load(relief_texture[EMPTY][UKRAINE][0], "textures\\relief\\ukrain\\grass_ukrain.png");
    Load(relief_texture[EMPTY][UKRAINE][1], "textures\\relief\\ukrain\\grass_ukrain_navedeno.png");
    Load(relief_texture[EMPTY][UKRAINE][2], "textures\\relief\\ukrain\\grass_ukrain_pr.png");
    Load(relief_texture[MOUNTAIN][UKRAINE][0], "textures\\relief\\ukrain\\rock_ukrain.png");
    Load(relief_texture[MOUNTAIN][UKRAINE][1], "textures\\relief\\ukrain\\rock_ukrain_navedeno.png");
    Load(relief_texture[MOUNTAIN][UKRAINE][2], "textures\\relief\\ukrain\\rock_ukrain_pr.png");
    Load(relief_texture[RIVER][UKRAINE][0], "textures\\relief\\ukrain\\RIVER_ukrain.png");
    Load(relief_texture[RIVER][UKRAINE][1], "textures\\relief\\ukrain\\RIVER_ukrain_navedeno.png");
    Load(relief_texture[RIVER][UKRAINE][2], "textures\\relief\\ukrain\\RIVER_ukrain_pr.png");
    Load(relief_texture[FORT][UKRAINE][0], "textures\\relief\\ukrain\\Fort_ukrain.png");
    Load(relief_texture[FORT][UKRAINE][1], "textures\\relief\\ukrain\\Fort_ukrain_navedeno.png");
    Load(relief_texture[FORT][UKRAINE][2], "textures\\relief\\ukrain\\Fort_ukrain_pr.png");
    Load(relief_texture[SNOW][UKRAINE][0], "textures\\relief\\ukrain\\snow_ukrain.png");
    Load(relief_texture[SNOW][UKRAINE][1], "textures\\relief\\ukrain\\snow_ukrain_navedeno.png");
    Load(relief_texture[SNOW][UKRAINE][2], "textures\\relief\\ukrain\\snow_ukrain_pr.png");


    Load(relief_texture[EMPTY][RUSSIA][0], "textures\\relief\\rusia\\grass_rusia.png");
    Load(relief_texture[EMPTY][RUSSIA][1], "textures\\relief\\rusia\\grass_rusia_navedeno.png");
    Load(relief_texture[EMPTY][RUSSIA][2], "textures\\relief\\rusia\\grass_rusia_pr.png");
    Load(relief_texture[MOUNTAIN][RUSSIA][0], "textures\\relief\\rusia\\rock_rusia.png");
    Load(relief_texture[MOUNTAIN][RUSSIA][1], "textures\\relief\\rusia\\rock_rusia_navedeno.png");
    Load(relief_texture[MOUNTAIN][RUSSIA][2], "textures\\relief\\rusia\\rock_rusia_pr.png");
    Load(relief_texture[RIVER][RUSSIA][0], "textures\\relief\\rusia\\RIVER_rusia.png");
    Load(relief_texture[RIVER][RUSSIA][1], "textures\\relief\\rusia\\RIVER_rusia_navedeno.png");
    Load(relief_texture[RIVER][RUSSIA][2], "textures\\relief\\rusia\\RIVER_rusia_pr.png");
    Load(relief_texture[FORT][RUSSIA][0], "textures\\relief\\rusia\\Fort_rusia.png");
    Load(relief_texture[FORT][RUSSIA][1], "textures\\relief\\rusia\\Fort_rusia_navedeno.png");
    Load(relief_texture[FORT][RUSSIA][2], "textures\\relief\\rusia\\Fort_rusia_pr.png");
    Load(relief_texture[SNOW][RUSSIA][0], "textures\\relief\\rusia\\snow_rusia.png");
    Load(relief_texture[SNOW][RUSSIA][1], "textures\\relief\\rusia\\snow_rusia_navedeno.png");
    Load(relief_texture[SNOW][RUSSIA][2], "textures\\relief\\rusia\\snow_rusia_pr.png");


    Load(relief_texture[EMPTY][USA][0], "textures\\relief\\usa\\grass_usa.png");
    Load(relief_texture[EMPTY][USA][1], "textures\\relief\\usa\\grass_usa_navedeno.png");
    Load(relief_texture[EMPTY][USA][2], "textures\\relief\\usa\\grass_usa_pr.png");
    Load(relief_texture[MOUNTAIN][USA][0], "textures\\relief\\usa\\rock_usa.png");
    Load(relief_texture[MOUNTAIN][USA][1], "textures\\relief\\usa\\rock_usa_navedeno.png");
    Load(relief_texture[MOUNTAIN][USA][2], "textures\\relief\\usa\\rock_usa_pr.png");
    Load(relief_texture[RIVER][USA][0], "textures\\relief\\usa\\RIVER_usa.png");
    Load(relief_texture[RIVER][USA][1], "textures\\relief\\usa\\RIVER_usa_navedeno.png");
    Load(relief_texture[RIVER][USA][2], "textures\\relief\\usa\\RIVER_usa_pr.png");
    Load(relief_texture[FORT][USA][0], "textures\\relief\\usa\\Fort_usa.png");
    Load(relief_texture[FORT][USA][1], "textures\\relief\\usa\\Fort_usa_navedeno.png");
    Load(relief_texture[FORT][USA][2], "textures\\relief\\usa\\Fort_usa_pr.png");
    Load(relief_texture[SNOW][USA][0], "textures\\relief\\usa\\snow_usa.png");
    Load(relief_texture[SNOW][USA][1], "textures\\relief\\usa\\snow_usa_navedeno.png");
    Load(relief_texture[SNOW][USA][2], "textures\\relief\\usa\\snow_usa_pr.png");


    Load(relief_texture[EMPTY][GERMANY][0], "textures\\relief\\germany_dark\\grass_germany.png");
    Load(relief_texture[EMPTY][GERMANY][1], "textures\\relief\\germany_dark\\grass_germany_navedeno.png");
    Load(relief_texture[EMPTY][GERMANY][2], "textures\\relief\\germany_dark\\grass_germany_pr.png");
    Load(relief_texture[MOUNTAIN][GERMANY][0], "textures\\relief\\germany_dark\\rock_germany.png");
    Load(relief_texture[MOUNTAIN][GERMANY][1], "textures\\relief\\germany_dark\\rock_germany_navedeno.png");
    Load(relief_texture[MOUNTAIN][GERMANY][2], "textures\\relief\\germany_dark\\rock_germany_pr.png");
    Load(relief_texture[RIVER][GERMANY][0], "textures\\relief\\germany_dark\\RIVER_gemany.png");
    Load(relief_texture[RIVER][GERMANY][1], "textures\\relief\\germany_dark\\RIVER_gemany_navedeno.png");
    Load(relief_texture[RIVER][GERMANY][2], "textures\\relief\\germany_dark\\RIVER_gemany_pr.png");
    Load(relief_texture[FORT][GERMANY][0], "textures\\relief\\germany_dark\\Fort_germany.png");
    Load(relief_texture[FORT][GERMANY][1], "textures\\relief\\germany_dark\\Fort_germany_navedeno.png");
    Load(relief_texture[FORT][GERMANY][2], "textures\\relief\\germany_dark\\Fort_germany_pr.png");
    Load(relief_texture[SNOW][GERMANY][0], "textures\\relief\\germany_dark\\snow_germany.png");
    Load(relief_texture[SNOW][GERMANY][1], "textures\\relief\\germany_dark\\snow_germany_navedeno.png");
    Load(relief_texture[SNOW][GERMANY][2], "textures\\relief\\germany_dark\\snow_germany_pr.png");

    Load(relief_texture[EMPTY][NONE][0], "textures\\relief\\standart\\grass.png");
    Load(relief_texture[EMPTY][NONE][1], "textures\\relief\\standart\\grass_navedeno.png");
    Load(relief_texture[EMPTY][NONE][2], "textures\\relief\\standart\\grass_pr.png");
    Load(relief_texture[MOUNTAIN][NONE][0], "textures\\relief\\standart\\rock.png");
    Load(relief_texture[MOUNTAIN][NONE][1], "textures\\relief\\standart\\rock_navedeno.png");
    Load(relief_texture[MOUNTAIN][NONE][2], "textures\\relief\\standart\\rock_pr.png");
    Load(relief_texture[RIVER][NONE][0], "textures\\relief\\standart\\RIVER.png");
    Load(relief_texture[RIVER][NONE][1], "textures\\relief\\standart\\RIVER_navedeno.png");
    Load(relief_texture[RIVER][NONE][2], "textures\\relief\\standart\\RIVER_pr.png");
    Load(relief_texture[FORT][NONE][0], "textures\\relief\\standart\\Fort.png");
    Load(relief_texture[FORT][NONE][1], "textures\\relief\\standart\\Fort_navedeno.png");
    Load(relief_texture[FORT][NONE][2], "textures\\relief\\standart\\Fort_pr.png");
    Load(relief_texture[SNOW][NONE][0], "textures\\relief\\standart\\snow.png");
    Load(relief_texture[SNOW][NONE][1], "textures\\relief\\standart\\snow_navedeno.png");
    Load(relief_texture[SNOW][NONE][2], "textures\\relief\\standart\\snow_pr.png");

    Load(town_sprite[FRANCE][0], "textures\\relief\\france\\castle_france.png");
    Load(town_sprite[FRANCE][1], "textures\\relief\\france\\castle_france_navedeno.png");
    Load(town_sprite[FRANCE][2], "textures\\relief\\france\\castle_france_pr.png");

    Load(town_sprite[UKRAINE][0], "textures\\relief\\ukrain\\castle_ukrain.png");
    Load(town_sprite[UKRAINE][1], "textures\\relief\\ukrain\\castle_ukrain_navedeno.png");
    Load(town_sprite[UKRAINE][2], "textures\\relief\\ukrain\\castle_ukrain_pr.png");

    Load(town_sprite[GERMANY][0], "textures\\relief\\germany_dark\\castle_germany.png");
    Load(town_sprite[GERMANY][1], "textures\\relief\\germany_dark\\castle_germany_navedeno.png");
    Load(town_sprite[GERMANY][2], "textures\\relief\\germany_dark\\castle_germany_pr.png");

    Load(town_sprite[USA][0], "textures\\relief\\usa\\castle_usa.png");
    Load(town_sprite[USA][1], "textures\\relief\\usa\\castle_usa_navedeno.png");
    Load(town_sprite[USA][2], "textures\\relief\\usa\\castle_usa_pr.png");

    Load(town_sprite[ENGLAND][0], "textures\\relief\\britain\\castle_britain.png");
    Load(town_sprite[ENGLAND][1], "textures\\relief\\britain\\castle_britain_navedeno.png");
    Load(town_sprite[ENGLAND][2], "textures\\relief\\britain\\castle_britain_pr.png");

    Load(town_sprite[RUSSIA][0], "textures\\relief\\rusia\\castle_rusia.png");
    Load(town_sprite[RUSSIA][1], "textures\\relief\\rusia\\castle_rusia_navedeno.png");
    Load(town_sprite[RUSSIA][2], "textures\\relief\\rusia\\castle_rusia_pr.png");

    Load(flag[FRANCE], "textures\\flag\\france.png");
    Load(flag[UKRAINE], "textures\\flag\\ukraine.png");
    Load(flag[GERMANY], "textures\\flag\\germany.png");
    Load(flag[USA], "textures\\flag\\usa.png");
    Load(flag[ENGLAND], "textures\\flag\\england.png");
    Load(flag[RUSSIA], "textures\\flag\\russia.png");
}

void LoadAll()
{
    GLuint tex;

    name[0].pb("Napoleon_Bonapart");
    Load(tex, "generals\\France\\Napoleon.png");
    general_sprite[name[0][0]] = tex;
    name[0].pb("Karl_the_Great");
    Load(tex, "generals\\France\\Karl the Great.png");
    general_sprite[name[0][1]] = tex;
    name[0].pb("Francisk_II");
    Load(tex, "generals\\France\\Francisk.png");
    general_sprite[name[0][2]] = tex;
    name[0].pb("Capet");
    Load(tex, "generals\\France\\Capet.png");
    general_sprite[name[0][3]] = tex;

    name[1].pb("Otto_fon_Bismark");
    Load(tex, "generals\\Germany\\Otto fon Bismark.png");
    general_sprite[name[1][0]] = tex;
    name[1].pb("Fridrich_Barbarossa");
    Load(tex, "generals\\Germany\\Barbarosa.png");
    general_sprite[name[1][1]] = tex;
    name[1].pb("Adolf_Hitler");
    Load(tex, "generals\\Germany\\Hitler.png");
    general_sprite[name[1][2]] = tex;
    name[1].pb("Nicholas");
    Load(tex, "generals\\Germany\\nikolas.png");
    general_sprite[name[1][3]] = tex;

    name[2].pb("Bohdan_Hmelnitskiy");
    Load(tex, "generals\\Ukraine\\Hmelnitskiy.png");
    general_sprite[name[2][0]] = tex;
    name[2].pb("Volodymyr_Velykiy");
    Load(tex, "generals\\Ukraine\\Volodymyr.png");
    general_sprite[name[2][1]] = tex;
    name[2].pb("Yaroslav_Mudriy");
    Load(tex, "generals\\Ukraine\\Yaroslav.png");
    general_sprite[name[2][2]] = tex;
    name[2].pb("Ivan_Mazepa");
    Load(tex, "generals\\Ukraine\\Mazepa.png");
    general_sprite[name[2][3]] = tex;

    name[3].pb("Iosif_Stalin");
    Load(tex, "generals\\Russia\\Stalin.png");
    general_sprite[name[3][0]] = tex;
    name[3].pb("Katerina_II");
    Load(tex, "generals\\Russia\\Katerina.png");
    general_sprite[name[3][1]] = tex;
    name[3].pb("Petr_I");
    Load(tex, "generals\\Russia\\Petr.png");
    general_sprite[name[3][2]] = tex;
    name[3].pb("Nickolas_II");
    Load(tex, "generals\\Russia\\nicholas.png");
    general_sprite[name[3][3]] = tex;

    name[4].pb("Avraam_Linkoln");
    Load(tex, "generals\\USA\\Linkoln.png");
    general_sprite[name[4][0]] = tex;
    name[4].pb("Franklin_Roosevelt");
    Load(tex, "generals\\USA\\Ruzveld.png");
    general_sprite[name[4][1]] = tex;
    name[4].pb("George_Washington");
    Load(tex, "generals\\USA\\Washington.png");
    general_sprite[name[4][2]] = tex;
    name[4].pb("Taylor");
    Load(tex, "generals\\USA\\taylore.png");
    general_sprite[name[4][3]] = tex;

    name[5].pb("Elizabeth_II");
    Load(tex, "generals\\England\\Elizabeth.png");
    general_sprite[name[5][0]] = tex;
    name[5].pb("Richard_Lionheart");
    Load(tex, "generals\\England\\Richard.png");
    general_sprite[name[5][1]] = tex;
    name[5].pb("Karl");
    Load(tex, "generals\\England\\karl.png");
    general_sprite[name[5][2]] = tex;
    name[5].pb("George_III");
    Load(tex, "generals\\England\\Georg_3.png");
    general_sprite[name[5][3]] = tex;

    Load(tex, "generals\\Russia\\Partizan.png");
    general_sprite["Partizan"] = tex;

    LoadCountries();

    Load(menu_background, "textures\\buttons\\menu_back.png");
    Load(fortex_active, "textures\\buttons\\set_fortress_button_active.png");
    Load(fortex_passive, "textures\\buttons\\set_fortress_button_passive.png");
    Load(get_info_button, "textures\\buttons\\get_info_button.png");
    Load(logo, "textures\\logo.png");
    Load(logo_team, "textures\\logo_team.png");

    all_menu_init();

}

void init_start_button()
{
    start_button.clear();
    start_button.pb(Load("textures\\buttons\\start_can_not.png"));
    start_button.pb(Load("textures\\buttons\\start.png"));
    start_button.pb(Load("textures\\buttons\\start_pr.png"));
    start_button.pb(Load("textures\\buttons\\start_navedeno.png"));
}

void init_settings()
{
    int dop;
    menu["small"]=Button(90.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\small.png"),Load("textures\\buttons\\small_pr.png"),Load("textures\\buttons\\small_navedeno.png"));
    menu["medium"]=Button(90.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\medium.png"),Load("textures\\buttons\\medium_pr.png"),Load("textures\\buttons\\medium_navedeno.png"));
    menu["big"]=Button(90.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\big.png"),Load("textures\\buttons\\big_pr.png"),Load("textures\\buttons\\big_navedeno.png"));
    menu["giant"]=Button(90.0*width/1366,325.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\giant.png"),Load("textures\\buttons\\giant_pr.png"),Load("textures\\buttons\\giant_navedeno.png"));

    menu["mainland"]=Button(390.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\mainland.png"),Load("textures\\buttons\\mainland_pr.png"),Load("textures\\buttons\\mainland_navedeno.png"));
    menu["continents"]=Button(390.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\continents.png"),Load("textures\\buttons\\continents_pr.png"),Load("textures\\buttons\\continents_navedeno.png"));
    menu["islands"]=Button(390.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\islands.png"),Load("textures\\buttons\\islands_pr.png"),Load("textures\\buttons\\islands_navedeno.png"));

    dop=Load("textures\\buttons\\mainland_can_not.png");
    menu["mainland!"]=Button(390.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\continents_can_not.png");
    menu["continents!"]=Button(390.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\islands_can_not.png");
    menu["islands!"]=Button(390.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);

    menu["mountainous"]=Button(690.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\mountainous.png"),Load("textures\\buttons\\mountainous_pr.png"),Load("textures\\buttons\\mountainous_navedeno.png"));
    menu["piedmont"]=Button(690.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\piedmont.png"),Load("textures\\buttons\\piedmont_pr.png"),Load("textures\\buttons\\piedmont_navedeno.png"));
    menu["plain"]=Button(690.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\plain.png"),Load("textures\\buttons\\plain_pr.png"),Load("textures\\buttons\\plain_navedeno.png"));

    dop=Load("textures\\buttons\\mountainous_can_not.png");
    menu["mountainous!"]=Button(690.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\piedmont_can_not.png");
    menu["piedmont!"]=Button(690.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\plain_can_not.png");
    menu["plain!"]=Button(690.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);

    menu["first"]=Button(990.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\easy.png"),Load("textures\\buttons\\easy_pr.png"),Load("textures\\buttons\\easy_navedeno.png"));
    menu["second"]=menu["medium"];
    menu["second"].st_x=990.0*width/1366;
    menu["third"]=Button(990.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,Load("textures\\buttons\\hard.png"),Load("textures\\buttons\\hard_pr.png"),Load("textures\\buttons\\hard_navedeno.png"));

    dop=Load("textures\\buttons\\easy_can_not.png");
    menu["first!"]=Button(990.0*width/1366,100.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\medium_can_not.png");
    menu["second!"]=Button(990.0*width/1366,175.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);
    dop=Load("textures\\buttons\\hard_can_not.png");
    menu["third!"]=Button(990.0*width/1366,250.0*height/768,220.0*width/1366,60.0*height/768,dop,dop,dop);

    menu["save"]=Button(875.0*width/1366,685.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\save.png"),Load("textures\\buttons\\save_pr.png"),Load("textures\\buttons\\save_navedeno.png"));
    menu["cancel1"]=menu["cancel"];

    bad_line=Load("textures\\buttons\\line.png");

    /// TODO :: 3 textures for romb
    dop=Load("textures\\buttons\\romb.png");
    menu["point"]=Button(435.0*width/1366,605.0*height/768,30.0*width/1366,40.0*height/768,dop,dop,dop);
}

Button clear_button;

void init_listik()
{
    listik.clear();
    for (auto i:remember1)
        listik.pb(mp(clear_button,i));
}

void init_remember1()
{
    remember1.clear();
    ifstream dop_1("load_data.txt");
    string s;
    while (dop_1>>s)
        if (!s.empty())
            remember1.pb(s);
        else
            break;
    dop_1.close();
    init_listik();
}

void init_load()
{
    menu["arrow_down"]=Button(675.0*width/1366,400.0*height/768,75.0*width/1366,75.0*height/768,Load("textures\\buttons\\strilka_vnuz.png"),Load("textures\\buttons\\strilka_vnyz_pr.png"),Load("textures\\buttons\\strilka_vnyz_navedeno.png"));;
    menu["arrow_up"]=Button(675.0*width/1366,250.0*height/768,75.0*width/1366,75.0*height/768,Load("textures\\buttons\\strilka_vverx.png"),Load("textures\\buttons\\strilka_vverx_pr.png"),Load("textures\\buttons\\strilka_vverx_navedeno.png"));;

    init_remember1();

    menu["save_load"]=menu["load"];
    menu["save_load"].st_x=475.0*width/1366;
    menu["save_load"].st_y=650.0*height/768;
    menu["save_load"].w=225.0*width/1366;
    menu["save_load"].h=65.0*height/768;

    menu["save_load!"]=menu["save_load"];
    menu["save_load!"].data[0]=Load("textures\\buttons\\load_can_not.png");
    menu["save_load!"].data[1]=menu["save_load!"].data[0];
    menu["save_load!"].data[2]=menu["save_load!"].data[0];

    menu["cancel2"]=menu["cancel"];
    menu["cancel2"].st_x=1025.0*width/1366;
    menu["cancel2"].st_y=650.0*height/768;
    menu["cancel2"].w=225.0*width/1366;
    menu["cancel2"].h=65.0*height/768;

    menu["delete"]=Button(750.0*width/1366,650.0*height/768,225.0*width/1366,65.0*height/768,Load("textures\\buttons\\delete.png"),Load("textures\\buttons\\delete_pr.png"),Load("textures\\buttons\\delete_navedeno.png"));
    texture dop_qwe_123_ber=Load("textures\\buttons\\delete_can_not.png");
    menu["delete!"]=Button(750.0*width/1366,650.0*height/768,225.0*width/1366,65.0*height/768,dop_qwe_123_ber,dop_qwe_123_ber,dop_qwe_123_ber);
}

void init_surrender_menu()
{
    int dop_;
    dop_=Load("textures\\pause.png");
    menu["pause22"]=Button(550.0*width/1366,-10.0*height/768,100.0*width/1366,105.0*height/768,dop_,dop_,dop_);
    menu["surrender"]=Button(700.0*width/1366,0.0*height/768,100.0*width/1366,80.0*height/768,Load("textures\\flag\\white_flag.png"),Load("textures\\flag\\white_flag_pr.png"),Load("textures\\flag\\white_flag_navedeno.png"));

    menu["yes"]=Button(250.0*width/1366,400.0*height/768,350.0*width/1366,100.0*height/768,Load("textures\\buttons\\yes.png"),Load("textures\\buttons\\yes_pr.png"),Load("textures\\buttons\\yes_navedeno.png"));
    menu["no"]=Button(750.0*width/1366,400.0*height/768,350.0*width/1366,100.0*height/768,Load("textures\\buttons\\no.png"),Load("textures\\buttons\\no_pr.png"),Load("textures\\buttons\\no_navedeno.png"));
}

void init_sukotay()
{
    int eps=30.0*height/768;
    menu["back_to_game(pause)"]=Button(500.0*width/1366,100.0*height/768-eps,400.0*width/1366,100.0*height/768,Load("textures\\sukotay\\back_to_game.png"),Load("textures\\sukotay\\back_to_game_pr.png"),Load("textures\\sukotay\\back_to_game_navedeno.png"));;;
    menu["save_game(pause)"]=Button(500.0*width/1366,230.0*height/768-eps,400.0*width/1366,100.0*height/768,Load("textures\\sukotay\\save.png"),Load("textures\\sukotay\\save_pr.png"),Load("textures\\sukotay\\save_navedeno.png"));;;
    menu["load(pause)"]=Button(500.0*width/1366,360.0*height/768-eps,400.0*width/1366,100.0*height/768,Load("textures\\sukotay\\load.png"),Load("textures\\sukotay\\load_pr.png"),Load("textures\\sukotay\\load_navedeno.png"));;;
    menu["back_to_main_menu(pause)"]=Button(500.0*width/1366,490.0*height/768-eps,400.0*width/1366,100.0*height/768,Load("textures\\sukotay\\back_to_main_menu.png"),Load("textures\\sukotay\\back_to_main_menu_pr.png"),Load("textures\\sukotay\\back_to_main_menu_navedeno.png"));;;
    menu["exit(pause)"]=Button(500.0*width/1366,620.0*height/768-eps,400.0*width/1366,100.0*height/768,Load("textures\\sukotay\\exit_from_game.png"),Load("textures\\sukotay\\exit_from_game_pr.png"),Load("textures\\sukotay\\exit_from_game_navedeno.png"));;;
}

void init_standart_maps()
{
    int eps=30.0*height/768;
    menu["Standart_maps"]=Button(990.0*width/1366,390.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\Standart_maps.png"),Load("textures\\buttons\\Standart_maps_pr.png"),Load("textures\\buttons\\Standart_maps_navedeno.png"));
    menu["BigBattle"]=Button(400.0*width/1366,100.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\BigBattle.png"),Load("textures\\buttons\\BigBattle_pr.png"),Load("textures\\buttons\\BigBattle_navedeno.png"));
    menu["Caribians"]=Button(400.0*width/1366,400.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\Caribians.png"),Load("textures\\buttons\\Caribians_pr.png"),Load("textures\\buttons\\Caribians_navedeno.png"));
    menu["Gorge"]=Button(400.0*width/1366,300.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\Gorge.png"),Load("textures\\buttons\\Gorge_pr.png"),Load("textures\\buttons\\Gorge_navedeno.png"));
    menu["Snake"]=Button(400.0*width/1366,200.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\Snake.png"),Load("textures\\buttons\\Snake_pr.png"),Load("textures\\buttons\\Snake_navedeno.png"));
    menu["Earth"]=Button(400.0*width/1366,500.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\Earth.png"),Load("textures\\buttons\\Earth_pr.png"),Load("textures\\buttons\\Earth_navedeno.png"));

    int dop_;

    menu["Earth!"]=menu["Earth"];
    dop_=Load("textures\\buttons\\Earth_can_not.png");
    menu["Earth!"].data[0]=dop_;
    menu["Earth!"].data[1]=dop_;
    menu["Earth!"].data[2]=dop_;

    menu["Caribians!"]=menu["Caribians"];
    dop_=Load("textures\\buttons\\Caribians_can_not.png");
    menu["Caribians!"].data[0]=dop_;
    menu["Caribians!"].data[1]=dop_;
    menu["Caribians!"].data[2]=dop_;

    menu["cancel3"]=menu["cancel"];
    menu["start3"]=menu["start"];
    menu["start3!"]=menu["start3"];
    menu["start3!"].data[0]=start_button[0];
    menu["start3!"].data[1]=start_button[0];
    menu["start3!"].data[2]=start_button[0];
}

void all_menu_init()
{
    clear_button=Button(235.0*width/1366,0,400.0*width/1366,75.0*height/768,Load("textures\\buttons\\clear_button.png"),Load("textures\\buttons\\clear_button_pr.png"),Load("textures\\buttons\\clear_button_navedeno.png"));;

    int eps=50.0*height/768;
    menu["play"]=Button(900.0*width/1366,100.0*height/768-eps,350.0*width/1366,100.0*height/768,Load("textures\\buttons\\new_game.png"),Load("textures\\buttons\\new_game_pr.png"),Load("textures\\buttons\\new_game_navedeno.png"));
    menu["load"]=Button(900.0*width/1366,300.0*height/768-eps,350.0*width/1366,100.0*height/768,Load("textures\\buttons\\load.png"),Load("textures\\buttons\\load_pr.png"),Load("textures\\buttons\\load_navedeno.png"));
    menu["quit"]=Button(900.0*width/1366,500.0*height/768-eps,350.0*width/1366,100.0*height/768,Load("textures\\buttons\\quit.png"),Load("textures\\buttons\\quit_pr.png"),Load("textures\\buttons\\quit_navedeno.png"));

    menu["usa1"]=Button(100.0*width/1366,100.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\usa.png"),Load("textures\\buttons\\usa_pr.png"),Load("textures\\buttons\\usa_navedeno.png"));
    menu["usa2"]=Button(1050.0*width/1366,100.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\usa.png"),Load("textures\\buttons\\usa_pr.png"),Load("textures\\buttons\\usa_navedeno.png"));

    menu["france1"]=Button(100.0*width/1366,200.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\france.png"),Load("textures\\buttons\\france_pr.png"),Load("textures\\buttons\\france_navedeno.png"));
    menu["france2"]=Button(1050.0*width/1366,200.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\france.png"),Load("textures\\buttons\\france_pr.png"),Load("textures\\buttons\\france_navedeno.png"));

    menu["england1"]=Button(100.0*width/1366,300.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\england.png"),Load("textures\\buttons\\england_pr.png"),Load("textures\\buttons\\england_navedeno.png"));
    menu["england2"]=Button(1050.0*width/1366,300.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\england.png"),Load("textures\\buttons\\england_pr.png"),Load("textures\\buttons\\england_navedeno.png"));

    menu["ukraine1"]=Button(100.0*width/1366,400.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\ukraine.png"),Load("textures\\buttons\\ukraine_pr.png"),Load("textures\\buttons\\ukrain_navedeno.png"));
    menu["ukraine2"]=Button(1050.0*width/1366,400.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\ukraine.png"),Load("textures\\buttons\\ukraine_pr.png"),Load("textures\\buttons\\ukrain_navedeno.png"));

    menu["germany1"]=Button(100.0*width/1366,500.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\germany.png"),Load("textures\\buttons\\germany_pr.png"),Load("textures\\buttons\\germany_navedeno.png"));
    menu["germany2"]=Button(1050.0*width/1366,500.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\germany.png"),Load("textures\\buttons\\germany_pr.png"),Load("textures\\buttons\\germany_navedeno.png"));

    menu["russia1"]=Button(100.0*width/1366,600.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\russia.png"),Load("textures\\buttons\\russia_pr.png"),Load("textures\\buttons\\russia_navedeno.png"));
    menu["russia2"]=Button(1050.0*width/1366,600.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\russia.png"),Load("textures\\buttons\\russia_pr.png"),Load("textures\\buttons\\russia_navedeno.png"));

    menu["player_vs_player"]=Button(575.0*width/1366,100.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\player_vs_player.png"),Load("textures\\buttons\\player_vs_player_pr.png"),Load("textures\\buttons\\player_vs_player_navedeno.png"));
    menu["player_vs_pc"]=Button(575.0*width/1366,200.0*height/768-eps,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\player_vs_pc.png"),Load("textures\\buttons\\player_vs_pc_pr.png"),Load("textures\\buttons\\player_vs_pc_navedeno.png"));

    menu["but1"]=Button(525.0*width/1366,400.0*height/768-eps,325.0*width/1366,60.0*height/768,Load("textures\\buttons\\i'm_to_young_too_die.png"),Load("textures\\buttons\\i'm_to_young_too_die_pr.png"),Load("textures\\buttons\\i'm_to_young_too_die_navedeno.png"));
    menu["but2"]=Button(525.0*width/1366,500.0*height/768-eps,325.0*width/1366,60.0*height/768,Load("textures\\buttons\\hey,_not_too_rough!.png"),Load("textures\\buttons\\hey,_not_too_rough!_pr.png"),Load("textures\\buttons\\hey,_not_too_rough!_navedeno.png"));
    menu["but3"]=Button(525.0*width/1366,600.0*height/768-eps,325.0*width/1366,60.0*height/768,Load("textures\\buttons\\hurt_me_plenty.png"),Load("textures\\buttons\\hurt_me_plenty_pr.png"),Load("textures\\buttons\\hurt_me_plenty_navedeno.png"));

    start_back.clear();
    start_back.pb(Load("textures\\start1.jpg"));

    init_start_button();

    menu["start"]=Button(875.0*width/1366,685.0*height/768,225.0*width/1366,60.0*height/768,start_button[1],start_button[2],start_button[3]);
    menu["cancel"]=Button(1120.0*width/1366,685.0*height/768,225.0*width/1366,60.0*height/768,Load("textures\\buttons\\cancel.png"),Load("textures\\buttons\\cancel_pr.png"),Load("textures\\buttons\\cancel_navedeno.png"));

    menu["settings"]=Button(275.0*width/1366,675.0*height/768,300.0*width/1366,75.0*height/768,Load("textures\\buttons\\additional_settings.png"),Load("textures\\buttons\\additional_settings_pr.png"),Load("textures\\buttons\\additional_settings_navedeno.png"));

    ramka=Load("textures\\ramka.png");
    cursor=Load("textures\\cursor.png");
    no_save=Load("textures\\no_saved_files.psd");
    ramka_for_score=Load("textures\\ramka_for_score.png");

    init_settings();
    init_load();

    init_sukotay();

    menu["small"].pressed=true;
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
    menu["third"].pressed=false;

    village_texture[0]=Load("textures\\relief\\ukrain\\village_ukraine.png");
    village_texture[1]=Load("textures\\relief\\ukrain\\village_ukraine_navedeno.png.png");
    village_texture[2]=Load("textures\\relief\\ukrain\\village_ukraine_pr.png.png.png");

    texture dop1=Load("textures\\checkbox.png");
    texture dop2=Load("textures\\checkbox_pr.png");

    menu["game_with_features"]=Button(1000.0*width/1366,500.0*height/768,50.0*width/1366,50.0*height/768,dop1,dop2,dop1);
    menu["play_dermo"]=Button(875.0*width/1366,167.0*height/768,350.0*width/1366,80.0*height/768,Load("textures\\buttons\\play_a_turn_from_file.png"),Load("textures\\buttons\\play_a_turn_from_file_pr.png"),Load("textures\\buttons\\play_a_turn_from_file_navedeno.png"));

    fone=Load("textures\\fon2.png");

    init_standart_maps();

    vec1={{235.0*width/1366,175.0*height/768},{235.0*width/1366,275.0*height/768},{235.0*width/1366,375.0*height/768},{235.0*width/1366,475.0*height/768}};
}
