#include "Button.h"
#include "all_includes.h"

template<typename type1,typename type2,typename type3> inline bool in_range(type1 a,type2 b,type3 c)
{
    return a<=b&&b<=c;
}

Button::Button()
{
    this->st_x=0;
    this->st_y=0;
    this->w=0;
    this->h=0;
    this->data[0]=0;
    this->data[1]=0;
    this->data[2]=0;
    this->pressed=false;
}


Button::Button(int st_x_,int st_y_,int w_,int h_,texture t0,texture t1,texture t2)
{
    this->st_x=st_x_;
    this->st_y=st_y_;
    this->w=w_;
    this->h=h_;
    this->data[0]=t0;
    this->data[1]=t1;
    this->data[2]=t2;
    this->pressed=false;
}

void Button::draw(bool dr=true)
{
    int wh=pressed;
    if (dr)
        if (!wh&&this->on_click())
            wh=2;
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D,this->data[wh]);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0); glVertex2f(st_x,st_y);
                glTexCoord2f(1,0); glVertex2f(st_x+w,st_y);
                glTexCoord2f(1,1); glVertex2f(st_x+w,st_y+h);
                glTexCoord2f(0,1); glVertex2f(st_x,st_y+h);
            glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

bool Button::click()
{
    POINT mouse;
    GetCursorPos(&mouse);
    if (in_range(this->st_x+20.0*width/1366,mouse.x,this->st_x+w-20.0*width/1366))
        if (in_range(this->st_y,mouse.y,this->st_y+h))
            return void(this->pressed^=true), true;
    return false;
}

bool Button::on_click()
{
    POINT mouse;
    GetCursorPos(&mouse);
    if (in_range(this->st_x+20.0*width/1366,mouse.x,this->st_x+w-20.0*width/1366))
        if (in_range(this->st_y,mouse.y,this->st_y+h))
            return true;
    return false;
}

bool Button::all_click()
{
    POINT mouse;
    GetCursorPos(&mouse);
    if (in_range(this->st_x+3.0*width/1366,mouse.x,this->st_x+w-3.0*width/1366))
        if (in_range(this->st_y+3.0*height/768,mouse.y,this->st_y+h-3.0*height/768))
            return void(this->pressed^=true), true;
    return false;
}

bool Button::on_all_click()
{
    POINT mouse;
    GetCursorPos(&mouse);
    if (in_range(this->st_x+3.0*width/1366,mouse.x,this->st_x+w-3.0*width/1366))
        if (in_range(this->st_y+3.0*height/768,mouse.y,this->st_y+h-3.0*height/768))
            return true;
    return false;
}
