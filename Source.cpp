#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Camera.h"
#include "Redactor.h"
#include "stb_image.h"

using namespace std;

#pragma region defines
#define screenWidth  1280
#define screenHeight 720
#define countOfButton 4
#pragma endregion

#pragma region lands
GLFWwindow* win;
Redactor *Red[100];
int choise = 0;
Color background = { 0.f, 0.f, 0.f, 1.f };
Camera camera(glm::vec3(0.f, 0.f, -2.f));
bool wireframeMode = false;
bool menuIsOpen = false;
float  but_coord[8] = { 0,0, 100, 0,100, 30,0,30 };
Shader* polygon_shader;
Shader* light_shader;
Shader * cursor_shader;
Shader* menu_shader;
GLuint MenuArrayO, MenuBO;
int sw, sh;
int axis;//ось вращения
unsigned int menu_texture[4];

TButton btn[countOfButton] = {
{ "save",{ glm::vec3(0.f, 0.5f, 0.f),
			glm::vec3(0.f, 0.0f, 0.f),
			glm::vec3(0.5f, 0.25f, 1.f) } ,{ 0.0f, 0.6f, 0.6f, 1.0f }},
{ "add", { glm::vec3(0.0f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f, 0.25f, 1.f)} ,{ 0.0f, 1.f, 0.2f, 1.0f }},
{ "quit", { glm::vec3(0.f,-0.5f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f, 0.25f, 1.f) },{ 1.0f, 0.0f, 0.0f, 1.0f }},
{ "load", { glm::vec3(0.f,-1.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f, 0.25f, 1.f) },{ 0.0f, 0.0f, 0.0f, 1.0f }}
};
glm::mat4 p;
glm::mat4 v;
glm::mat4 pv;
glm::mat4 model;
#pragma endregion

void loadMenuTextures() {
	int channels, box_width, box_height;
	glGenTextures(4, menu_texture);
	string str;
	byte* data;
	for (int i = 0; i < 4; i++)	{
		str = ""; str += "images\\\\"; str += btn[i].name.c_str(); str += ".png";
		data = stbi_load(str.c_str(), &box_width, &box_height, &channels, 0);
		glBindTexture(GL_TEXTURE_2D, menu_texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, box_width, box_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, box_width, box_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// texture coords
	glEnableVertexAttribArray(1);
}

void OnResize(GLFWwindow* win, int width, int height){
	sw = width; sh = height;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* win, double dt){
	uint32_t dir = 0;
	if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
		switch (axis)		{
		case 0:
			(*Red[choise])._ModelTrans->rotation.x -= 0.7f;		break;
		case 1:
			(*Red[choise])._ModelTrans->rotation.y -= 0.7f;		break;
		case 2:
			(*Red[choise])._ModelTrans->rotation.z -= 0.7f;		break;
		}
	if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		switch (axis)	{
		case 0:
			(*Red[choise])._ModelTrans->rotation.x += 0.7f;		break;
		case 1:
			(*Red[choise])._ModelTrans->rotation.y += 0.7f;		break;
		case 2:
			(*Red[choise])._ModelTrans->rotation.z += 0.7f;		break;
		}

	if (glfwGetKey(win, GLFW_KEY_G) == GLFW_PRESS)
		dir |= CAM_UP;
	if (glfwGetKey(win, GLFW_KEY_B) == GLFW_PRESS)
		dir |= CAM_DOWN;
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		dir |= CAM_FORWARD;
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		dir |= CAM_BACKWARD;
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		dir |= CAM_LEFT;
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		dir |= CAM_RIGHT;
	double newx = 0.f, newy = 0.f;
	glfwGetCursorPos(win, &newx, &newy);
	static double x = newx, y = newy;
	double xoffset = newx - x;
	double yoffset = newy - y;
	x = newx; y = newy;
	camera.Move(dir, dt);
	camera.Rotate(xoffset, -yoffset);
}

void OnScroll(GLFWwindow* win, double x, double y){
	if (y < 0)
			(*Red[choise]).cube_scale *= 0.95f;
	else	(*Red[choise]).cube_scale *= 1.05f;
}

void TButton_Show(TButton btn,int ii){
	glBindVertexArray(MenuArrayO);
	model = glm::mat4(1.0f);
	model = glm::translate(model, btn.butTrans.position);
	model = glm::scale(model, btn.butTrans.scale);
	if (ii==-1)	{
		cursor_shader->use();
		cursor_shader->setMatrix4F("model", model);
		cursor_shader->setVec3("butColor", { btn.color.r, btn.color.g, btn.color.b });
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		return;
	}
	glBindTexture(GL_TEXTURE_2D, menu_texture[ii]);
	menu_shader->use();
	menu_shader->setMatrix4F("model", model);
	menu_shader->setVec3("butColor", {btn.color.r, btn.color.g, btn.color.b});
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void ShowMenu(){
	for (int i = 0; i < countOfButton; i++)
		TButton_Show(btn[i],i);
}

void ShowPointInCenter(){
		TButton_Show((*Red[0]).pointInCenter,-1);
}

void OpenMenu(){
	background = { 0.6f, 0.6f, 0.6f, 1.0f };
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void CloseMenu(){
	background = { 0.f, 0.f, 0.f, 1.0f };
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void AddNewRed(){
	static float temp = 2.1f;
	Red[(*Red[0]).countOfcubes] = new Redactor();
	(*Red[(*Red[0]).countOfcubes]).model = new glm::mat4();
	(*Red[(*Red[0]).countOfcubes])._ModelTrans->position.x = 0.f + temp;
	(*Red[(*Red[0]).countOfcubes])._ModelTrans->position.y = 0.f + temp;
	glGenBuffers	 (1, &(*Red[(*Red[0]).countOfcubes]).VBO_polygon);
	glGenVertexArrays(1, &(*Red[(*Red[0]).countOfcubes]).VAO_polygon);
	glBindVertexArray	 ((*Red[(*Red[0]).countOfcubes]).VAO_polygon);
	glBindBuffer(GL_ARRAY_BUFFER, (*Red[(*Red[0]).countOfcubes]).VBO_polygon);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*Red[(*Red[0]).countOfcubes]).cube_size, (*Red[(*Red[0]).countOfcubes]).cube2, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));	glEnableVertexAttribArray(2);
	(*Red[0]).countOfcubes++ ;
	temp += 2.1f;
}

void CheckMenuPress(double x,double y) {
	int x1, y1, x2, y2,swtc=-1;
	for (int i = 0; i < countOfButton; i++)	{
		x1 = sw / 2 + sw / 2 * btn[i].butTrans.position[0];
		x2 = x1 + sw / 2 * btn[i].butTrans.scale[0];
		y1 = sh / 2 - sh / 2 * btn[i].butTrans.position[1];
		y2 = y1 -sh / 2 * btn[i].butTrans.scale[1];
		cout << "Y1= " << y1 << endl;
		cout << "Y2= " << y2 << endl<<endl;
		if (x > x1 && x < x2 && y<y1 && y > y2)		{
			cout << "Button " <<btn[i].name << endl;
			swtc = i;
		}
	}
	if (btn[swtc].name == "add")	{
		AddNewRed();
	}
	else
	if (btn[swtc].name == "load")	{
		string str;
		ifstream iif;
		nlohmann::json json;
		iif.open("xxx.txt");
		iif >> json;
		iif.close();
		double pos[3]; int ii = 0;  float* c2;
		cout << endl << endl;
		if (json.find("x2") != json.end())	{
			int temp = (*Red[0]).countOfcubes;	
			for ( int i =-1+ temp;i>=0; i--){
				(*Red[i]).~Redactor();
				cout << "destructor\n";
			}
			for (auto const& val : json["x2"])	{
				AddNewRed();
				while ((*Red[(*Red[0]).countOfcubes - 1]).verts< stoi(val["verts"].dump()))				
					(*Red[(*Red[0]).countOfcubes - 1]).detail_up();
				(*Red[(*Red[0]).countOfcubes-1]).cube_scale = stof(val["cube_scale"].dump());
				ii = 0;
				for (auto const& val1 : val["position"]) {
					pos[ii] = stof(val1.dump());
					ii++;
				}
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->position.x = pos[0];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->position.y = pos[1];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->position.z = pos[2];
				ii = 0;
				for (auto const& val1 : val["rotation"]) {
					pos[ii] = stof(val1.dump());
					ii++;
				}
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->rotation.x = pos[0];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->rotation.y = pos[1];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->rotation.z = pos[2];
				ii = 0;
				for (auto const& val1 : val["scale"]) {
					pos[ii] = stof(val1.dump());
					ii++;
				}
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->scale.x = pos[0];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->scale.y = pos[1];
				(*Red[(*Red[0]).countOfcubes-1])._ModelTrans->scale.z = pos[2];
				ii = 0;
				for (auto const& val1 : val["cube2"]) {
					(*Red[(*Red[0]).countOfcubes - 1]).cube2[ii] = stof(val1.dump());
					ii++;
				}
			}
			(*Red[(*Red[0]).countOfcubes - 1]).drop();
			choise = 0;
		}
	}
	else
	if (btn[swtc].name == "quit")
		glfwSetWindowShouldClose(win, true);
	else
	if (btn[swtc].name == "save")
	{
		string str = "{ \"x2\":[";
		for (int i = 0; i < (*Red[0]).countOfcubes - 1; i++)		{
			str += Red[i]->serialize(); str += ",";
		}
		str += Red[(*Red[0]).countOfcubes - 1]->serialize();
		str += "]}";
		cout << str;
		ofstream of;
		of.open("xxx.txt");
		of << str;
		of.close();
		of.open("count.txt");
		of << (*Red[0]).countOfcubes;
		of.close();
	}
}

void UpdatePolygoneMode(){
	if (wireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OnKeyAction(GLFWwindow* win, int key, int scancode, int action, int mods){
	if (action == GLFW_PRESS)	{
		switch (key)	{
		case GLFW_KEY_SPACE:
			wireframeMode = !wireframeMode;
			UpdatePolygoneMode();		break;
		case GLFW_KEY_R:
			glFrontFace(GL_CCW);		break;
		case GLFW_KEY_T:
			glFrontFace(GL_CW);			break;
		case GLFW_KEY_LEFT_BRACKET:
			(*Red[0]).cursor_scale *= 0.95f;	break;
		case GLFW_KEY_RIGHT_BRACKET:
			(*Red[0]).cursor_scale *= 1.05f;	break;
		case GLFW_KEY_F:
			(*Red[0]).drag_all_points = !(*Red[0]).drag_all_points;		break;
		case GLFW_KEY_M:
			choise ++;
			if (choise >= (*Red[0]).countOfcubes)
				choise=0;					break;
		case GLFW_KEY_1:
			choise = 0;						break;
		case GLFW_KEY_3:
			(*Red[choise]).detail_up();		break;
		case GLFW_KEY_5:
			background = { 0.6f, 0.6f, 0.6f, 1.0f };	break;
		case GLFW_KEY_6:
			background = { 0.0f, 0.0f, 0.0f, 1.0f };	break;
		case GLFW_KEY_UP:
			axis++;
			if (axis >= 3)
				axis = 2;		break;
		case GLFW_KEY_DOWN:
			axis--;
			if (axis <=-1)
				axis = 0;		break;
		case GLFW_KEY_ESCAPE:
			menuIsOpen = !menuIsOpen;
			if (menuIsOpen)
				OpenMenu();
			else CloseMenu();
			break;
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	static double time1=0, time2=0;
	if (!menuIsOpen) {
		if (action == GLFW_PRESS)	{
			switch (button)
			{
			case GLFW_MOUSE_BUTTON_LEFT:
				for (int i = 0; i < (*Red[0]).countOfcubes; i++)
				(*Red[i]).drag();
					break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				for (int i = 0; i < (*Red[0]).countOfcubes; i++)	{
					(*Red[i]).drop();
					(*Red[i]).set_normals();
				}
				break;
			}
		}
	}
	else	{
		if (action == GLFW_PRESS)	{
			switch (button)		{
			case GLFW_MOUSE_BUTTON_LEFT:
				time2 = time1;
				time1 = glfwGetTime();
				if (time1-time2<0.5 )
					break;
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				CheckMenuPress(xpos,ypos);	
				break;
			}
		}
	}
}

typedef unsigned char byte;

int main(){
#pragma region WINDOW INITIALIZATION
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Window", NULL, NULL);
	if (win == NULL)	{
		std::cout << "Error. Couldn't create window!" << std::endl;
		glfwTerminate();return -1;
	}
	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	{
		std::cout << "Error. Couldn't load GLAD!" << std::endl;
		glfwTerminate();return -1;
	}
	glfwSetFramebufferSizeCallback(win, OnResize);
	glfwSetScrollCallback(win, OnScroll);
	glfwSetKeyCallback(win, OnKeyAction);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	UpdatePolygoneMode();
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
#pragma endregion

	sw = screenWidth;
	sh = screenHeight;
	axis = 0;
	(*Red[0]).countOfcubes = 0;
	ModelTransform lightTrans =	  { glm::vec3(0.f, 0.f, 0.f),	// position
									glm::vec3(0.f, 0.f, 0.f),	// rotation
									glm::vec3(0.1f, 0.1f, 0.1f) };	// scale
#pragma region BUFFERS INITIALIZATION

	(*Red[0]).countOfcubes = 1;
	Red[0]				   = new Redactor();
	(*Red[0]).model		   = new glm::mat4();
	for (int i = 0; i < (*Red[0]).countOfcubes; i++)	{
		glGenBuffers(1, &(*Red[i]).VBO_polygon);
		glGenVertexArrays(1, &(*Red[i]).VAO_polygon);
		glBindVertexArray((*Red[i]).VAO_polygon);
		glBindBuffer(GL_ARRAY_BUFFER, (*Red[i]).VBO_polygon);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*Red[i]).cube_size, (*Red[i]).cube2, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);	glEnableVertexAttribArray(0);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));	glEnableVertexAttribArray(1);		// normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));	glEnableVertexAttribArray(2);		// color
	}
	GLuint CursorArrayO, CursorBO;
	glGenBuffers(1, &CursorBO);
	glGenVertexArrays(1, &CursorArrayO);

	glBindVertexArray(CursorArrayO);
	glBindBuffer(GL_ARRAY_BUFFER, CursorBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, (*Red[0]).cursor_cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	glEnableVertexAttribArray(0);
	float menu_polygon[(12)] = {
			0.f,	0.0f,	0.0f,		
			1.f,	0.0f,	0.0f,		
			1.f,	1.f,	0.0f,		
			0.0f,	1.f,	0.0f		
	};
	glGenBuffers(1, &MenuBO);
	glGenVertexArrays(1, &MenuArrayO);
	glBindVertexArray(MenuArrayO);
	glBindBuffer(GL_ARRAY_BUFFER, MenuBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, menu_polygon, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	loadMenuTextures();
#pragma endregion

	polygon_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag");
	light_shader   = new Shader("shaders\\light.vert", "shaders\\light.frag");
	cursor_shader  = new Shader("shaders\\cursor.vert", "shaders\\cursor.frag");
	menu_shader    = new Shader("shaders\\menu.vert", "shaders\\menu.frag");
	double oldTime = glfwGetTime(), newTime, deltaTime;
	glm::vec3 lightPos = glm::vec3(1.5f, 1.3f, -2.5f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 currentColor = glm::vec3(1.0f, 0.8f, 0.2f);
	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 old_cursor = glm::vec3(0, 0, 0);
	glm::vec3 old_front = glm::vec3(0, 0, 0);

	while (!glfwWindowShouldClose(win))	{
		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (menuIsOpen)		{
			ShowMenu();
		}
		else	{
			p = camera.GetProjectionMatrix();
			v = camera.GetViewMatrix();
			pv = p * v;
			newTime = glfwGetTime();
			deltaTime = newTime - oldTime;
			oldTime = newTime;
			old_cursor = camera.Position + camera.Front;
			old_front= camera.Front;
			processInput(win, deltaTime);

			(*Red[0]).cursorTrans->position = camera.Position;
			(*Red[0]).red_cursor();
			(*Red[0]).set_front(camera.Front);
			for (int i = 0; i < (*Red[0]).countOfcubes; i++)	{
				(*Red[i]).drag_move(camera.Position + camera.Front - old_cursor);
				(*Red[i]).is_Drag();
				(*Red[i]).cursorTrans->setScale((*Red[i]).cursor_scale);
			}
			glBindVertexArray(CursorArrayO);

			// LIGH
			lightTrans.position = lightPos;
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightTrans.position);
			model = glm::scale(model, lightTrans.scale);
			light_shader->use();
			light_shader->setMatrix4F("pv", pv);
			light_shader->setMatrix4F("model", model);
			light_shader->setVec3("lightColor", lightColor);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//points_cubs
			for (int j = 0; j <(*Red[0]).countOfcubes; j++)		{
				if (choise != j)
					light_shader->setVec3("lightColor", lightColor);
				else
					light_shader->setVec3("lightColor", currentColor);
				for (int i = 0; i < (*Red[j]).verts; i++)		{
					lightTrans.position = glm::vec3((*Red[j]).cube2[i * 9], (*Red[j]).cube2[i * 9 + 1], (*Red[j]).cube2[i * 9 + 2]) * (*Red[j]).cube_scale;
					model = glm::mat4(1.0f);
					model = glm::translate(model,			(*Red[j])._ModelTrans->position);
					model = glm::rotate(model, glm::radians((*Red[j])._ModelTrans->rotation.x), glm::vec3(1.f, 0.f, 0.f));
					model = glm::rotate(model, glm::radians((*Red[j])._ModelTrans->rotation.y), glm::vec3(0.f, 1.f, 0.f));
					model = glm::rotate(model, glm::radians((*Red[j])._ModelTrans->rotation.z), glm::vec3(0.f, 0.f, 1.f));
					model = glm::translate(model, lightTrans.position);
					model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
					light_shader->setMatrix4F("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}

			// Red objects
			for (int i = 0; i < (*Red[0]).countOfcubes; i++)	{
				glBindVertexArray((*Red[i]).VAO_polygon);
				glBindBuffer(GL_ARRAY_BUFFER, (*Red[i]).VBO_polygon);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*Red[i]).cube_size, (*Red[i]).cube2, GL_DYNAMIC_DRAW);
				(*Red[i])._ModelTrans->setScale((*Red[i]).cube_scale);
				*(*Red[i]).model = glm::mat4(1.0f);
				*(*Red[i]).model = glm::translate (*((*Red[i]).model),			(*Red[i])._ModelTrans->position);
				*(*Red[i]).model = glm::rotate	  (*((*Red[i]).model), glm::radians((*Red[i])._ModelTrans->rotation.x), glm::vec3(1.f, 0.f, 0.f));
				*(*Red[i]).model = glm::rotate	  (*((*Red[i]).model), glm::radians((*Red[i])._ModelTrans->rotation.y), glm::vec3(0.f, 1.f, 0.f));
				*(*Red[i]).model = glm::rotate	  (*((*Red[i]).model), glm::radians((*Red[i])._ModelTrans->rotation.z), glm::vec3(0.f, 0.f, 1.f));
				*(*Red[i]).model = glm::scale	  (*((*Red[i]).model),				(*Red[i])._ModelTrans->scale);	
				polygon_shader->use();
				polygon_shader->setMatrix4F("pv", pv);
				polygon_shader->setMatrix4F("model", *(*Red[i]).model);
				polygon_shader->setBool("wireframeMode", wireframeMode);
				polygon_shader->setVec3("viewPos", camera.Position);
				polygon_shader->setVec3("lightPos", lightPos);
				polygon_shader->setVec3("lightColor", lightColor);
				polygon_shader->setVec3("ambientColor", ambientColor);
				glDrawArrays(GL_TRIANGLES, 0, (*Red[i]).verts);
			}
			ShowPointInCenter();
		}
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	delete polygon_shader;
	delete light_shader;
	delete cursor_shader;
	delete menu_shader;
	glfwTerminate();
	return 0;
}