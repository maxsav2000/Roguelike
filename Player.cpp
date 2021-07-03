#include "Player.h"
#include <string>
#include <iostream>
#include <tuple>
bool Player::Moved() const
{
  if(coords.x == old_coords.x && coords.y == old_coords.y)
    return false;
  else
    return true;
}

void Player::ProcessInput(MovementDir dir,CommonMap &map,Image& screenBuffer,Image& background_1,
                          std::vector<StaticObj>& Static)
{
  int move_dist = move_speed * 1;
  curr_frame++;
  switch(dir)
  {
    case MovementDir::UP:
      if ((map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)!='!')&
      (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)!='!')&
      (map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)!='D')&
      (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)!='D')){//TODO

          old_coords.y = coords.y;
          coords.y += move_dist;
          if ((map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='%')|
              (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='%')){
              health = 0;
              move_speed=0;
              screenBuffer.DrowBar(0,1024,"../resources/win.png");
          }//поражаение
          if ((map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='G')|
              (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='G')){
              health = 0;
              move_speed=0;
              screenBuffer.DrowBar(0,1024,"../resources/lost.png");
          }//победа
          if ((map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='U')|
              (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='U')){
              if (freze_gamage<=0){
                  health -= 1;
                  freze_gamage=10;
              }else{
                  freze_gamage--;
              }
              PutHealth(screenBuffer,background_1);
          }//шипы
          if (map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='K'){
              keys++;
              PutKey(screenBuffer,background_1);
              map.ChengeChar(31-(coords.x)/32,31-(coords.y+32)/32,'#');
              std::tuple<int,int> map_cords(31-(coords.x)/32,31-(coords.y+32)/32);
              for (int i=0;i<Static.size();i++){
                  if ((coords.x)/32==std::get<0>(Static[i].GetCord())&
                          (coords.y+32)/32 == std::get<1>(Static[i].GetCord())){
                      Static[i].DeleteKey();
                  }
              }
          }//ключ первый угол героя
          if (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='K'){
              keys++;
              PutKey(screenBuffer,background_1);
              map.ChengeChar(31-(coords.x+31)/32,31-(coords.y+32)/32,'#');
              std::tuple<int,int> map_cords(31-(coords.x+31)/32,31-(coords.y+32)/32);
              for (int i=0;i<Static.size();i++){

                  if ((coords.x+31)/32==std::get<0>(Static[i].GetCord())&
                      (coords.y+32)/32 == std::get<1>(Static[i].GetCord())){
                      Static[i].DeleteKey();
                  }
              }

          }//ключ второй угол героя

          if (map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='T'){
              map.ChengeChar(31-(coords.x)/32,31-(coords.y+32)/32,'U');
              std::tuple<int,int> map_cords(31-(coords.x)/32,31-(coords.y+32)/32);
              for (int i=0;i<Static.size();i++){
                  if ((coords.x)/32==std::get<0>(Static[i].GetCord())&
                      (coords.y+32)/32 == std::get<1>(Static[i].GetCord())){
                      Static[i].DeleteTrap();
                  }
              }
          }//ловушка первый угол героя
          if (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='T'){
              map.ChengeChar(31-(coords.x+31)/32,31-(coords.y+32)/32,'U');
              std::tuple<int,int> map_cords(31-(coords.x+31)/32,31-(coords.y+32)/32);
              for (int i=0;i<Static.size();i++){
                  if ((coords.x+31)/32==std::get<0>(Static[i].GetCord())&
                      (coords.y+32)/32 == std::get<1>(Static[i].GetCord())){
                      Static[i].DeleteTrap();
                  }
              }

          }//ловушка второй угол героя

          if ((map.GetChar(31-(coords.x)/32,31-(coords.y+32)/32)=='x')|
              (map.GetChar(31-(coords.x+31)/32,31-(coords.y+32)/32)=='x')){
              //поменять координату игрока + фон + буффер + загрузщик
              map.PutNewCord(std::get<0>(map.GetCord())-1,std::get<1>(map.GetCord()));
              coords.y = 100;
              coords.x = 500;
              old_coords.y = coords.y;
              old_coords.x = coords.x;
          }//cмена карты

      }
      break;
    case MovementDir::DOWN:
        if ((map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)!='!')&
            (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)!='!')&
            (map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)!='D')&
            (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)!='D')){//TODO
            old_coords.y = coords.y;
            coords.y -= move_dist;


            if ((map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='%')|
                (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='%')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/win.png");
            }//поражение
            if ((map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='G')|
                (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='G')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/lost.png");
            }//поражение
            if ((map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='U')|
                (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='U')){
                if (freze_gamage<=0){
                    health -= 1;
                    freze_gamage=10;
                }else{
                    freze_gamage--;
                }
                PutHealth(screenBuffer,background_1);

            }//шипы
            if (map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x)/32,31-(coords.y-1)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x)/32,31-(coords.y-1)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y-1)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }
            }//ключ первый угол героя
            if (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x+31)/32,31-(coords.y-1)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x+31)/32,31-(coords.y-1)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x+31)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y-1)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }

            }//ключ второй угол героя
            if (map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='T'){
                map.ChengeChar(31-(coords.x)/32,31-(coords.y-1)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x)/32,31-(coords.y-1)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y-1)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }
            }//ловушка первый угол
            if (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='T'){
                map.ChengeChar(31-(coords.x+31)/32,31-(coords.y-1)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x+31)/32,31-(coords.y-1)/32);
                for (int i=0;i<Static.size();i++){
                    if ((coords.x+31)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y-1)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }

            }//ловушка второй угол

            if ((map.GetChar(31-(coords.x)/32,31-(coords.y-1)/32)=='x')|
                (map.GetChar(31-(coords.x+31)/32,31-(coords.y-1)/32)=='x')){
                //поменять координату игрока + фон + буффер + загрузщик
                map.PutNewCord(std::get<0>(map.GetCord())+1,std::get<1>(map.GetCord()));
                coords.y = 892;
                coords.x = 500;
                old_coords.y = coords.y;
                old_coords.x = coords.x;
            }
        }
      break;
    case MovementDir::LEFT:
        letf_flag=true;
        if ((map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)!='!')&
            (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)!='!')&
            (map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)!='D')&
            (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)!='D')){//TODO
            old_coords.x = coords.x;
            coords.x -= move_dist;

            if ((map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='%')|
                (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='%')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/win.png");
            }
            if ((map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='G')|
                (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='G')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/lost.png");
            }
            if ((map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='U')|
                (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='U')){
                if (freze_gamage<=0){
                    health -= 1;
                    freze_gamage=10;
                }else{
                    freze_gamage--;
                }
                PutHealth(screenBuffer,background_1);

            }//шипы
            if (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x-1)/32,31-(coords.y)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }
            }//ключ первый угол героя
            if (map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x-1)/32,31-(coords.y+31)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y+31)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }

            }//ключ второй угол героя
            if (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='T'){
                map.ChengeChar(31-(coords.x-1)/32,31-(coords.y)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }
            }//ловушка первый угол
            if (map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='T'){
                map.ChengeChar(31-(coords.x-1)/32,31-(coords.y+31)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y+31)/32);
                for (int i=0;i<Static.size();i++){
                    if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }

            }//ловушка второй угол
            if ((map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='x')|
                (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='x')){
                map.PutNewCord(std::get<0>(map.GetCord()),std::get<1>(map.GetCord())-1);
                coords.y = 500;
                coords.x = 892;
                old_coords.y = coords.y;
                old_coords.x = coords.x;
            }
        }

      break;
    case MovementDir::RIGHT:
        letf_flag = false;
        if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)!='!')&
            (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)!='!')&
            (map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)!='D')&
            (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)!='D')){//TODO
            old_coords.x = coords.x;
            coords.x += move_dist;

            if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='G')|
                (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='G')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/lost.png");
            }//победа
            if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='%')|
                (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='%')){
                health = 0;
                move_speed=0;
                screenBuffer.DrowBar(0,1024,"../resources/win.png");
            }
            if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='U')|
                (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='U')){
                if (freze_gamage<=0){
                    health -= 1;
                    freze_gamage=10;
                }else{
                    freze_gamage--;
                }
                PutHealth(screenBuffer,background_1);

            }//шипы

            if (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x+32)/32,31-(coords.y)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }
            }//ключ первый угол героя
            if (map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='K'){
                keys++;
                PutKey(screenBuffer,background_1);
                map.ChengeChar(31-(coords.x+32)/32,31-(coords.y+31)/32,'#');
                std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y+31)/32);
                for (int i=0;i<Static.size();i++){

                    if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteKey();
                    }
                }

            }//ключ второй угол героя

            if (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='T'){
                map.ChengeChar(31-(coords.x+32)/32,31-(coords.y)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y)/32);
                for (int i=0;i<Static.size();i++){
                    if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }
            }//ловушка первый угол героя
            if (map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='T'){
                map.ChengeChar(31-(coords.x+32)/32,31-(coords.y+31)/32,'U');
                std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y+31)/32);
                for (int i=0;i<Static.size();i++){
                    if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                        (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                        Static[i].DeleteTrap();
                    }
                }

            }//ловушка второй угол героя

            if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='x')|
                (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='x')){
                map.PutNewCord(std::get<0>(map.GetCord()),std::get<1>(map.GetCord())+1);
                coords.y = 500;
                coords.x = 100;
                old_coords.y = coords.y;
                old_coords.x = coords.x;

            }
        }
      break;
        case MovementDir::PUSH:
            if ((map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='D')|
                    (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='D')|
                    (map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='D')|
                    (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='D'))
            {
                if(keys>=1){
                    keys-=1;
                    PutKey(screenBuffer,background_1);
                    if (map.GetChar(31-(coords.x+32)/32,31-(coords.y+31)/32)=='D'){
                        map.ChengeChar(31-(coords.x+32)/32,31-(coords.y+31)/32,'O');
                        std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y+31)/32);
                        for (int i=0;i<Static.size();i++){
                            if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                                (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                                Static[i].OpenDoor();
                            }
                        }
                    }
                    if (map.GetChar(31-(coords.x+32)/32,31-(coords.y)/32)=='D'){
                        map.ChengeChar(31-(coords.x+32)/32,31-(coords.y)/32,'O');
                        std::tuple<int,int> map_cords(31-(coords.x+32)/32,31-(coords.y)/32);
                        for (int i=0;i<Static.size();i++){
                            if ((coords.x+32)/32==std::get<0>(Static[i].GetCord())&
                                (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                                Static[i].OpenDoor();
                            }
                        }
                    }
                    if (map.GetChar(31-(coords.x-1)/32,31-(coords.y+31)/32)=='D'){
                        map.ChengeChar(31-(coords.x-1)/32,31-(coords.y+31)/32,'O');
                        std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y+31)/32);
                        for (int i=0;i<Static.size();i++){
                            if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                                (coords.y+31)/32 == std::get<1>(Static[i].GetCord())){
                                Static[i].OpenDoor();
                            }
                        }
                    }
                    if (map.GetChar(31-(coords.x-1)/32,31-(coords.y)/32)=='D'){
                        map.ChengeChar(31-(coords.x-1)/32,31-(coords.y)/32,'O');
                        std::tuple<int,int> map_cords(31-(coords.x-1)/32,31-(coords.y)/32);
                        for (int i=0;i<Static.size();i++){
                            if ((coords.x-1)/32==std::get<0>(Static[i].GetCord())&
                                (coords.y)/32 == std::get<1>(Static[i].GetCord())){
                                Static[i].OpenDoor();
                            }
                        }
                    }


                }
            }
            break;
    default:
      break;
  }
}

void Player::Draw(Image &screen,Image &background)
{
  if(Moved())
  {
    for(int y = old_coords.y; y <= old_coords.y + tileSize; ++y)
    {
      for(int x = old_coords.x; x <= old_coords.x + tileSize; ++x)
      {
        screen.PutPixel(x, y, background.GetPixel(x,y));
      }
    }
    old_coords = coords;
  }
  curr_frame%=16;
    switch (curr_frame) {
        case 0:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_6.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_6.png");
            }
            break;
        case 1:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_6.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_6.png");
            }
            break;
        case 2:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_6.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_6.png");
            }
            break;
        case 3:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_6.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_6.png");
            }
            break;
        case 4:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_6.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_6.png");
            }
            break;
        case 5:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_7.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_7.png");
            }
            break;
        case 6:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_7.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_7.png");
            }
            break;
        case 7:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_7.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_7.png");
            }
            break;
        case 8:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_7.png");
            }else{
                image_player.DrowBack(0,0,".//resources/hero_7.png");
            }
            break;
        case 9:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_8.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_8.png");
            }
            break;
        case 10:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_8.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_8.png");
            }
            break;
        case 11:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_8.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_8.png");
            }
            break;
        case 12:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_9.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_9.png");
            }
            break;
        case 13:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_9.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_9.png");
            }
            break;
        case 14:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_9.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_9.png");
            }
            break;
        case 15:
            if (letf_flag){
                image_player.DrowBackRivers(0,0,"../resources/hero_9.png");
            }else{
                image_player.DrowBack(0,0,"../resources/hero_9.png");
            }
            break;
        default:
            break;
    }


  for(int y = coords.y; y <= coords.y + tileSize; ++y)
  {
    for(int x = coords.x; x <= coords.x + tileSize; ++x)
    {
        Pixel pix = image_player.GetPixel(x-coords.x,y-coords.y);
        if (pix.b==0 & pix.g==0 & pix.r==0){
            screen.PutPixel(x, y, background.GetPixel(x,y));
        }else{
            screen.PutPixel(x, y, image_player.GetPixel(x-coords.x,y-coords.y));
        }

    }
  }
}
void Player::PutHealth(Image &screenBuffer, Image &background_1) {
    if( health==5){
        screenBuffer.DrowBack(1320,1145,"../resources/five.png");
    }
    if( health==4){
        screenBuffer.DrowBack(1320,1145,"../resources/four.png");
    }
    if( health==3){
        screenBuffer.DrowBack(1320,1145,"../resources/three.png");
    }
    if( health==2){
        screenBuffer.DrowBack(1320,1145,"../resources/two.png");
    }
    if( health==1){
        screenBuffer.DrowBack(1320,1145,"../resources/one.png");
    }
    if (health==0){
        move_speed=0;
        screenBuffer.DrowBar(0,1024,"../resources/win.png");
    }
}
void Player::PutKey(Image& screenBuffer,Image& background_1){
    if( keys==5){
        screenBuffer.DrowBack(1480,1076,"../resources/five.png");
    }
    if( keys==4){
        screenBuffer.DrowBack(1480,1076,"../resources/four.png");
    }
    if( keys==3){
        screenBuffer.DrowBack(1480,1076,"../resources/three.png");
    }
    if( keys==2){
        screenBuffer.DrowBack(1480,1076,"../resources/two.png");
    }
    if( keys==1){
        screenBuffer.DrowBack(1480,1076,"../resources/one.png");
    }
    if (keys==0){
        screenBuffer.DrowBack(1480,1076,"../resources/zero.png");

    }
}
