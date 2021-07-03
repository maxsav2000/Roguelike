#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Image::Image(const std::string &a_path)
{
  if((data = (Pixel*)stbi_load(a_path.c_str(), &width, &height, &channels, 0)) != nullptr)
  {
    size = width * height * channels;
  }
}

Image::Image(int a_width, int a_height, int a_channels)
{
  data = new Pixel[a_width * a_height ]{};

  if(data != nullptr)
  {
    width = a_width;
    height = a_height;
    size = a_width * a_height * a_channels;
    channels = a_channels;
    self_allocated = true;
  }
}


int Image::Save(const std::string &a_path)
{
  auto extPos = a_path.find_last_of('.');
  if(a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG")
  {
    stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
  }
  else if(a_path.substr(extPos, std::string::npos) == ".jpg" || a_path.substr(extPos, std::string::npos) == ".JPG" ||
          a_path.substr(extPos, std::string::npos) == ".jpeg" || a_path.substr(extPos, std::string::npos) == ".JPEG")
  {
    stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
  }
  else
  {
    std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path << "\n";
    return 1;
  }

  return 0;
}
void Image::KillBlack() {
    for (size_t i=0;i<width*height;i++){
        Pixel pix = data[i];
        if (pix.g==0 & pix.r==0 & pix.b==0){
            data[i].a=255;
        }
    }
}
void Image::DrowImage(int x,int y,const std::string &a_path,int bright){
    Image curr_image (a_path);
    int w = curr_image.Width();
    int h = curr_image.Height();
    for (int i=x;i<x+w;i++){
        for(int j=y;j<y+h;j++){
            Pixel pix = curr_image.GetPixel(h-(i-x)-1,w-(j-y)-1);
            Pixel new_pix;
            if (bright!=500){
                double koff_bright = bright;
                koff_bright*=-(double)1/25;
                koff_bright+=1;
                new_pix.r = round(std::max((int)round(pix.r*koff_bright),25));
                new_pix.g = round(std::max((int)round(pix.g*koff_bright),25));
                new_pix.b = round(std::max((int)round(pix.b*koff_bright),25));
                new_pix.a = pix.a;
            }else{
                new_pix = pix;
            }

            data[width* j + i] = new_pix;
        }
    }
} //для рисования картинки на картинке
void Image::DrowBar(int x,int y,const std::string &a_path){
    Image curr_image (a_path);
    int w = 1024;
    int h = 224;
    for (int i=x;i<x+w;i++){
        for(int j=y;j<y+h;j++){
            Pixel pix = curr_image.GetPixel(i-x,224-(j-y)-1);
            data[width* j + i] = pix;
        }
    }
} //для рисования картинки на картинке
void Image::DrowBack(int x,int y,const std::string &a_path){
    Image curr_image (a_path);
    int w = curr_image.Width();
    int h = curr_image.Height();
    for (int i=x;i<x+w;i++){
        for(int j=y;j<y+h;j++){
            Pixel pix = curr_image.GetPixel(i-x,w-(j-y)-1);
            data[width* j + i] = pix;
        }
    }
} //для рисования картинки на картинке
void Image::DrowBackRivers(int x,int y,const std::string &a_path){
    Image curr_image (a_path);
    int w = curr_image.Width();
    int h = curr_image.Height();
    for (int i=x;i<x+w;i++){
        for(int j=y;j<y+h;j++){
            Pixel pix = curr_image.GetPixel(h-(i-x)-1,w-(j-y)-1);
            data[width* j + i] = pix;
        }
    }
} //для рисования картинки на картинке

void Image::Get_Background(std::vector<std::string>& map_info,std::vector<std::vector<int> >& bright){

    for (int i=0;i<32;i++){
        std::string line = map_info[i];
        for (int j=0;j<32;j++){
            char curr_ch = line[j];
            if (curr_ch =='#'){
                Image tree_title("../resources/floor.png");
                DrowImage(j*32,(31-i)*32,"../resources/floor.png",bright[i][j]);
            }
            if (curr_ch == '!'){
                Image tree_title("../resources/wall.png");
                DrowImage(j*32,(31-i)*32,"../resources/wall.png",bright[i][j]);
            }
            if (curr_ch == 'x'){
                Image tree_title("../resources/port.png");
                DrowImage(j*32,(31-i)*32,"../resources/port.png",bright[i][j]);
            }
            if (curr_ch == '@'){
                Image tree_title("../resources/start.png");
                DrowImage(j*32,(31-i)*32,"../resources/start.png",bright[i][j]);
            }
            if (curr_ch == 'T'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/trap_1_1.png",bright[i][j]);
            }
            if (curr_ch == 'U'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/trap_2_1.png",bright[i][j]);
            }
            if (curr_ch == 'F'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/fire_1.png",bright[i][j]);
            }
            if (curr_ch == '%'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/Lava.png",bright[i][j]);
            }
            if (curr_ch == 'K'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/key_1.png",bright[i][j]);
            }
            if (curr_ch == 'D'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/door_1.png",bright[i][j]);
            }
            if (curr_ch == 'O'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/door_2.png",bright[i][j]);
            }
            if (curr_ch == 'G'){
                Image tree_title("../resources/trap_2_4.png");
                DrowImage(j*32,(31-i)*32,"../resources/girl_1.png",bright[i][j]);
            }
        }
    }
}
void Image::CopyTitle(int x,int y, Image &im){
    for (int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            Pixel pix =im.GetPixel(x,y);
            data[width* y + x] = pix;
        }
    }
}

Image::~Image()
{
  if(self_allocated)
    delete [] data;
  else
  {
    stbi_image_free(data);
  }
}