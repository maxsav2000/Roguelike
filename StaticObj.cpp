#include "StaticObj.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include "Image.h"
StaticObj::StaticObj(int x,int y,char tp,int br) {
    cord = std::tuple<int,int>(x,y);
    curr_titles=0;
    bright=br;
    switch (tp) {
        case 'U':
            type = TypeObj::USED;
            titles=4;
            break;
        case 'T':
            type = TypeObj::TRAP;
            titles=16;
            break;
        case 'F':
            type = TypeObj::FIRE;
            titles=4;
            break;
        case 'G':
            type = TypeObj::GIRL;
            titles=48;
            break;
        case 'K':
            type = TypeObj::KEY;
            titles=8;
            break;
        case 'D':
            type = TypeObj::CLOSE;
            break;
        default:
            titles =-1;
            type=TypeObj::USED;
            break;
    }
}
void StaticObj::processObj(){
    int slow = 8;
    curr_titles++;
    if (curr_titles >= titles*slow){
        curr_titles = curr_titles % (titles*slow);
    }
}
void StaticObj::DrowObj(Image& image){
    int slow = 8;
    switch (type) {
        case TypeObj::FIRE:
            if (curr_titles/slow==0){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/fire_1.png",bright);

            }
            if (curr_titles/slow==1){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/fire_2.png",bright);

            }
            if (curr_titles/slow==2){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/fire_3.png",bright);

            }
            if (curr_titles/slow==3){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/fire_4.png",bright);

            }
            break;
        case TypeObj::USED:
            if (curr_titles/slow==0){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_2_1.png",bright);

            }
            if (curr_titles/slow==1){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_2_2.png",bright);

            }
            if (curr_titles/slow==2){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_2_3.png",bright);

            }
            if (curr_titles/slow==3){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_2_4.png",bright);

            }
            break;
        case TypeObj::TRAP:
            if (curr_titles/slow<15){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_1_1.png",bright);

            }else{
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/trap_1_2.png",bright);
            }
            break;
        case TypeObj::GIRL:
            if (curr_titles/slow<7){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_1.png",bright);

            }else{
                if (curr_titles/slow<10){
                    image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_2.png",bright);

                }else{
                    if (curr_titles/slow<20){
                        image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_3.png",bright);

                    }else{
                        if (curr_titles/slow<25){
                            image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_4.png",bright);

                        }else{
                            if (curr_titles/slow<30){
                                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_5.png",bright);

                            }else{
                                if (curr_titles/slow<38){
                                    image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_6.png",bright);

                                }else{
                                    if (curr_titles/slow<42){
                                        image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_7.png",bright);

                                    }else{
                                        if (curr_titles/slow<45){
                                            image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_7_2.png",bright);

                                        }else{
                                            if (curr_titles/slow<47){
                                                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/girl_8.png",bright);

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            break;
        case TypeObj::KEY:
            if (curr_titles/slow<7){
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/key_1.png",bright);
            }else{
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/key_2.png",bright);
            }
            break;
        case TypeObj::GROUND:
                image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/floor.png",bright);
            break;
        case TypeObj::CLOSE:
            image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/door_1.png",bright);
            break;
        case TypeObj::OPEN:
            image.DrowImage(std::get<0>(cord)*32,std::get<1>(cord)*32,"../resources/door_2.png",bright);
            break;
        default:
            break;
    }
}
void StaticObj::Drow2layer(Image& screenBuffer,Image& background){
    screenBuffer.CopyTitle(std::get<0>(cord)*32,std::get<1>(cord)*32,background);
}
std::vector<std::vector<int> > GetBright(std::vector<std::string>& map){
    std::vector<std::vector<int> > res = std::vector<std::vector<int> >(32,std::vector<int>(32,500));
    for (int i=1;i<31;i++){
        for (int j=1;j<31;j++){
            if (map[i][j]=='F'){
                res[i][j]=0;
            }
        }
    }
    for (int k=0;k<2048;k++){
        for (int i=1;i<31;i++){
            for (int j=1;j<31;j++){
                if (res[i][j]!=-1){
                    if(map[i+1][j]!='!'){
                        if (res[i+1][j]>res[i][j]+1){
                            res[i+1][j] = res[i][j]+1;
                        }
                    }
                    if(map[i-1][j]!='!'){
                        if (res[i-1][j]>res[i][j]+1){
                            res[i-1][j] = res[i][j]+1;
                        }
                    }
                    if(map[i][j+1]!='!'){
                        if (res[i][j+1]>res[i][j]+1){
                            res[i][j+1] = res[i][j]+1;
                        }
                    }
                    if(map[i][j-1]!='!'){
                        if (res[i][j-1]>res[i][j]+1){
                            res[i][j-1] = res[i][j]+1;
                        }
                    }
                }
            }
        }
    }

    return res;
}
void StaticObj::DeleteKey() {
    type=TypeObj::GROUND;
}
void StaticObj::DeleteTrap(){
    type=TypeObj::USED;
    titles=16;
    curr_titles=0;
}
void StaticObj::OpenDoor(){
    type=TypeObj::OPEN;
    titles=16;
    curr_titles=0;
}
std::tuple<int,int> StaticObj::GetCord(){
    return cord;
}






