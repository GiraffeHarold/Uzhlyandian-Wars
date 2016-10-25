#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

    #include "textures.h"
    #include "basic_classes.h"

    void drawHex(GLuint, GLuint, ld, ld, ld, int);
    void try_move_cam(int&, int, int&, int&, int&, int&);
    void drawStrokeText(int xx,int yy,string s);
    void set_color(int color);
    void display_field(vector<vector<Cell> >& Hexes);
    void display_menu();
    void draw_big_logotype();
    void maximize();
#endif // DRAWING_H_INCLUDED
