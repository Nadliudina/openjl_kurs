#include "Redactor.h"
float Redactor::cursor_scale;
float* Redactor::cursor_cube = nullptr;
bool Redactor::is_drag;
int Redactor::countOfcubes;
int Redactor::accuracy;
int Redactor::selected_accuracy;
ModelTransform* Redactor::cursorTrans = nullptr;
glm::vec3 Redactor::cursorColor;
TButton Redactor::pointInCenter;
glm::vec3 Redactor::frontOfCamera;
bool Redactor::drag_all_points;

 Redactor::Redactor()
{
	cube0 = new float[324];
	float temp0[]= {
		//position			normal					color			
	-1.0f,-1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f,-1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,//????? 18*6*3=324
	-1.0f,-1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f, 1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f, 1.0f,-1.0f,	-1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,

	 1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f,
	-1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f,
	-1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f, 	0.38f,0.43f,0.68f, //?? ???
	 1.0f, 1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,
	 1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,
	-1.0f,-1.0f,-1.0f,	 0.0f, 0.0f, -1.0f,		0.38f,0.43f,0.68f,

	 1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,//???
	 1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f,-1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f,-1.0f,-1.0f,	 0.0f, -1.0f,  0.0f,	0.38f,0.43f,0.68f,

	-1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
	-1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
	 1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,//?? ???
	 1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
	-1.0f, 1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,
	 1.0f,-1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,		0.38f,0.43f,0.68f,

	 1.0f, 1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f,-1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f, 1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,//????
	 1.0f,-1.0f,-1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f, 1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f,-1.0f, 1.0f,	 1.0f,  0.0f,  0.0f,	0.38f,0.43f,0.68f,

	 1.0f, 1.0f, 1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
	 1.0f, 1.0f,-1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,
	-1.0f, 1.0f,-1.0f,	 0.0f,  1.0f,  0.0f,	0.38f,0.43f,0.68f,//????
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
	-1.0f, 1.0f, 1.0f,	//?????
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,

	 1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,	 //?? ???
	 1.0f, 1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,

	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	 1.0f,-1.0f,-1.0f,	//???
	 1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,

	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,	//?? ???
	 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,

	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f,-1.0f,	//????
	 1.0f,-1.0f,-1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,

	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,	//????
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
	cursor_scale =  0.04f;
	is_drag = false;
	//cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
	pointInCenter = {
 "cursor",{ glm::vec3(-0.f, 0.0f, 0.f),
			glm::vec3(0.f, 0.0f, 0.f),
			glm::vec3(0.05f, 0.05f, 0.05f) } ,{ 1.0f, 1.f, 1.f, 1.0f }
	};
	accuracy = 500;
	drag_all_points = false;
}

void Redactor::red_cursor()
{
	if (!is_drag)
	{
		cursorColor = glm::vec3(0.85f, 0.2f, 0.2f);
		pointInCenter.color.r = 0.85f;
		pointInCenter.color.g = 0.2f;
		pointInCenter.color.b = 0.2f;
	}
}

//void Redactor::saveAll( Redactor* ptr)
//{
//	string str;
//	for (int i = 0; i < countOfcubes; i++)
//	{
//		cout <<"\n___"<< countOfcubes<<" __________________________________________________\n";
//		str += 	ptr[i].serialize();
//	}
//	cout << endl << str << endl;
//}

string Redactor::serialize()
{
	nlohmann::json jn{};
	jn["cube_scale"]	= cube_scale;
	jn["verts"]			= verts;
	//_ModelTrans
	nlohmann::json pos_list = nlohmann::json::array();
	pos_list.push_back(_ModelTrans->position.x);
	pos_list.push_back(_ModelTrans->position.y);
	pos_list.push_back(_ModelTrans->position.z);
	jn["position"] = pos_list;
	nlohmann::json rot_list = nlohmann::json::array();
	rot_list.push_back(_ModelTrans->rotation.x);
	rot_list.push_back(_ModelTrans->rotation.y);
	rot_list.push_back(_ModelTrans->rotation.z);
	jn["rotation"] = rot_list;
	nlohmann::json scale_list = nlohmann::json::array();
	scale_list.push_back(_ModelTrans->scale.x);
	scale_list.push_back(_ModelTrans->scale.y);
	scale_list.push_back(_ModelTrans->scale.z);
	jn["scale"] = scale_list;

	nlohmann::json cube2_list = nlohmann::json::array();
	for (int i = 0; i < cube_size; i++)
	{
		cube2_list.push_back(cube2[i]);
	}
	jn["cube2"] = cube2_list;

	//cout << jn.dump() << endl;
	return jn.dump();
}

Redactor Redactor::deserialize(const std::string& data)
{
	return Redactor();
}

void Redactor::is_Drag()
{
	if (is_drag)
		return;
	
	glm::vec4 Position;
	glm::vec4 inPos= glm::vec4(0.f,0.f,0.f,1.f);
		
	for (int i = 0; i < verts; i++)
	{
		inPos.x = cube2[i * 9 + 0];
		inPos.y = cube2[i * 9 + 1];
		inPos.z = cube2[i * 9 + 2];
		inPos.a = 1.f;

		Position = *model * inPos;
		for (int j = 0; j < accuracy; j++)
		if ((Position.x  <= +cursorTrans->scale.x / 2 + cursorTrans->position.x + 0.01f * frontOfCamera.x * j)
		&&  (Position.x  >= -cursorTrans->scale.x / 2 + cursorTrans->position.x + 0.01f * frontOfCamera.x * j) &&
			(Position.y  <= +cursorTrans->scale.y / 2 + cursorTrans->position.y + 0.01f * frontOfCamera.y * j)
		&&  (Position.y  >= -cursorTrans->scale.y / 2 + cursorTrans->position.y + 0.01f * frontOfCamera.y * j) &&
			(Position.z  <= +cursorTrans->scale.z / 2 + cursorTrans->position.z + 0.01f * frontOfCamera.z * j)
		&&  (Position.z  >= -cursorTrans->scale.z / 2 + cursorTrans->position.z + 0.01f * frontOfCamera.z * j))
		{
			cursorColor = glm::vec3(0.2f, 0.85f, 0.2f);
			pointInCenter.color.r = 0.2f;
			pointInCenter.color.g = 0.85f;
			pointInCenter.color.b = 0.2f;
			break;
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
	float* temp = new float[cube_size * 4];
	cube2 = temp;
	for (int i = 0; i < cube_size / 9; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int t = 3; t < 9; t++)// ??????? ? ????
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

Redactor::~Redactor()
{
	countOfcubes--;

	delete[] cube0;
//	delete[] cube1;
	delete[] cube2;
	delete[] drag_list;
}

glm::vec3 Redactor::normal(glm::vec3 a, glm::vec3 b)
{
	return glm::normalize(glm::cross(a, b));
}

void Redactor::drag()
{
	if (is_drag)
		return;
	glm::vec4 Position;
	glm::vec4 inPos = glm::vec4(0.f, 0.f, 0.f, 1.f);
	bool tru = false;	
	selected_accuracy = accuracy;
	for (int i = 0; i < verts; i++)
	{
		inPos.x = cube2[i * 9 + 0];
		inPos.y = cube2[i * 9 + 1];
		inPos.z = cube2[i * 9 + 2];
		inPos.a = 1.f;
		Position = *model * inPos;
		drag_list[i] = false;
	
	
	for (int j = 0; j < accuracy; j++)
		if ((Position.x  <= +cursorTrans->scale.x / 2 + cursorTrans->position.x + 0.01f * frontOfCamera.x * j)
		&&  (Position.x  >= -cursorTrans->scale.x / 2 + cursorTrans->position.x + 0.01f * frontOfCamera.x * j) &&
			(Position.y  <= +cursorTrans->scale.y / 2 + cursorTrans->position.y + 0.01f * frontOfCamera.y * j)
		&&  (Position.y  >= -cursorTrans->scale.y / 2 + cursorTrans->position.y + 0.01f * frontOfCamera.y * j) &&
			(Position.z  <= +cursorTrans->scale.z / 2 + cursorTrans->position.z + 0.01f * frontOfCamera.z * j)
		&&  (Position.z  >= -cursorTrans->scale.z / 2 + cursorTrans->position.z + 0.01f * frontOfCamera.z * j))
		{
			if (selected_accuracy < j)		break;
			if (selected_accuracy > j)
			{
				selected_accuracy = j;	cout << "selected_accuracy= " << j << endl;
			}
			drag_list[i] = true;
			is_drag = true;
			cursorColor = glm::vec3(0.2f, 0.2f, 0.85f);
			pointInCenter.color.r = 0.2f;
			pointInCenter.color.g = 0.2f;
			pointInCenter.color.b = 0.85f;
			tru = true;
			
		}
	if (tru&&drag_all_points)
	{
		for (int e = 0; e < verts; e++)
		{
			drag_list[e] = true;
		}
		break;
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

void Redactor::drop()
{
	is_drag = false;
	//float x=0,y=0,z=0;
	//static float xold = 0,yold=0,zold=0;
	for (int i = 0; i < verts; i++)
	{
//		x += cube2[i * 9 + 0];
//		y += cube2[i * 9 +1];
//		z += cube2[i * 9 + 2];
		drag_list[i] = false;
	}
//	x = x / verts;
//	y = y / verts;
//	z = z / verts;
//
//	for (int i = 0; i < verts; i++)
//	{
//		cube2[i * 9 + 0]-=x-xold;
//		cube2[i * 9 + 1]-=y-yold;
//		cube2[i * 9 + 2]-=z-zold;
//	}
//	_ModelTrans->position.x += x - xold;
//	xold = x;
//	_ModelTrans->position.y += y - yold;
//	yold = y;
//	_ModelTrans->position.z += z - zold;
//	zold = z;
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

void Redactor::set_front(glm::vec3 inFront)
{
	frontOfCamera = inFront;
}

void Redactor::drag_move(glm::vec3 move_to)
{
	//bool tru = false;
	glm::vec4 move_model = glm::vec4(move_to, 1.f) ** model;
	
	for (int i = 0; i < verts; i++)
	{
		if (drag_list[i] == true)
		{
		//	tru = true;
		//	if (!drag_all_points)
		//	{
				cube2[i * 9 + 0] += move_model.x / _ModelTrans->scale.x / _ModelTrans->scale.x * selected_accuracy * 0.01f;
				cube2[i * 9 + 1] += move_model.y / _ModelTrans->scale.y / _ModelTrans->scale.y * selected_accuracy * 0.01f;
				cube2[i * 9 + 2] += move_model.z / _ModelTrans->scale.z / _ModelTrans->scale.z * selected_accuracy * 0.01f;
		//	}
		}
	}
//	if (tru&& drag_all_points)
//	{
//		_ModelTrans->position.x += move_model.x / _ModelTrans->scale.x / _ModelTrans->scale.x * selected_accuracy * 0.01f;
//		_ModelTrans->position.y += move_model.y / _ModelTrans->scale.y / _ModelTrans->scale.y * selected_accuracy * 0.01f;
//		_ModelTrans->position.z += move_model.z / _ModelTrans->scale.z / _ModelTrans->scale.z * selected_accuracy * 0.01f;
//	}

}
