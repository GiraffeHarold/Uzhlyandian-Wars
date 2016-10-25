#include "draw_menu.h"
#include "menu_mouse.h"
#include "drawing.h"

vector<pair<int,int>> vec1;
vector<pair<Button,string>> listik;
texture bad_line;

void outtext(string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    for (auto i:s)
        glutBitmapCharacter(font,i);
}

void outtext(int xx,int yy,string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    glColor3f(1,0.5,0);
    glRasterPos2f(xx,yy);
    outtext(s);
}

void outtext_black(int xx,int yy,string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    glColor3f(0.9,0.9,0.9);
    glRasterPos2f(xx,yy);
    outtext(s);
}

void draw_background()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,start_back[rand()%start_back.size()]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(0,0);
                glTexCoord2f(1,0); glVertex2f(width,0);
                glTexCoord2f(1,1); glVertex2f(width,height);
                glTexCoord2f(0,1); glVertex2f(0,height);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void black_fone(ld f)
{
    glPushMatrix();
        glBegin(GL_POLYGON);
            glColor4f(0,0,0,f);
            glVertex2f(0,0);
            glVertex2f(10000,0);
            glVertex2f(10000,10000);
            glVertex2f(0,10000);
        glEnd();
    glPopMatrix();
}

void draw_cursor()
{
    glutSetCursor(101);
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            POINT mouse;
            GetCursorPos(&mouse);
            glBindTexture(GL_TEXTURE_2D,cursor);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(mouse.x,mouse.y);
                glTexCoord2f(1,0); glVertex2f(mouse.x+30,mouse.y);
                glTexCoord2f(1,1); glVertex2f(mouse.x+30,mouse.y+30);
                glTexCoord2f(0,1); glVertex2f(mouse.x,mouse.y+30);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_start_menu()
{
    menu["play"].draw(type_of_menu=="Start_menu");
    menu["load"].draw(type_of_menu=="Start_menu");
    menu["quit"].draw(type_of_menu=="Start_menu");
}

void draw_start_button()
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

    ///psove(sobache) dermo
    ///sukatay blat
    is_check4|=menu["but1"].pressed;
    is_check4|=menu["but2"].pressed;
    is_check4|=menu["but3"].pressed;

    if (!is_check1||!is_check2||!is_check3||!is_check4)
    {
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,start_button[0]);
                glBegin(GL_POLYGON);
                    int st_x=875.0*width/1366;
                    int st_y=685.0*height/768;
                    int w=225.0*width/1366;
                    int h=60.0*height/768;
                    glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                    glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                    glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                    glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
                glEnd();
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        menu["start"].pressed=false;
    }
    else
    {
        menu["start"].draw(type_of_menu=="Check_country");
    }
}

void draw_ramka()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            int st_x=180.0*width/1366;
            int st_y=80.0*height/768;
            int w=1000.0*width/1366;
            int h=600.0*height/768;
            glBindTexture(GL_TEXTURE_2D,ramka);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_cant_load()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            int st_x=180.0*width/1366;
            int st_y=80.0*height/768;
            int w=1000.0*width/1366;
            int h=600.0*height/768;
            glBindTexture(GL_TEXTURE_2D,no_save);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_empty_load_menu()
{
    menu["cancel2"].draw(true);
    draw_cant_load();
}

void draw_load_menu()
{
    if (in_main_menu)
        menu["play_dermo"].draw(type_of_menu=="Load_menu");

    if (listik.size()==0)
        return void(draw_empty_load_menu());

    if (listik.size()>4)
    {
        menu["arrow_down"].draw(pointer+4!=listik.size());
        menu["arrow_up"].draw(pointer!=0);
    }

    for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
        listik[i].first.st_y=vec1[i-pointer].second;

    for (int i=pointer;i<min(pointer+4,int(listik.size()));i++)
        listik[i].first.draw(true),
        outtext_black(listik[i].first.st_x+68.0*listik[i].first.w/400,listik[i].first.st_y+45.0*listik[i].first.h/75,listik[i].second);

    bool ok=false;

    for (auto i:listik)
        ok|=(i.first.pressed);

    if (ok)
        menu["save_load"].draw(type_of_menu=="Load_menu");
    else
        menu["save_load!"].draw(type_of_menu=="Load_menu");

    if (ok)
        menu["delete"].draw(type_of_menu=="Load_menu");
    else
        menu["delete!"].draw(type_of_menu=="Load_menu");

    menu["cancel2"].draw(type_of_menu=="Load_menu");
}

void draw_check_country_menu()
{
    menu["usa1"].draw(type_of_menu=="Check_country");
    menu["usa2"].draw(type_of_menu=="Check_country");

    menu["france1"].draw(type_of_menu=="Check_country");
    menu["france2"].draw(type_of_menu=="Check_country");

    menu["england1"].draw(type_of_menu=="Check_country");
    menu["england2"].draw(type_of_menu=="Check_country");

    menu["ukraine1"].draw(type_of_menu=="Check_country");
    menu["ukraine2"].draw(type_of_menu=="Check_country");

    menu["germany1"].draw(type_of_menu=="Check_country");
    menu["germany2"].draw(type_of_menu=="Check_country");

    menu["russia1"].draw(type_of_menu=="Check_country");
    menu["russia2"].draw(type_of_menu=="Check_country");

    menu["player_vs_player"].draw(type_of_menu=="Check_country");
    menu["player_vs_pc"].draw(type_of_menu=="Check_country");

    menu["but1"].draw(type_of_menu=="Check_country");
    menu["but2"].draw(type_of_menu=="Check_country");
    menu["but3"].draw(type_of_menu=="Check_country");

    draw_start_button();
    menu["cancel"].draw(type_of_menu=="Check_country");

    menu["settings"].draw(type_of_menu=="Check_country");
}

void draw_bad_line()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            int st_x=200.0*width/1366;
            int st_y=600.0*height/768;
            int w=500.0*width/1366;
            int h=50.0*height/768;
            glBindTexture(GL_TEXTURE_2D,bad_line);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

string to_string(int a)
{
    stringstream stt;
    stt<<a;
    string res;
    stt>>res;
    return res;
}

int get_current_check_turns()
{
    ld how_much=(menu["point"].st_x+menu["point"].w/2.0-225.0*width/1366)/(450.0*width/1366);
    int maximum;
    if (menu["small"].pressed) maximum=8;
    if (menu["medium"].pressed) maximum=25;
    if (menu["big"].pressed) maximum=120;
    if (menu["giant"].pressed) maximum=300;
    int cnt=round(how_much*maximum);
    cnt=max(cnt,1);
    return cnt;
}

void draw_current_check_turns()
{
    int cnt=get_current_check_turns();
    outtext(720.0*width/1366,632.0*height/768,to_string(cnt));
}

void draw_minmax_check_turns()
{
    int maximum;
    if (menu["small"].pressed) maximum=8;
    if (menu["medium"].pressed) maximum=25;
    if (menu["big"].pressed) maximum=120;
    if (menu["giant"].pressed) maximum=300;
    outtext(200.0*width/1366,680.0*height/768,to_string(1));
    outtext(680.0*width/1366,680.0*height/768,to_string(maximum));
}

void scrol_romb()
{
    if (!menu["point"].pressed) return;
    POINT mouse;
    GetCursorPos(&mouse);
    menu["point"].st_x=min(690.0*width/1366-menu["point"].w,max(210.0*width/1366,mouse.x-menu["point"].w/2.0));
}

void draw_settings()
{
    outtext(1065.0*width/1366,533.0*height/768,"Additional abilities");
    menu["game_with_features"].draw(type_of_menu=="Settings");

    outtext(155.0*width/1366,70.0*height/768,"Map size");

    menu["small"].draw(type_of_menu=="Settings");
    menu["medium"].draw(type_of_menu=="Settings");
    menu["big"].draw(type_of_menu=="Settings");
    menu["giant"].draw(type_of_menu=="Settings");

    outtext(455.0*width/1366,70.0*height/768,"Map type");

    if (!menu["but1"].pressed)
    {
        menu["mainland"].draw(type_of_menu=="Settings");
        menu["continents"].draw(type_of_menu=="Settings");
    }
    else
    {
        menu["mainland!"].draw(type_of_menu=="Settings");
        menu["continents!"].draw(type_of_menu=="Settings");
    }

    if (!menu["but1"].pressed&&!menu["but2"].pressed)
        menu["islands"].draw(type_of_menu=="Settings");
    else
        menu["islands!"].draw(type_of_menu=="Settings");

    outtext(770.0*width/1366,70.0*height/768,"Relief");

    if (!menu["but1"].pressed)
    {
        menu["mountainous"].draw(type_of_menu=="Settings");
        menu["piedmont"].draw(type_of_menu=="Settings");
        menu["plain"].draw(type_of_menu=="Settings");
    }
    else
    {
        menu["mountainous!"].draw(type_of_menu=="Settings");
        menu["piedmont!"].draw(type_of_menu=="Settings");
        menu["plain!"].draw(type_of_menu=="Settings");
    }

    outtext(1033.0*width/1366,70.0*height/768,"Intellect level");

    if (!menu["player_vs_player"].pressed)
    {
        menu["first"].draw(type_of_menu=="Settings");
        menu["second"].draw(type_of_menu=="Settings");
        menu["third"].draw(type_of_menu=="Settings");
    }
    else
    {
        menu["first!"].draw(type_of_menu=="Settings");
        menu["second!"].draw(type_of_menu=="Settings");
        menu["third!"].draw(type_of_menu=="Settings");
    }

    menu["save"].draw(type_of_menu=="Settings");
    menu["cancel1"].draw(type_of_menu=="Settings");

    scrol_romb();

    outtext(423.0*width/1366,570.0*height/768,"Turns");
    draw_bad_line();
    menu["point"].draw(type_of_menu=="Settings");
    draw_current_check_turns();
    draw_minmax_check_turns();

    menu["Standart_maps"].draw(type_of_menu=="Settings");
}

void draw_standart_maps()
{
    if (type_of_menu=="Standart_maps")
    {
        if (menu["but3"].pressed&&menu["game_with_features"].pressed)
            menu["Earth"].draw(true),
            menu["Caribians"].draw(true);
        else
            menu["Earth!"].draw(true),
            menu["Caribians!"].draw(true);
    }
    else
    {
        menu["Earth"].draw(false);
        menu["Caribians"].draw(false);
    }
    menu["BigBattle"].draw(type_of_menu=="Standart_maps");
    menu["Gorge"].draw(type_of_menu=="Standart_maps");
    menu["Snake"].draw(type_of_menu=="Standart_maps");

    bool ok=false;
    ok|=menu["Earth"].pressed;
    ok|=menu["BigBattle"].pressed;
    ok|=menu["Caribians"].pressed;
    ok|=menu["Gorge"].pressed;
    ok|=menu["Snake"].pressed;

    if (ok&&I_check_all())
        menu["start3"].draw(type_of_menu=="Standart_maps");
    else
        menu["start3!"].draw(type_of_menu=="Standart_maps");
    menu["cancel3"].draw(type_of_menu=="Standart_maps");
}

void drawStrokeText111(int xx,int yy,string s)
{
    for (int i=0;i<5;i++)
    {
        glPushMatrix();
        glTranslatef(xx+i,yy+30.0*height/768,0);
        glScalef(0.45f,-0.45f,0);
        glColor3f(1,0.5,0);
        for (auto i:s)
            glutStrokeCharacter(GLUT_STROKE_ROMAN,i);
        glPopMatrix();
    }
}

void draw_surrender_menu()
{
    menu["yes"].draw(surrender_menu);
    menu["no"].draw(surrender_menu);
    drawStrokeText111(212.0*width/1366,270.0*height/768,"Do you really want to surrender?");
}
