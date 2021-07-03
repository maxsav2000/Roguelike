//
#ifndef MAIN_MAP_H
#define MAIN_MAP_H
#include "StaticObj.h"
#include <string>
#include <vector>
#include <tuple>
struct CommonMap {
    explicit CommonMap(const std::string &a_path,int x,int y);
    explicit CommonMap(char a);
    char GetChar(int x,int y);
    void ChengeChar(int x,int y,char ch);
    std::vector<std::string> GetCharInfo();
    bool IsEmpty();
    std::tuple<int,int> GetCord();
    std::tuple<int,int> GetNewCord();
    void PutNewCord(int x,int y);
    std::vector<StaticObj> GetAllStatic(std::vector<std::vector<int> >&bright);
private:
    std::tuple<int,int> cord;
    std::tuple<int,int> new_cord;

    std::vector<std::string> CharInfo;
    bool Empty;
};
struct MainMap//TODO
{
    MainMap(const std::string &a_path);
    CommonMap GetMap(int x,int y);
    void PutMap(int x,int y,CommonMap& cm);
    std::vector<std::string> GetCharInfo();
private:
    std::vector<std::string> CharInfo;
    std::vector<std::vector<CommonMap> > AllInfo;
};
std::vector<std::vector<int> > GetBright(std::vector<std::string>& map);
#endif //MAIN_MAP_H
