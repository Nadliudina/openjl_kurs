#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>
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

typedef struct
{
	string name;
	ModelTransform butTrans;
	Color color;
}TButton;

class Redactor{
public :
	static int		accuracy;//cursor
	static int		selected_accuracy;
	static glm::vec3 frontOfCamera;
	unsigned int	VBO_polygon, VAO_polygon;
	static int		countOfcubes;
	static float	cursor_scale;
	static float	* cursor_cube;
	float			cube_scale ;
	static bool		is_drag ;
	int				verts ;		//?????????? ??????
	int				cube_size ; //?????? ???????
	float			* cube0,* cube1, * cube2;
	bool			* drag_list;
	glm::mat4		* model;
	static bool		drag_all_points;
	
	static ModelTransform* cursorTrans;
	ModelTransform* _ModelTrans;
	static glm::vec3 cursorColor ;

	static TButton pointInCenter ;

	glm::vec3 point0;// for x4
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
	~Redactor();
	
	void x4_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	glm::vec3 normal(glm::vec3 a, glm::vec3 b);
	void set_normals();
	void detail_up();
	void is_Drag();//glm::mat4 &model
	void drag( );//glm::mat4 &model
	void drop();
	void drag_move(glm::vec3 move_to);
	void drag_move_to(glm::vec3 move_to);
	void red_cursor();
	void set_front(glm::vec3 inFront);
	
	//void saveAll	( Redactor* ptr);
	string serialize();
	Redactor deserialize(const std::string& data);

};

