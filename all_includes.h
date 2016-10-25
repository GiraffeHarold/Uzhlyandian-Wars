#ifndef MAIN_HEAD_H_INCLUDED

    #define MAIN_HEAD_H_INCLUDED

    #pragma once

    #include <GL/glut.h>
    #include <IL/ilut.h>
    #include <bits/stdc++.h>

    #define INF 1e9
    #define pb push_back
    #define mp make_pair
    #define fi first
    #define se second
    #define I "%d"
    #define II "%d%d"
    #define III "%d%d%d"
    #define IIII "%d%d%d%d"
    #define R_ cos(PI/6)*R
    #define cur_country chosen_country[cur_turn%2]
    #define log log_stream

    /// define by barik
    #define bleat cout<<"bleat !!!\n"

    using namespace std;

    typedef GLuint texture;
    typedef int Relief;
    typedef int Country;
    typedef GLuint Sprite;
    typedef vector<int> vi;
    typedef pair <int, int> pii;
    typedef vector<pii> vii;
    typedef long long ll;
    typedef unsigned long long ull;
    typedef long double ld;


    #include "global_vars.h"

    const ld PI = acos(-1.0);

    template <typename type> inline type sqr(type x)
    {
        return x*x;
    }

    #define EMPTY 0
    #define RIVER 1
    #define MOUNTAIN 2
    #define FORT 3
    #define SNOW 4

    #define FRANCE 0
    #define GERMANY 1
    #define UKRAINE 2
    #define RUSSIA 3
    #define USA 4
    #define ENGLAND 5
    #define NONE 6

    #define HUMAN 0
    #define PC 1
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

    #define EASY 0
    #define MEDIUM 1
    #define HARD 2


#endif // MAIN_HEAD_H_INCLUDED

/*
Òóò âñ³ ³íêëóäè , äåôàéíè ³ òåìïëåéòè
*/
