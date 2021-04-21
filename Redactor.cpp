#include "Redactor.h"

Redactor::Redactor()
{
	cube0 = new float[324];
	float temp0[]= {
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
	for (int i = 0; i < 324; i++)
		cube0[i] = temp0[i];
	cursor_cube = new float[108];
	float temp1[]={
		//position						
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
	for (int i = 0; i < 108; i++)
		cursor_cube[i] = temp1[i];
	verts = 36;
	cube_size = 324;
	drag_list = new bool[verts];
	for (int i = 0; i < verts; i++)
		drag_list[i] = false;
	cube1 = cube0;

	cube2 = new float[cube_size];
	for (int i = 0; i < cube_size / 9; i++)
	{
		for (int t = 0; t < 9; t++)
			cube2[i * 9 + t] = cube1[i * 9 + t];
	}
	cube1 = cube2;

	cursorTrans=new ModelTransform { glm::vec3(0.f,   1.f,   0.f),
								glm::vec3(0.f,   0.f,   0.f),
								glm::vec3(0.02f, 0.02f, 0.02f) };

	_ModelTrans=new ModelTransform { glm::vec3(0.3f, 0.5f, 0.f),	// position
									 glm::vec3(0.f, 0.f, 0.f),	// rotation
									 glm::vec3(1.f, 1.f, 1.f) };	// scale

	cube_scale = 1.0f;
	cursor_scale =  0.08f;
	is_drag = false;
	cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
}

void Redactor::is_Drag()
{
	if (is_drag)
		return;
	cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);

	glm::vec4 Position;
	glm::vec4 inPos= glm::vec4(0.f,0.f,0.f,1.f);
		
	for (int i = 0; i < verts; i++)
	{
		inPos.x = cube2[i * 9 + 0];
		inPos.y = cube2[i * 9 + 1];
		inPos.z = cube2[i * 9 + 2];
		inPos.a = 1.f;

		Position = *model * inPos;
		                                
		if ((Position.x  <= +cursorTrans->scale.x / 2 + cursorTrans->position.x)
		&&  (Position.x  >= -cursorTrans->scale.x / 2 + cursorTrans->position.x) &&
			(Position.y  <= +cursorTrans->scale.y / 2 + cursorTrans->position.y)
		&&  (Position.y  >= -cursorTrans->scale.y / 2 + cursorTrans->position.y) &&
			(Position.z  <= +cursorTrans->scale.z / 2 + cursorTrans->position.z)
		&&  (Position.z  >= -cursorTrans->scale.z / 2 + cursorTrans->position.z))
		{
			cursorColor = glm::vec3(0.2f, 0.85f, 0.2f); break;
		}
	}
}

void Redactor::x4_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 d, e, f;
	d = (a + b); d *= 0.5f;
	e = (b + c); e *= 0.5f;
	f = (c + a); f *= 0.5f;

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
	point10 = f;
	point11 = d;
}

void Redactor::detail_up()
{
	//cube2 = new float[cube_size * 4];
	float* temp = new float[cube_size * 4];
	cube2 = temp;
	for (int i = 0; i < cube_size / 9; i++)
	{
		for (int j = 0; j < 4; j++)//копирование 4 раза
		{
			for (int t = 3; t < 9; t++)// нормаль и цвет
				cube2[i * 36 + j * 9 + t] = cube1[i * 9 + t];
		}
		if ((i) % 3 == 0)
		{
			x4_triangle(
				glm::vec3(cube1[i * 9], cube1[i * 9 + 1], cube1[i * 9 + 2]),
				glm::vec3(cube1[i * 9 + 9], cube1[i * 9 + 9 + 1], cube1[i * 9 + 9 + 2]),
				glm::vec3(cube1[i * 9 + 18], cube1[i * 9 + 18 + 1], cube1[i * 9 + 18 + 2]));
			cube2[           i * 36] = point0.x;  cube2[           i * 36 + 1] = point0.y;  cube2[           i * 36 + 2] = point0.z;
			cube2[(9 * 1)  + i * 36] = point1.x;  cube2[(9 * 1)  + i * 36 + 1] = point1.y;  cube2[(9 * 1)  + i * 36 + 2] = point1.z;
			cube2[(9 * 2)  + i * 36] = point2.x;  cube2[(9 * 2)  + i * 36 + 1] = point2.y;  cube2[(9 * 2)  + i * 36 + 2] = point2.z;
			cube2[(9 * 3)  + i * 36] = point3.x;  cube2[(9 * 3)  + i * 36 + 1] = point3.y;  cube2[(9 * 3)  + i * 36 + 2] = point3.z;
			cube2[(9 * 4)  + i * 36] = point4.x;  cube2[(9 * 4)  + i * 36 + 1] = point4.y;  cube2[(9 * 4)  + i * 36 + 2] = point4.z;
			cube2[(9 * 5)  + i * 36] = point5.x;  cube2[(9 * 5)  + i * 36 + 1] = point5.y;  cube2[(9 * 5)  + i * 36 + 2] = point5.z;
			cube2[(9 * 6)  + i * 36] = point6.x;  cube2[(9 * 6)  + i * 36 + 1] = point6.y;  cube2[(9 * 6)  + i * 36 + 2] = point6.z;
			cube2[(9 * 7)  + i * 36] = point7.x;  cube2[(9 * 7)  + i * 36 + 1] = point7.y;  cube2[(9 * 7)  + i * 36 + 2] = point7.z;
			cube2[(9 * 8)  + i * 36] = point8.x;  cube2[(9 * 8)  + i * 36 + 1] = point8.y;  cube2[(9 * 8)  + i * 36 + 2] = point8.z;
			cube2[(9 * 9)  + i * 36] = point9.x;  cube2[(9 * 9)  + i * 36 + 1] = point9.y;  cube2[(9 * 9)  + i * 36 + 2] = point9.z;
			cube2[(9 * 10) + i * 36] = point10.x; cube2[(9 * 10) + i * 36 + 1] = point10.y; cube2[(9 * 10) + i * 36 + 2] = point10.z;
			cube2[(9 * 11) + i * 36] = point11.x; cube2[(9 * 11) + i * 36 + 1] = point11.y; cube2[(9 * 11) + i * 36 + 2] = point11.z;

		}
	}

	cube_size *= 4;
	verts *= 4;
	delete[]drag_list;
	drag_list = new bool[verts];
	for (int i = 0; i < verts; i++)
		drag_list[i] = false;
	cube1 = cube2;
}

glm::vec3 Redactor::normal(glm::vec3 a, glm::vec3 b)
{
	glm::vec3 plane;
	plane.x = a.y * b.z - a.z * b.y;
	plane.y =-a.x * b.z + a.z * b.x;
	plane.z = a.x * b.y - a.y * b.x;
	float length_of_v = sqrt((plane.x * plane.x) + (plane.y * plane.y) + (plane.z * plane.z));
	plane.x = plane.x / length_of_v;
	plane.y = plane.y / length_of_v;
	plane.z = plane.z / length_of_v;
	return plane;
}

void Redactor::drag()
{
	glm::vec4 Position;
	glm::vec4 inPos = glm::vec4(0.f, 0.f, 0.f, 1.f);

	for (int i = 0; i < verts; i++)
	{
		inPos.x = cube2[i * 9 + 0];
		inPos.y = cube2[i * 9 + 1];
		inPos.z = cube2[i * 9 + 2];
		inPos.a = 1.f;
		Position = *model * inPos;
		///

	   if ((Position.x <= +cursorTrans->scale.x / 2 + cursorTrans->position.x)
		&& (Position.x >= -cursorTrans->scale.x / 2 + cursorTrans->position.x) &&
		   (Position.y <= +cursorTrans->scale.y / 2 + cursorTrans->position.y)
		&& (Position.y >= -cursorTrans->scale.y / 2 + cursorTrans->position.y) &&
		   (Position.z <= +cursorTrans->scale.z / 2 + cursorTrans->position.z)
	   	&& (Position.z >= -cursorTrans->scale.z / 2 + cursorTrans->position.z))
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

void Redactor::set_normals()
{
	glm::vec3 v;
	for (int i = 0; i < cube_size / 9; i+=3)
	{
		v=normal(glm::vec3((cube2[i * 9 + 9]  - cube2[i * 9]),     (cube2[i * 9 + 9 + 1]  - cube2[i * 9 + 1]),     (cube2[i * 9 + 9 + 2]  - cube2[i * 9 + 2])), 
		         glm::vec3((cube2[i * 9 + 18] - cube2[i * 9 + 9]), (cube2[i * 9 + 18 + 1] - cube2[i * 9 + 9 + 1]), (cube2[i * 9 + 18 + 2] - cube2[i * 9 + 9 + 2])));
		for (int j =i; j <i+ 3; j++)
		{
			cube2[j * 9 + 3] = v.x;
			cube2[j * 9 + 4] = v.y;
			cube2[j * 9 + 5] = v.z;
		}
	}
}

void Redactor::set_model(glm::mat4 &m)
{
	model = &m;
}

void Redactor::drop()
{
	is_drag = false;
	for (int i = 0; i < verts; i++)
	{
		cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
		drag_list[i] = false;
	}
}

void Redactor::drag_move_to(glm::vec3 move_to)
{
//	cout << cube_scale << endl;
	for (int i = 0; i < verts; i++)
	{
		if (drag_list[i] == true)
		{
			cube2[i * 9 + 0] = move_to.x;
			cube2[i * 9 + 1] = move_to.y;
			cube2[i * 9 + 2] = move_to.z;
		}
	}
	cout << endl;
}

void Redactor::drag_move(glm::vec3 move_to)
{
	glm::vec4 move_model = glm::vec4(move_to, 1.f) ** model;
	for (int i = 0; i < verts; i++)
	{
		if (drag_list[i] == true)
		{
			cube2[i * 9 + 0] += move_model.x / _ModelTrans->scale.x/ _ModelTrans->scale.x;
			cube2[i * 9 + 1] += move_model.y / _ModelTrans->scale.y/ _ModelTrans->scale.y;
			cube2[i * 9 + 2] += move_model.z / _ModelTrans->scale.z/ _ModelTrans->scale.z;
		}
	}
	cout << endl;
}
