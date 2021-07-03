
#ifndef MAIN_STATICOBJ_H
#define MAIN_STATICOBJ_H
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
enum class TypeObj
{
    FIRE,
    TRAP,
    USED,
    GIRL,
    KEY,
    GROUND,
    OPEN,
    CLOSE
};
struct StaticObj {
    explicit StaticObj(int x,int y,char tp,int br);
    void processObj();
    void DrowObj(Image& image);
    void Drow2layer(Image& screenBuffer,Image& background);
    void DeleteKey();
    void DeleteTrap();
    void OpenDoor();
    std::tuple<int,int> GetCord();
private:
    TypeObj type;
    std::tuple<int,int> cord;
    int titles;
    int curr_titles;
    int bright;
};


#endif //MAIN_STATICOBJ_H
