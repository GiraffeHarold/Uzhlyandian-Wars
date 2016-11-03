#include "drawing.h"
#include "draw_menu.h"
#include "end_game.h"
#include "pause_menu.h"
#include "loading_game.h"

ld ml = 0, mu = 0, mr = 1.25 * R + 1.5 * (R - 2.5) * (N-1) + 1.5*R , md = R_ + R + (2*(M-1)) * R_ + R;
int water[100][100];

vector <pair <General*, pair<ld, ld> > > stck;

void drawHex(GLuint tex, ld cx, ld cy, int country)
{

    //cerr << cy << " " << cy + curu << "\n";
    if (tex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);

        glPushMatrix();
            glColor4f(1, 1, 1, 1);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(cx - R, cy - R*cos(PI/6));
                glTexCoord2f(1, 0); glVertex2f(cx + R, cy - R*cos(PI/6));
                glTexCoord2f(1, 1); glVertex2f(cx + R, cy + R*cos(PI/6));
                glTexCoord2f(0, 1); glVertex2f(cx - R, cy + R*cos(PI/6));
            glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
    }
}

void draw_big_logotype()
{
    glLoadIdentity();
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glOrtho(0.0,width,height,0.0,0.f,-1.f);
    //black_fone(1);
    glEnable(GL_TEXTURE_2D);
    if (loading_now < 150) glBindTexture(GL_TEXTURE_2D, logo);
        else glBindTexture(GL_TEXTURE_2D, logo_team);
    glPushMatrix();
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(width/2 - 250.0*width/1366, height/2 - 250.0*height/768);
            glTexCoord2f(1, 0); glVertex2f(width/2 + 250.0*width/1366, height/2 - 250.0*height/768);
            glTexCoord2f(1, 1); glVertex2f(width/2 + 250.0*width/1366, height/2 + 250.0*height/768);
            glTexCoord2f(0, 1); glVertex2f(width/2 - 250.0*width/1366, height/2 + 250.0*height/768);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    if (cursor) draw_cursor();
    glutSwapBuffers();
}

void General :: draw(ld cx, ld cy)
{
    //if (this->is_killed)
      //  cout<<"bleat "<<this->killed<<" !\n";
    if (cnt_killed<0&&is_killed)
    {
        is_killed=false;
        Hexes[x][y].general=NULL;
        return;
    }
    if (is_killed) cnt_killed--;
    //cerr << name << " " << sprite << " " << add_x << " " << add_y <<  " "  << cx << " " << cy << "\n";
    glEnable(GL_TEXTURE_2D);
    texture what=sprite;
    if (is_killed)
        what=killed_array[name];
    glBindTexture(GL_TEXTURE_2D, what);

    GLfloat addx = add_x, addy = add_y;
    //cerr << addx << " " << addy << " !\n";

    glPushMatrix();
        glColor4f(1,1,1,0.8);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(cx - 2*R/3 + addx, cy - 2*R/3 + 7 * R / 100 + addy);
            glTexCoord2f(1, 0); glVertex2f(cx + 2*R/3 + addx, cy - 2*R/3 + 7 * R / 100 + addy);
            glTexCoord2f(1, 1); glVertex2f(cx + 2*R/3 + addx, cy + 2*R/3 + 7 * R / 100 + addy);
            glTexCoord2f(0, 1); glVertex2f(cx - 2*R/3 + addx, cy + 2*R/3 + 7 * R / 100 + addy);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void Cell :: draw(int l, int u)
{
    GLuint tex = 0;
    if (fort != NULL) relief = FORT;
    tex = relief_texture[relief][color][shined];
    if (snow && fort == NULL) tex = relief_texture[SNOW][color][shined];
    if (town != NULL) tex = town_sprite[color][shined];
    if (village) tex=village_texture[shined];
    ld cx = 1.25 * R + 1.5 * (R - 2.5) * x - l;
    ld cy = 120 + (x%2) * R_ + R_ + (2*y) * R_ - u;
    drawHex(tex, cx, cy, color);
    if (general != NULL) stck.pb(mp(general, mp(cx, cy)));
}

void set_color(int country)
{
    //cout << country << "\n";
    switch (country)
    {
    case FRANCE:
        glColor4f(0.8125, 0.2, 0.91, 0.8);
        break;
    case GERMANY:
        glColor4f(0.6, 0.03, 0.03, 0.9);
        break;
    case UKRAINE:
        glColor4f(1, 1, 0, 0.95);
        break;
    case RUSSIA:
        glColor4f(0.31, 0.0625, 0.371, 0.95);
        break;
    case USA:
        glColor4f(0.4726, 0, 0.762, 0.9);
        break;
    case ENGLAND:
        glColor4f(0.578, 0.4609, 0.574, 1);
        break;
    case NONE:
        glColor4f(1, 1, 1, 1);
        break;
    }
}

void maximize()
{
    R += 2;
    curl += min((ld)1.5*M + 1.75, width/(R));
    curr -= min((ld)1.5*M + 1.75, width/(R));
    curu += min((ld)2*N + cos(PI/6), height/(R));
    curd -= min((ld)2*N + cos(PI/6), height/(R));
    ml = 0, mu = 0, mr = 1.25 * R + 1.5 * (R - 2.5) * (N-1) + 1.5*R , md = 130 + (2*M) * R_ + R_;
    if (mr < width)
    {
        ml = -(mr + width)/2 + mr;
        curl = ml;
        mr = ml + mr;
    }
    if (md < height)
    {
        mu = -(md + height)/2 + md;
        curu = mu;
        md = mu + md;
    }
}

void try_move_cam(int& state, int key, int& l, int& r, int &d, int &u)
{
    if (state == -1) state = 1;
    else if (state == 1) state = 0;
    else if (state == 0) state = 15*R/100;
    ml = 0, mu = 0, mr = 1.25 * R + 1.5 * (R - 2.5) * (N-1) + 1.5*R , md = 130 + (2*M) * R_ + R_;
    if (mr < width)
    {
        ml = -(mr + width)/2 + mr;
        l = ml;
        mr = ml + mr;
    }
    if (md < height)
    {
        mu = -(md + height)/2 + md;
        u = mu;
        md = mu + md;
    }
    if (ml < 0) mr += ml;
    if (mu < 0) md += mu;
    l = max((ld)ml, (ld)l);
    r = l + width;
    r = min((ld)r, mr);
    l = r - width;
    l = max((ld)ml, (ld)l);
    r = l + width;
    u = max((ld)mu, (ld)u);
    d = u + height;
    d = min((ld)d, md);
    u = d - height;
    u = max((ld)mu, (ld)u);
    d = u + height;
    //u = min(ld(u), md);
    //l = min(ld(l), mr);
//    cerr << R << " " << R_ << " Maximum down: " << md << "    Down: " << d << " " << u << "\nMaximum right: " << mr << "    Right: " << r << " " << l << "\n";
//    cerr << " Minimum up: " << mu << " Minimum right: " << mr << "\n";
    switch (key)
    {
    case GLUT_KEY_DOWN:
        if (d + state < md) d+=state, u+=state;
        break;

    case GLUT_KEY_UP:
        if (u - state > mu) d-=state, u-=state;
        break;

    case GLUT_KEY_RIGHT:
        if (r + state < mr) r+=state, l+=state;
        break;

    case GLUT_KEY_LEFT:
        if (l - state > ml) r-=state, l-=state;
        break;
    state = -1;
    }
}


void _outtext(string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    for (auto i:s)
        glutBitmapCharacter(font,i);
}

void _outtext(int xx,int yy,string s,void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    glRasterPos2f(xx,yy);
    _outtext(s);
}

int eps_score=0;

void drawStrokeText(int xx,int yy,string s)
{
    for (int i=0;i<3;i++)
    {
        glPushMatrix();
        glTranslatef(xx+i,yy+30.0*height/768,0);
        glScalef(0.4f,-0.28f,0);
        glColor3f(1,0.5,0);
        for (auto i:s)
            glutStrokeCharacter(GLUT_STROKE_ROMAN,i);
        glPopMatrix();
    }
}

void draw_black_cube()
{
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,ramka_for_score);
            glBegin(GL_POLYGON);
                int st_x=-100.0*width/1366;
                int w=width+1000.0*width/1366;
                int st_y=-20.0*height/768;
                int h=120.0*height/768;
                glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

int last_dermo;
void draw_buttons_pause()
{
    menu["pause22"].draw(!pause);
    menu["surrender"].draw(!pause&&player[cur_turn%2]==HUMAN);
}

void draw_score()
{
    int X = 0, Y = 0;
    for (auto q : Hexes)
        for (auto x : q)
            if (x.color == chosen_country[0]) X++;
            else if (x.color == chosen_country[1]) Y++;
    stringstream buff;
    string s;
    stringstream scoreX;
    stringstream scoreY;
    draw_black_cube();
    buff << "Turns left:" << Turns - cur_turn/2;
    s = buff.str();
    drawStrokeText(100.0*width/1366,30.0*height/768-eps_score,s);
    s=get_name(chosen_country[0]);
    drawStrokeText(width*0.7,10.0*height/768-eps_score,s);
    s=get_name(chosen_country[1]);
    drawStrokeText(width*0.7,50.0*height/768-eps_score,s);
    scoreX<<X;
    drawStrokeText(width*0.9,10.0*height/768-eps_score,scoreX.str());
    scoreY<<Y;
    drawStrokeText(width*0.9,50.0*height/768-eps_score,scoreY.str());
    draw_buttons_pause();
}

void display_field(vector<vector<Cell> >& Hexes)
{
    glLoadIdentity();
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, width, height, 0.0, 0.f, -1.f);

    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,fone);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(0,0);
                glTexCoord2f(1,0); glVertex2f(width,0);
                glTexCoord2f(1,1); glVertex2f(width,height);
                glTexCoord2f(0,1); glVertex2f(0,height);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
        for (auto x : Hexes)
            for (auto y : x)
                y.draw(curl, curu);
    glPopMatrix();

    glPushMatrix();
        for (auto q : stck)
            q.fi -> draw(q.se.fi, q.se.se);
        stck.clear();
    glPopMatrix();
    draw_score();
    if (game_ending_menu)
        draw_end_game();
    if (pause&&!surrender_menu)
        draw_pause_menu();
    if (pause_load_menu)
    {
        black_fone(0.95);
        draw_load_menu();
    }
    if (surrender_menu)
    {
        black_fone(0.95);
        draw_surrender_menu();
    }
    draw_cursor();
    glutSwapBuffers();
}

void draw_logotype()
{
    glColor4f(1,1,1,0.8);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,logo);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(75.0*width/1366, 75.0*height/768);
            glTexCoord2f(0, 1); glVertex2f(75.0*width/1366, 525.0*height/768);
            glTexCoord2f(1, 1); glVertex2f(525.0*width/1366, 525.0*height/768);
            glTexCoord2f(1, 0); glVertex2f(525.0*width/1366, 75.0*height/768);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void display_menu()
{
    if (!in_main_menu) return;

    glLoadIdentity();
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glOrtho(0.0,width,height,0.0,0.f,-1.f);

    draw_background();
    draw_logotype();
    draw_start_menu();

    if (type_of_menu=="Load_menu")
    {
        black_fone(0.95);
        draw_load_menu();
    }

    if (type_of_menu=="Check_country"||type_of_menu=="Settings"||type_of_menu=="Standart_maps")
    {
        black_fone(0.85);
        draw_check_country_menu();
    }

    if (type_of_menu=="Settings"||type_of_menu=="Standart_maps")
    {
        black_fone(0.95);
        draw_settings();
    }

    if (type_of_menu=="Standart_maps")
    {
        black_fone(0.95);
        draw_standart_maps();
    }

    draw_cursor();

    glutSwapBuffers();
}

void ContextMenu :: draw()
{
    ld r = min((ld)150, (ld)150);

    glColor4f(1,1,1,0.7);

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, menu_background);

        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(x - r, y - r*cos(PI/6));
                glTexCoord2f(1, 0); glVertex2f(x + r, y - r*cos(PI/6));
                glTexCoord2f(1, 1); glVertex2f(x + r, y + r*cos(PI/6));
                glTexCoord2f(0, 1); glVertex2f(x - r, y + r*cos(PI/6));
            glEnd();
        glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, fortex_button);

        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(x - r, y - r*cos(PI/6));
                glTexCoord2f(1, 0); glVertex2f(x + r, y - r*cos(PI/6));
                glTexCoord2f(1, 1); glVertex2f(x + r, y + r*cos(PI/6));
                glTexCoord2f(0, 1); glVertex2f(x - r, y + r*cos(PI/6));
            glEnd();
        glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, info_button);

        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex2f(x - r, y - r*cos(PI/6));
                glTexCoord2f(1, 0); glVertex2f(x + r, y - r*cos(PI/6));
                glTexCoord2f(1, 1); glVertex2f(x + r, y + r*cos(PI/6));
                glTexCoord2f(0, 1); glVertex2f(x - r, y + r*cos(PI/6));
            glEnd();
        glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}
