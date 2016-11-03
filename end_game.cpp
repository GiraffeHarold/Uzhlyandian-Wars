#include "end_game.h"
#include "global_vars.h"
#include "Button.h"
#include "textures.h"
#include "draw_menu.h"
#include "loading_game.h"
#include "hard_intellect.h"
#include "debug.h"
#include "controller.h"

int not_inited_end = 1, pressed = 0;
bool surrendered[2];
Button back_to_main;

void end_game()
{
    //for (int i=0; i<2e9; ) i++;
    int cnt0 = 0, cnt1 = 0;
    for (auto x : Hexes)
        for (auto y : x)
            if (y.color == chosen_country[0]) cnt0++;
            else if (y.color == chosen_country[1]) cnt1++;
    cnt0 *= 1 - surrendered[0];
    cnt1 *= 1 - surrendered[1];
    score = mp(cnt0, cnt1);
    game_ending_menu = true;
    //exit(0);
}

void draw_winner_flag()
{
    if (score.fi > score.se)
    {
        GLuint tex = flag[chosen_country[0]];
        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 0.7);

        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, tex);
            glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex2f(0, 0);
            glTexCoord2f(1, 0); glVertex2f(width, 0);
            glTexCoord2f(1, 1); glVertex2f(width, height);
            glTexCoord2f(0, 1); glVertex2f(0, height);

            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else if (score.fi < score.se)
    {
        GLuint tex = flag[chosen_country[1]];
        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 0.7);

        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, tex);
            glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex2f(0, 0);
            glTexCoord2f(1, 0); glVertex2f(width, 0);
            glTexCoord2f(1, 1); glVertex2f(width, height);
            glTexCoord2f(0, 1); glVertex2f(0, height);

            glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else
    {
        GLuint tex1 = flag[chosen_country[0]], tex2 = flag[chosen_country[1]];
        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 0.7);

        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, tex1);
            glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex2f(0, 0);
            glTexCoord2f(1, 0); glVertex2f(width/2 + 50.0*width/1366, 0);
            glTexCoord2f(1, 1); glVertex2f(width/2 - 50.0*width/1366, height);
            glTexCoord2f(0, 1); glVertex2f(0, height);

            glEnd();
        glPopMatrix();


        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, tex2);
            glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex2f(width/2 + 50.0*width/1366, 0);
            glTexCoord2f(1, 0); glVertex2f(width, 0);
            glTexCoord2f(1, 1); glVertex2f(width, height);
            glTexCoord2f(0, 1); glVertex2f(width/2 - 50.0*width/1366, height);

            glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
    }
}

void draw_menu_background()
{
    GLuint tex = menu_background;
    glEnable(GL_TEXTURE_2D);
    glColor4f(1, 1, 1, 0.7);

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);

        glTexCoord2f(0, 0); glVertex2f(width/3.0, 2.0*height/5);
        glTexCoord2f(1, 0); glVertex2f(2.0*width/3.0, 2.0*height/5);
        glTexCoord2f(1, 1); glVertex2f(2.0*width/3.0, 3.0*height/5);
        glTexCoord2f(0, 1); glVertex2f(width/3.0, 3.0*height/5);

        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

string get_name(int x)
{
    if (x == FRANCE) return "France ";
    if (x == UKRAINE) return "Ukraine ";
    if (x == GERMANY) return "Germany ";
    if (x == USA) return "USA ";
    if (x == ENGLAND) return "England ";
    if (x == RUSSIA) return "Russia ";
}

string string_score()
{
    stringstream ss;
    ss << score.fi << "-" << score.se;
    return ss.str();
}

void out_text(string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    for (auto i:s)
        glutBitmapCharacter(font,i);
}

void out_text(int xx,int yy,string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    glColor3f(1,1,1);
    glRasterPos2f(xx,yy);
    //glTranslatef(2, 2, 2);
    out_text(s);
}

void draw_text_winning()
{
    int k;
    if (score.fi > score.se)
    {
        if (chosen_country[0]==USA) k=-10.0*width/1366;
        if (chosen_country[0]==GERMANY) k=7.0*width/1366;
        if (chosen_country[0]==FRANCE) k=-1.0*width/1366;
        if (chosen_country[0]==RUSSIA) k=-1.0*width/1366;
        if (chosen_country[0]==UKRAINE) k=4.0*width/1366;
        if (chosen_country[0]==ENGLAND) k=5.0*width/1366;
    }
    if (score.fi < score.se)
    {
        if (chosen_country[1]==USA) k=-10.0*width/1366;
        if (chosen_country[1]==GERMANY) k=7.0*width/1366;
        if (chosen_country[1]==FRANCE) k=-1.0*width/1366;
        if (chosen_country[1]==RUSSIA) k=-1.0*width/1366;
        if (chosen_country[1]==UKRAINE) k=4.0*width/1366;
        if (chosen_country[1]==ENGLAND) k=5.0*width/1366;
    }
    if (score.fi == score.se)
        out_text(0.425*width, 0.45*height, "Game ended in draw");
    else if (score.fi > score.se)
        out_text(0.45*width-k, 0.45*height, get_name(chosen_country[0]) + " won!");
    else
        out_text(0.45*width-k, 0.45*height, get_name(chosen_country[1]) + " won!");
    out_text(0.49*width-string_score().length()*3, 0.488*height, string_score());
}

void init_end()
{
    back_to_main = *(new Button(0.42*width, 0.50*height, 0.16*width, 0.07*height,
                                Load("textures\\buttons\\back_to_main_menu.png"),
                                Load("textures\\buttons\\back_to_main_menu_pr.png"),
                                Load("textures\\buttons\\back_to_main_menu_navedeno.png")));
    not_inited_end = 0;
}

void draw_button()
{
    back_to_main.draw(1);
}

void mouse_end(int state)
{
    if (state==GLUT_UP)
    {
        if (back_to_main.pressed&&!back_to_main.on_click())
            back_to_main.pressed=false;
        if (back_to_main.pressed)
        {
            back_to_main.pressed=false;
//            cout << "    1\n";
            game_ending_menu = false;
//            cout << "    2\n";
            in_main_menu = true;
//            cout << "    3\n";
            Hexes.clear();
//            cout << "    4\n";
            player_general[0].clear();
//            cout << "    5\n";
            player_general[1].clear();
//            cout << "    6\n";
            cur_turn = 0;
//            cout << "    7\n";
            Turns = 0;
//            cout << "    8\n";
            R = 100;
//            cout << "    9\n";
            for (int i=0; i<10; i++)
                last[i] = "";

//            cout << "    10\n";
            general_chosen = NULL;
//            cout << "    11\n";
            just_moved = 0;
//            cout << "    12\n";
            general_moving_left = 0;
//            cout << "    13\n";
            type_of_menu = "Start_menu";
//            cout << "    14\n";
            mouse_gen_func = 0;
//            cout << "    15\n";
            mouse_not_gen_func = 0;
//            cout << "    16\n";
            surrendered[0] = 0;
//            cout << "    17\n";
            surrendered[1] = 0;
//            cout << "    18\n";
            ourSquads.clear();
//            cout << "    19\n";
            for (int i=0; i<N; i++)
                for (int j=0; j<M; j++)
                    chosen_to_build[i][j] = 0;
//            cout << "    20\n";
            set_fort_now = false;
            Display();
            glutTimerFunc(1, timer, 1);
        }
    }
    if (state==GLUT_DOWN)
    {
        back_to_main.click();
    }
}

void draw_end_game()
{
    if (not_inited_end)
        init_end();
    draw_winner_flag();
    draw_menu_background();
    draw_text_winning();
    draw_button();
}

void surrender()
{
    surrendered[cur_turn%2] = 1;
    end_game();
}
