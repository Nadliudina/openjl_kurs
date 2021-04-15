#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Camera.h"
using namespace std;

struct ModelTransform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void setScale(float s)
	{
		scale.x = s;
		scale.y = s;
		scale.z = s;
	}
};

struct Color {
	float r, g, b, a;
};

#pragma region lands

Color background = { 0.f, 0.f, 0.f, 1.f };

Camera camera(glm::vec3(0.f, 0.f, -2.f));

float cursor_scale = 0.08f;

float cube_scale = 1.0f;

bool is_drag = false;

bool wireframeMode = false;

int verts = 36;

//int detail_level = 1;

int cube_size = 324;

float cube0[] = {
	//position			normal					color			
-1.0f,-1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f,-1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,//право 18*6*3=324
-1.0f,-1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,

 1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f,
-1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f,
-1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f, //на нас
 1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,
 1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,
-1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,
					 
 1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,//низ
 1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
					 
-1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
-1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
 1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,//от нас
 1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
-1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
 1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
					 
 1.0f, 1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f,-1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f, 1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,//лево
 1.0f,-1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f, 1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f,-1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
					 
 1.0f, 1.0f, 1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
 1.0f, 1.0f,-1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f,-1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,//верх
 1.0f, 1.0f, 1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f,-1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
-1.0f, 1.0f, 1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f
};

float * cube1,*cube2;

float cursor_cube[] = {
	//position			normal						
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,	//право
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,

 1.0f, 1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,	 //на нас
 1.0f, 1.0f,-1.0f,
 1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,

 1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
 1.0f,-1.0f,-1.0f,	//низ
 1.0f,-1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,

-1.0f, 1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
 1.0f,-1.0f, 1.0f,	//от нас
 1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
 1.0f,-1.0f, 1.0f,

 1.0f, 1.0f, 1.0f,
 1.0f,-1.0f,-1.0f,
 1.0f, 1.0f,-1.0f,	//лево
 1.0f,-1.0f,-1.0f,
 1.0f, 1.0f, 1.0f,
 1.0f,-1.0f, 1.0f,

 1.0f, 1.0f, 1.0f,
 1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,	//верх
 1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f
};

bool *drag_list;

glm::vec3 cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);

glm::vec3 point0;
glm::vec3 point1;
glm::vec3 point2;
glm::vec3 point3;
glm::vec3 point4;
glm::vec3 point5;
glm::vec3 point6;
glm::vec3 point7;
glm::vec3 point8;
glm::vec3 point9;
glm::vec3 point10;
glm::vec3 point11;

#pragma endregion

void cube_init() {
	drag_list = new bool[verts];
	for (int i = 0; i < verts; i++)
		drag_list[i] = false;
	cube1 = cube0;
	for (int i = 0; i < cube_size; i++)
	{
		cout << cube1[i];
	}
	cube2 = new float[cube_size ];
	for (int i = 0; i < cube_size / 9; i++)
	{
			for (int t = 0; t < 9; t++)
				cube2[i * 9  + t] = cube1[i * 9 + t];
	}

}

void x4_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	glm::vec3 d, e, f;
	d = (a + b); d *= 0.5f;
	e = (b + c); e *= 0.5f;
	f = (c + a); f *= 0.5f;

	cout << "A :: X= " << a.x << " Y= " << a.y << " Z= " << a.z << endl;
	cout << "B :: X= " << b.x << " Y= " << b.y << " Z= " << b.z << endl;
	cout << "C :: X= " << c.x << " Y= " << c.y << " Z= " << c.z << endl;
	cout << "D :: X= " << d.x << " Y= " << d.y << " Z= " << d.z << endl;
	cout << "E :: X= " << e.x << " Y= " << e.y << " Z= " << e.z << endl;
	cout << "F :: X= " << f.x << " Y= " << f.y << " Z= " << f.z << endl << endl;

	point0 = a;
	point1 = d;
	point2 = f;
	point3 = d;
	point4 = b;
	point5 = e;
	point6 = e;
	point7 = c;
	point8 = f;
	point9 = e;
	point10= f;
	point11= d;
}

void detail_up() 
{
	cube2 = new float[cube_size * 4];

	for (int i = 0; i < cube_size/9; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int t = 3; t < 9; t++)
			cube2[i*36+j*9+t ] = cube1[i*9+t ];
		}
		if ((i) % 3 == 0)
		{
			x4_triangle(
				glm::vec3(cube1[i * 9],		 cube1[i * 9 + 1],      cube1[i * 9 + 2]), 
				glm::vec3(cube1[i * 9 + 9],  cube1[i * 9 + 9 + 1],  cube1[i * 9 + 9 + 2]),
				glm::vec3(cube1[i * 9 + 18], cube1[i * 9 + 18 + 1], cube1[i * 9 + 18 + 2]));
			cube2[i * 36]             = point0.x;  cube2[i * 36 + 1]           = point0.y;  cube2[i * 36 + 2]          = point0.z;
			cube2[(9 * 1)  + i * 36]  = point1.x;  cube2[(9 * 1) + i * 36 + 1] = point1.y;  cube2[(9 * 1) +i * 36 + 2] = point1.z;
			cube2[(9 * 2)  + i * 36]  = point2.x;  cube2[(9 * 2) + i * 36 + 1] = point2.y;  cube2[(9 * 2) +i * 36 + 2] = point2.z;
			cube2[(9 * 3)  + i * 36]  = point3.x;  cube2[(9 * 3) + i * 36 + 1] = point3.y;  cube2[(9 * 3) +i * 36 + 2] = point3.z;
			cube2[(9 * 4)  + i * 36]  = point4.x;  cube2[(9 * 4) + i * 36 + 1] = point4.y;  cube2[(9 * 4) +i * 36 + 2] = point4.z;
			cube2[(9 * 5)  + i * 36]  = point5.x;  cube2[(9 * 5) + i * 36 + 1] = point5.y;  cube2[(9 * 5) +i * 36 + 2] = point5.z;
			cube2[(9 * 6)  + i * 36]  = point6.x;  cube2[(9 * 6) + i * 36 + 1] = point6.y;  cube2[(9 * 6) +i * 36 + 2] = point6.z;
			cube2[(9 * 7)  + i * 36]  = point7.x;  cube2[(9 * 7) + i * 36 + 1] = point7.y;  cube2[(9 * 7) +i * 36 + 2] = point7.z;
			cube2[(9 * 8)  + i * 36]  = point8.x;  cube2[(9 * 8) + i * 36 + 1] = point8.y;  cube2[(9 * 8) +i * 36 + 2] = point8.z;
			cube2[(9 * 9)  + i * 36]  = point9.x;  cube2[(9 * 9) + i * 36 + 1] = point9.y;  cube2[(9 * 9) +i * 36 + 2] = point9.z;
			cube2[(9 * 10) + i  * 36] = point10.x; cube2[(9 * 10)+ i * 36 + 1] = point10.y; cube2[(9 * 10)+i * 36 + 2] = point10.z;
			cube2[(9 * 11) + i  * 36] = point11.x; cube2[(9 * 11)+ i * 36 + 1] = point11.y; cube2[(9 * 11)+i * 36 + 2] = point11.z;

		}
	}
	cout << "__________"<<cube_size<<"_______" << verts << "_____\n";
	
	for (int i = 0; i < cube_size / 9; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int t = 0; t < 9; t++)
			{
				if (cube2[i * 36 + j * 9 + t] >= 0)cout << " ";
				cout << cube2[i * 36 + j * 9 + t] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << endl; cout << endl;
//	detail_level++;
	cube_size *= 4;
	verts *= 4;
	delete[]drag_list;
	drag_list = new bool[verts];
	for (int i = 0; i < verts; i++)
		drag_list[i] = false;
	//delete[cube_size/4]cube1;
	cube1 = cube2;

}

void OnResize(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* win, double dt)
{

	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);
	if (glfwGetKey(win, GLFW_KEY_1) == GLFW_PRESS)
		detail_up();
	if (glfwGetKey(win, GLFW_KEY_5) == GLFW_PRESS)
		background = { 1.0f, 0.0f, 0.0f, 1.0f };
	if (glfwGetKey(win, GLFW_KEY_6) == GLFW_PRESS)
		background = { 0.0f, 1.0f, 0.0f, 1.0f };
	

	uint32_t dir = 0;

	if (glfwGetKey(win, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		dir |= CAM_UP;
	if (glfwGetKey(win, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
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
	x = newx;
	y = newy;

	camera.Move(dir, dt);
	camera.Rotate(xoffset, -yoffset);
}

void OnScroll(GLFWwindow* win, double x, double y)
{
	//camera.ChangeFOV(y);	std::cout << "Scrolled x: " << x << ", y: " << y << ". FOV = " << camera.Fov << std::endl;
	if (y<0)
	{
		cube_scale *= 0.95f;
		cursor_scale *= 0.95f;
	}
	else
	{
		cube_scale *= 1.05f;
		cursor_scale *= 1.05f;
	}
}

void UpdatePolygoneMode()
{
	if (wireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OnKeyAction(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_SPACE:
			wireframeMode = !wireframeMode;
			UpdatePolygoneMode();
			break;
		case GLFW_KEY_R:
			glFrontFace(GL_CCW);
			break;
		case GLFW_KEY_T:
			glFrontFace(GL_CW);
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			glFrontFace(GL_CW);
			break;
		}
	}
}

ModelTransform cursorTrans = { glm::vec3(0.f,   1.f,   0.f),	// position
								glm::vec3(0.f,   0.f,   0.f),	// rotation
								glm::vec3(0.02f, 0.02f, 0.02f) };	// scale

ModelTransform polygonTrans1 = { glm::vec3(0.f, 0.f, 0.f),	// position
								glm::vec3(0.f, 0.f, 0.f),	// rotation
								glm::vec3(1.f, 1.f, 1.f) };	// scale

void is_Drag() {
	if (is_drag)
		return;
	cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
	for (int i = 0; i < verts; i++)
	{
		if ((cube2[i * 9 + 0] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.x) && (cube2[i * 9 + 0] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.x) &&
			(cube2[i * 9 + 1] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.y) && (cube2[i * 9 + 1] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.y) &&
			(cube2[i * 9 + 2] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.z) && (cube2[i * 9 + 2] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.z))
		{
			cursorColor = glm::vec3(0.2f, 0.85f, 0.2f);
		}
	}
}

void drag() {
	for (int i = 0; i < verts; i++)
	{
		if ((cube2[i * 9 + 0] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.x) && (cube2[i * 9 + 0] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.x) &&
			(cube2[i * 9 + 1] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.y) && (cube2[i * 9 + 1] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.y) &&
			(cube2[i * 9 + 2] * cube_scale <= +cursor_scale / 2 + cursorTrans.position.z) && (cube2[i * 9 + 2] * cube_scale >= -cursor_scale / 2 + cursorTrans.position.z))
		{
			drag_list[i] = true;
			is_drag = true;
			cursorColor = glm::vec3(0.2f, 0.2f, 0.85f);
		}
		else
		{
			drag_list[i] = false;
		}
	}
}

void drop() {
	is_drag = false;
	for (int i = 0; i < verts; i++)
	{
		cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
		drag_list[i] = false;
	}
}

void drag_move(glm::vec3 move_to) {
	for (int i = 0; i < verts; i++)
	{
		if (drag_list[i] == true)
		{
			cube2[i * 9 + 0] += move_to.x /cube_scale;
			cube2[i * 9 + 1] += move_to.y / cube_scale;
			cube2[i * 9 + 2] += move_to.z / cube_scale;
		}
	}
	cout << endl;
}

void drag_move_to(glm::vec3 move_to) {
	cout << cube_scale << endl;
	for (int i = 0; i < verts; i++)
	{
		if (drag_list[i] == true)
		{
			cube2[i * 9 + 0] = move_to.x ;
			cube2[i * 9 + 1] = move_to.y ;
			cube2[i * 9 + 2] = move_to.z ;
		}
	}
	cout << endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			drag();
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			drop();
			break;
		default:
			break;
		}
	}

}

typedef unsigned char byte;



int main()
{
#pragma region WINDOW INITIALIZATION
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(1280, 720, "OpenGL Window", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Error. Couldn't create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error. Couldn't load GLAD!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(win, OnResize);
	glfwSetScrollCallback(win, OnScroll);
	glfwSetKeyCallback(win, OnKeyAction);
	glfwSetMouseButtonCallback(win, mouse_button_callback);

	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	UpdatePolygoneMode();
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

#pragma endregion

	int box_width, box_height, channels;

	ModelTransform lightTrans = { glm::vec3(0.f, 0.f, 0.f),	// position
									glm::vec3(0.f, 0.f, 0.f),	// rotation
									glm::vec3(0.1f, 0.1f, 0.1f) };	// scale

	cube_init();

#pragma region BUFFERS INITIALIZATION

	unsigned int VBO_polygon, VAO_polygon;
	glGenBuffers(1, &VBO_polygon);
	glGenVertexArrays(1, &VAO_polygon);

	glBindVertexArray(VAO_polygon);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_size, cube2, GL_DYNAMIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	GLuint CursorArrayO, CursorBO;
	glGenBuffers(1, &CursorBO);
	glGenVertexArrays(1, &CursorArrayO);

	glBindVertexArray(CursorArrayO);
	glBindBuffer(GL_ARRAY_BUFFER, CursorBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*108, cursor_cube, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#pragma endregion

	Shader* polygon_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag"); 
	Shader* light_shader = new Shader("shaders\\light.vert", "shaders\\light.frag");
	Shader* cursor_shader = new Shader("shaders\\cursor.vert", "shaders\\cursor.frag");

	double oldTime = glfwGetTime(), newTime, deltaTime;

	glm::vec3 lightPos = glm::vec3(1.5f, 1.3f, -2.5f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 p ;
	glm::mat4 v ;
	glm::mat4 pv;
	glm::mat4 model ;

	glm::vec3 old_cursor=glm::vec3(0,0,0);


	while (!glfwWindowShouldClose(win))
	{
		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		  p = camera.GetProjectionMatrix();
		  v = camera.GetViewMatrix();
		  pv = p * v;
		
		  newTime = glfwGetTime();
		  deltaTime = newTime - oldTime;
		  oldTime = newTime;
		  processInput(win, deltaTime);

		glBindVertexArray(CursorArrayO);
		old_cursor = cursorTrans.position;
		cursorTrans.position = camera.Position + camera.Front;
		drag_move(cursorTrans.position - old_cursor);
	//	drag_move_to(cursorTrans.position);
		is_Drag();

		cursorTrans.setScale(cursor_scale);

		model = glm::mat4(1.0f);
		model = glm::translate	(model, cursorTrans.position);
		model = glm::rotate		(model, glm::radians(cursorTrans.rotation.x), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate		(model, glm::radians(cursorTrans.rotation.y), glm::vec3(0.f, 1.f, 0.f));
		model = glm::rotate		(model, glm::radians(cursorTrans.rotation.z), glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale		(model, cursorTrans.scale/2.f);


		cursor_shader->use();
		cursor_shader->setVec3("PointsColor", cursorColor);
		cursor_shader->setMatrix4F("pv", pv);
		cursor_shader->setMatrix4F("model", model);

		glDrawArrays(GL_TRIANGLES, 0, verts);

	
		polygonTrans1.setScale(cube_scale);

		// LIGH
		lightTrans.position = lightPos;
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightTrans.position);
		model = glm::scale(model, lightTrans.scale);

		light_shader->use();
		light_shader->setMatrix4F("pv", pv);
		light_shader->setMatrix4F("model", model);
		light_shader->setVec3("lightColor", lightColor);
		glDrawArrays(GL_TRIANGLES, 0, verts);
		
		glBindVertexArray(VAO_polygon);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_size, cube2, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

//1
		model = glm::mat4(1.0f);
		model = glm::translate(model, polygonTrans1.position);
		model = glm::rotate(model, glm::radians(polygonTrans1.rotation.x), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, glm::radians(polygonTrans1.rotation.y), glm::vec3(0.f, 1.f, 0.f));
		model = glm::rotate(model, glm::radians(polygonTrans1.rotation.z), glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale(model, polygonTrans1.scale);


		polygon_shader->use();
		polygon_shader->setMatrix4F("pv", pv);
		polygon_shader->setMatrix4F("model", model);
		polygon_shader->setBool("wireframeMode", wireframeMode);
		polygon_shader->setVec3("viewPos", camera.Position);
		polygon_shader->setVec3("lightPos", lightPos);
		polygon_shader->setVec3("lightColor", lightColor);
		polygon_shader->setVec3("ambientColor", ambientColor);

		glDrawArrays(GL_TRIANGLES, 0, verts);
		/// points
		cursor_shader->use();
		cursor_shader->setVec3("PointsColor", cursorColor);
		cursor_shader->setMatrix4F("pv", pv);
		cursor_shader->setMatrix4F("model", model);
		glDrawArrays(GL_POINTS, 0, verts);

	
	


		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	delete polygon_shader;
	delete light_shader;
	delete cursor_shader;

	glfwTerminate();
	return 0;
}