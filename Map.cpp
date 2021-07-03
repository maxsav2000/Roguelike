#include "Map.h"
#include "StaticObj.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
CommonMap::CommonMap(const std::string &a_path,int x,int y) {
    std::ifstream in(a_path); // окрываем файл для чтения
    if (in.is_open()) {
        for (int i=0;i<32;i++)//32-размер обычной карты TODO
        {
            std::string line;
            in >> line;
            CharInfo.push_back(line);
        }
    }
    Empty = false;
    cord = std::tuple<int,int>(x,y);
    new_cord = std::tuple<int,int>(x,y);
}
CommonMap::CommonMap(char a){
    Empty = true;
    cord = std::tuple<int,int>(-1,-1);
    new_cord = std::tuple<int,int>(-1,-1);
}
char CommonMap::GetChar(int x,int y){
    return CharInfo[y][31-x];
}
void CommonMap::ChengeChar(int x, int y,char ch) {
    CharInfo[y][31-x] = ch;
}
bool CommonMap::IsEmpty() {
    return Empty;
}
std::vector<std::string> CommonMap::GetCharInfo(){
    return CharInfo;
}
std::tuple<int,int> CommonMap::GetCord(){
    return cord;
}
std::tuple<int,int> CommonMap::GetNewCord(){
    return new_cord;
}
void CommonMap::PutNewCord(int x,int y){
    new_cord = std::tuple<int,int>(x,y);
}
std::vector<StaticObj> CommonMap::GetAllStatic(std::vector<std::vector<int> >&bright){
    std::vector<StaticObj> vec;
    for (int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            if (CharInfo[i][j]=='U'){
                StaticObj q(j,31-i,'U',bright[i][j]);
                vec.push_back(q);
            }
            if (CharInfo[i][j]=='T'){
                StaticObj q(j,31-i,'T',bright[i][j]);
                vec.push_back(q);
            }
            if (CharInfo[i][j]=='F'){
                StaticObj q(j,31-i,'F',bright[i][j]);
                vec.push_back(q);
            }
            if (CharInfo[i][j]=='G'){
                StaticObj q(j,31-i,'G',bright[i][j]);
                vec.push_back(q);
            }
            if (CharInfo[i][j]=='K'){
                StaticObj q(j,31-i,'K',bright[i][j]);
                vec.push_back(q);
            }
            if (CharInfo[i][j]=='D'){
                StaticObj q(j,31-i,'D',bright[i][j]);
                vec.push_back(q);
            }
        }
    }
    return vec;
}



MainMap::MainMap(const std::string &a_path){
    std::ifstream in(a_path); // окрываем файл для чтения

    if (in.is_open()) {
        for (int i=0;i<12;i++)//12-размер главной карты TODO
        {
            std::string line;
            in >> line;
            CharInfo.push_back(line);
            std::vector<CommonMap> vec;
            for (int j=0;j<12;j++){
                if (line[j]=='#'){
                    CommonMap q('#');
                    vec.push_back(q);
                }
                if (line[j]=='A'){
                    CommonMap q("../mapA.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='B'){
                    CommonMap q("../mapB.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='C'){
                    CommonMap q("../mapC.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='D'){
                    CommonMap q("../mapD.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='E'){
                    CommonMap q("../mapE.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='F'){
                    CommonMap q("../mapF.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='G'){
                    CommonMap q("../mapG.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='H'){
                    CommonMap q("../mapH.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='I'){
                    CommonMap q("../mapI.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='J'){
                    CommonMap q("../mapJ.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='K'){
                    CommonMap q("../mapK.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='L'){
                    CommonMap q("../mapL.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='M'){
                    CommonMap q("../mapM.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='N'){
                    CommonMap q("../mapN.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='O'){
                    CommonMap q("../mapO.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='P'){
                    CommonMap q("../mapP.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='Q'){
                    CommonMap q("../mapQ.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='R'){
                    CommonMap q("../mapR.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='S'){
                    CommonMap q("../mapS.txt",i,j);
                    vec.push_back(q);
                }
                if (line[j]=='T'){
                    CommonMap q("../mapT.txt",i,j);
                    vec.push_back(q);
                }

            }
            AllInfo.push_back(vec);
        }
    }

    //телепорты выставление
    for (int i=0;i<12;i++)//12-размер главной карты TODO
    {
        for (int j=0;j<12;j++){
            if (CharInfo[i][j]!='#' ){
                if (CharInfo[i-1][j]!='#'){
                    AllInfo[i][j].ChengeChar(15,1,'x');
                    AllInfo[i][j].ChengeChar(16,1,'x');
                    AllInfo[i][j].ChengeChar(15,2,'x');
                    AllInfo[i][j].ChengeChar(16,2,'x');
                    AllInfo[i][j].ChengeChar(17,2,'!');
                    AllInfo[i][j].ChengeChar(17,1,'!');
                    AllInfo[i][j].ChengeChar(18,1,'!');
                    AllInfo[i][j].ChengeChar(14,2,'!');
                    AllInfo[i][j].ChengeChar(14,1,'!');
                    AllInfo[i][j].ChengeChar(13,1,'!');

                }
                if (CharInfo[i+1][j]!='#'){
                    AllInfo[i][j].ChengeChar(15,29,'x');
                    AllInfo[i][j].ChengeChar(16,29,'x');
                    AllInfo[i][j].ChengeChar(15,30,'x');
                    AllInfo[i][j].ChengeChar(16,30,'x');
                    AllInfo[i][j].ChengeChar(17,29,'!');
                    AllInfo[i][j].ChengeChar(17,30,'!');
                    AllInfo[i][j].ChengeChar(18,30,'!');
                    AllInfo[i][j].ChengeChar(14,29,'!');
                    AllInfo[i][j].ChengeChar(14,30,'!');
                    AllInfo[i][j].ChengeChar(13,30,'!');
                }
                if (CharInfo[i][j+1]!='#'){
                    AllInfo[i][j].ChengeChar(1,15,'x');
                    AllInfo[i][j].ChengeChar(1,16,'x');
                    AllInfo[i][j].ChengeChar(2,15,'x');
                    AllInfo[i][j].ChengeChar(2,16,'x');
                    AllInfo[i][j].ChengeChar(2,17,'!');
                    AllInfo[i][j].ChengeChar(1,17,'!');
                    AllInfo[i][j].ChengeChar(1,18,'!');
                    AllInfo[i][j].ChengeChar(2,14,'!');
                    AllInfo[i][j].ChengeChar(1,14,'!');
                    AllInfo[i][j].ChengeChar(1,13,'!');
                }
                if (CharInfo[i][j-1]!='#'){
                    AllInfo[i][j].ChengeChar(29,15,'x');
                    AllInfo[i][j].ChengeChar(29,16,'x');
                    AllInfo[i][j].ChengeChar(30,15,'x');
                    AllInfo[i][j].ChengeChar(30,16,'x');
                    AllInfo[i][j].ChengeChar(29,17,'!');
                    AllInfo[i][j].ChengeChar(30,17,'!');
                    AllInfo[i][j].ChengeChar(30,18,'!');
                    AllInfo[i][j].ChengeChar(29,14,'!');
                    AllInfo[i][j].ChengeChar(30,14,'!');
                    AllInfo[i][j].ChengeChar(30,13,'!');
                }
            }
        }
    }

}
CommonMap MainMap::GetMap(int x,int y){
    return AllInfo[x][y];
}
std::vector<std::string> MainMap::GetCharInfo(){
    return CharInfo;
}
void MainMap::PutMap(int x, int y, CommonMap& cm) {
    AllInfo[x][y]=cm;
}

//    std::vector<std::vector<CommonMap> > AllInfo;