#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"


    void LoadAll();
    GLuint Load(GLuint& text, std::string b);
    GLuint Load(std::string b);
    void init_start_button();
    void all_menu_init();
    void init_load();
    void init_remember1();
    void init_listik();
    void init_surrender_menu();


#endif // TEXTURES_H_INCLUDED
