#ifndef GENERALS_H_INCLUDED
#define GENERALS_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"
    #include "global_vars.h"

    General* next_gen(int, int, int);
    void renew_turns();
    void log_generals(int);
    void log_generals_file(int);

#endif // GENERALS_H_INCLUDED
