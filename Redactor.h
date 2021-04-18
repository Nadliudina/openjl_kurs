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

class Redactor
{
public :

//	Camera *camera;

	float cursor_scale;

	float cube_scale ;

	bool is_drag ;

	int verts ;

	int cube_size ;

	float*cube0,* cube1, * cube2;

	float* cursor_cube;

	bool* drag_list;

	ModelTransform* cursorTrans;

	ModelTransform *polygonTrans1; 

	glm::vec3 cursorColor ;

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

	Redactor();

	void x4_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	void detail_up();
	void is_Drag();

	void drag();

	void drop();

	void drag_move(glm::vec3 move_to);

	void drag_move_to(glm::vec3 move_to);
};
