#ifndef MAP_GENERATOR_H_INCLUDED
#define MAP_GENERATOR_H_INCLUDED

    #include "all_includes.h"
    #include "basic_classes.h"

    using namespace std;

    #define SMALL 0
    #define MIDDLE 1
    #define LARGE 2
    #define GREAT 3

    #define MAINLAND 0
    #define CONTINENTS 1
    #define ISLANDS 2

    #define VALLEY 0
    #define PIEDMONT 1
    #define MOUNTIANOUS 2


    vector< vector< Cell > > generate_map(int size, int type, int relief);
    vector< vector< Cell > > generate_empty_map(int size);
    vector < vector < Cell > > parse_map_from_file(string File_Name);
    void give_log(ofstream&);

#endif // MAP_GENERATOR_H_INCLUDED
