#include "common.h"
#include "Image.h"
#include "Player.h"
#include "Map.h"
#include "StaticObj.h"
#include <fstream>
#include <tuple>
#include <vector>
#include <string>
#define GLFW_DLL
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 1248;

struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

void processPlayerMovement(Player &player,CommonMap &CurrMap,Image& screenBuffer,Image& background_1,std::vector<StaticObj>& Static)
{
  if (Input.keys[GLFW_KEY_W])
    player.ProcessInput(MovementDir::UP,CurrMap,screenBuffer,background_1,Static);
  else if (Input.keys[GLFW_KEY_S])
    player.ProcessInput(MovementDir::DOWN,CurrMap,screenBuffer,background_1,Static);

  if (Input.keys[GLFW_KEY_A])
    player.ProcessInput(MovementDir::LEFT,CurrMap,screenBuffer,background_1,Static);
  else if (Input.keys[GLFW_KEY_D])
    player.ProcessInput(MovementDir::RIGHT,CurrMap,screenBuffer,background_1,Static);

  if (Input.keys[GLFW_KEY_E]){
      player.ProcessInput(MovementDir::PUSH,CurrMap,screenBuffer,background_1,Static);
  }
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::cout << "Controls: "<< std::endl;
  std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "E - open the door" << std::endl;

    std::cout << "press ESC to exit" << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "To save a devochka s kare", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); 

	glfwSetKeyCallback        (window, OnKeyboardPressed);  
	glfwSetCursorPosCallback  (window, OnMouseMove); 
  glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);

	if(initGL() != 0) 
		return -1;
	
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();
  //Player

    Point starting_pos{512 , 512 };
	Player player{starting_pos,"../resources/hero_5.png"};
    player.GetImage();
    //Make curr_map
    //CommonMap CurrMap("../mapA.txt");
    MainMap mainMap("../main_map.txt");

    CommonMap CurrMap = mainMap.GetMap(6,6);

    //Make screenBuffer
	Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
    std::vector<std::string> cm = CurrMap.GetCharInfo();
    //Рассчет яркости
    std::vector<std::vector<int> > bright = GetBright(cm);

    screenBuffer.DrowBar(0,1024,"../resources/bar.png");
    screenBuffer.DrowBack(1320,1145,"../resources/five.png");

    screenBuffer.Get_Background(cm,bright);

  //Make background
    Image background_1(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    Image background_2(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    background_1.DrowBar(0,1024,"../resources/bar.png");
    screenBuffer.DrowBack(1320,1145,"../resources/five.png");
    screenBuffer.DrowBack(1530,1066,"../resources/key_bar.png");
    screenBuffer.DrowBack(1480,1076,"../resources/zero.png");
    background_1.Get_Background(cm,bright);

    background_2.Get_Background(cm,bright);
    std::vector<StaticObj> AllStatic = CurrMap.GetAllStatic(bright);

    //game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    glfwPollEvents();

    for (size_t i=0;i<AllStatic.size();i++){//process static on background
        AllStatic[i].processObj();
        AllStatic[i].DrowObj(screenBuffer);
        AllStatic[i].DrowObj(background_1);
    }
    processPlayerMovement(player,CurrMap,screenBuffer,background_1,AllStatic);
    player.Draw(screenBuffer,background_1);


    if (CurrMap.GetNewCord()!=CurrMap.GetCord()){
        //смена карты
        std::tuple<int,int> Tup = CurrMap.GetNewCord();
        std::tuple<int,int> old_cord = CurrMap.GetCord();
        CurrMap.PutNewCord(std::get<0>(old_cord),std::get<1>(old_cord));
        //старую карту обратно
        mainMap.PutMap(std::get<0>(old_cord),std::get<1>(old_cord),CurrMap);
        CurrMap=mainMap.GetMap(std::get<0>(Tup),std::get<1>(Tup));

        std::vector<std::string> curmap = CurrMap.GetCharInfo();
        bright = GetBright(curmap);
        screenBuffer.Get_Background(curmap,bright);
        background_1.Get_Background(curmap,bright);
        //замена статики
        AllStatic.clear();
        AllStatic = CurrMap.GetAllStatic(bright);
        //замена яркости

    }


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
    glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
