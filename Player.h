#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H
#include "Image.h"
#include "Map.h"
#include "StaticObj.h"
#include <string>
#include <tuple>
struct Point
{
  int x;
  int y;
};

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  PUSH
};

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10}, const std::string Path= (std::string& ) "") :
                 coords(pos), old_coords(coords), PathImage(Path), image_player(Path) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir,CommonMap &map,Image& screenBuffer,Image& background_1,std::vector<StaticObj>& Static);
  void Draw(Image &screen, Image &background);
  void GetImage(){image_player.KillBlack();}
  void PutHealth(Image& screenBuffer,Image& background_1);
  void PutKey(Image& screenBuffer,Image& background_1);

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  int move_speed = 4;
  int freze_gamage=0;
  std::string PathImage;
  Image image_player;
  bool letf_flag = true;
  int curr_frame=0;
  int health = 5;
  int keys = 0;
};

#endif //MAIN_PLAYER_H
