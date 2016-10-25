#ifndef BUTTON_H
#define BUTTON_H

#include <IL/ilut.h>
#include <GL/glut.h>
#define texture GLuint

template<typename type1,typename type2,typename type3> inline bool in_range(type1 a,type2 b,type3 c);

class Button
{
public:
    int st_x,st_y;
    int w,h;
    texture data[3];
    bool pressed;

    Button();
    Button(int,int,int,int,texture,texture,texture);
    void draw(bool);
    bool click();
    bool on_click();
    bool all_click();
    bool on_all_click();
};

#endif // BUTTON_H
