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
//#include "stb_image.h"

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Camera.h"
#include "Redactor.h"

using namespace std;

#pragma region lands

Redactor red[2];  
int choise = 0;

Color background = { 0.f, 0.f, 0.f, 1.f };

Camera camera(glm::vec3(0.f, 0.f, -2.f));

bool wireframeMode = false;

#pragma endregion

void OnResize(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* win, double dt)
{
	uint32_t dir = 0;

	if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
		switch (choise)
			{
			case 0:
				red[0]._ModelTrans->rotation.y -= 0.7f;
				break;
			case 1:
				red[1]._ModelTrans->rotation.y -= 0.7f;
				break;
			default:
				break;
			}
	if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		switch (choise)
			{
			case 0:
				red[0]._ModelTrans->rotation.y += 0.7f;
				break;
			case 1:
				red[1]._ModelTrans->rotation.y += 0.7f;
				break;
			default:
				break;
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
	x = newx;
	y = newy;

	camera.Move(dir, dt);
	camera.Rotate(xoffset, -yoffset);
}
 
void OnScroll(GLFWwindow* win, double x, double y)
{
	if (y<0)
	{
		switch (choise)
		{
		case 0:
			red[0].cube_scale *= 0.95f;
			break;
		case 1:
			red[1].cube_scale *= 0.95f;
			break;
		default:
			break;
		}
	//  red[0].cursor_scale  *= 0.95f;
	}
	else
	{
		switch (choise)
		{
		case 0:
			red[0].cube_scale *= 1.05f;
			break;
		case 1:
			red[1].cube_scale *= 1.05f;
			break;
		default:
			break;
		}
//		red[0].cursor_scale *= 1.05f;
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
		case GLFW_KEY_LEFT_BRACKET:
			red[0].cursor_scale *= 0.95f;
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			red[0].cursor_scale *= 1.05f;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, true);
			break;
		case GLFW_KEY_0:
			choise = 0;
			break;
		case GLFW_KEY_1:
			choise = 1;
			break;
		case GLFW_KEY_3:
			switch (choise)
			{
			case 0:
				red[0].detail_up();
				break;
			case 1:
				red[1].detail_up();
				break;
			default:
				break;
			}
		//		Sleep(500);
			break;
		case GLFW_KEY_5:
			background = { 0.6f, 0.6f, 0.6f, 1.0f };
			break;
		case GLFW_KEY_6:
			background = { 0.0f, 0.0f, 0.0f, 1.0f };
			break;
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			red[0].drag();
			red[1].drag();
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			red[0].drop();
			red[0].set_normals();
			red[1].drop();
			red[1].set_normals();
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

	//int box_width, box_height, channels;

	ModelTransform lightTrans = { glm::vec3(0.f, 0.f, 0.f),	// position
									glm::vec3(0.f, 0.f, 0.f),	// rotation
									glm::vec3(0.1f, 0.1f, 0.1f) };	// scale


#pragma region BUFFERS INITIALIZATION

	unsigned int VBO_polygon[2], VAO_polygon[2];
	glGenBuffers(1, &VBO_polygon[0]);
	glGenVertexArrays(1, &VAO_polygon[0]);

	glBindVertexArray(VAO_polygon[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * red[0].cube_size, red[0].cube2, GL_DYNAMIC_DRAW);//!!!!!!!!!!!!!!!!

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	////////////////////////////////////////////////////
	//unsigned int VBO_polygon[1], VAO_polygon[1];
	glGenBuffers(1, &VBO_polygon[1]);
	glGenVertexArrays(1, &VAO_polygon[1]);

	glBindVertexArray(VAO_polygon[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * red[1].cube_size, red[1].cube2, GL_DYNAMIC_DRAW);//!!!!!!!!!!!!!!!!

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);








	/////////////////////////////////////////////////


	GLuint CursorArrayO, CursorBO;
	glGenBuffers(1, &CursorBO);
	glGenVertexArrays(1, &CursorArrayO);

	glBindVertexArray(CursorArrayO);
	glBindBuffer(GL_ARRAY_BUFFER, CursorBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*108, red[0].cursor_cube, GL_STATIC_DRAW);

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
	glm::mat4 model , redmodel, redmodel1;

	glm::vec3 old_cursor=glm::vec3(0,0,0);

	red[0].set_model(redmodel);
	red[1].set_model(redmodel1);
	red[1]._ModelTrans->position.y = 2.f;
	red[0]._ModelTrans->position.y = -2.f;
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
		old_cursor = red[0].cursorTrans->position;
		red[0].cursorTrans->position = camera.Position + camera.Front;

		red[0].red_cursor();
		for (int i = 0; i < 2; i++)
		{
			red[i].drag_move(red[i].cursorTrans->position - old_cursor);
			red[i].is_Drag();
			red[i].cursorTrans->setScale(red[i].cursor_scale);
		}
	
		//cursor
		model = glm::mat4(1.0f);
		model = glm::translate	(model, red[0].cursorTrans->position);
		model = glm::rotate		(model, glm::radians(red[0].cursorTrans->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate		(model, glm::radians(red[0].cursorTrans->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		model = glm::rotate		(model, glm::radians(red[0].cursorTrans->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale		(model, red[0].cursorTrans->scale/2.f);

		cursor_shader->use();
		cursor_shader->setVec3("PointsColor", red[0].cursorColor);
		cursor_shader->setMatrix4F("pv", pv);
		cursor_shader->setMatrix4F("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);


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
		for (int j = 0; j < 2; j++)
			for (int i = 0; i < red[j].verts; i++)
			{
				lightTrans.position = glm::vec3(red[j].cube2[i * 9],red[j].cube2[i * 9+1],red[j].cube2[i * 9+2] ) * red[j].cube_scale  ;
				model = glm::mat4(1.0f);
				model = glm::translate(model, red[j]._ModelTrans->position);
				model = glm::rotate(model, glm::radians(red[j]._ModelTrans->rotation.x), glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, glm::radians(red[j]._ModelTrans->rotation.y), glm::vec3(0.f, 1.f, 0.f));
				model = glm::rotate(model, glm::radians(red[j]._ModelTrans->rotation.z), glm::vec3(0.f, 0.f, 1.f));
				model = glm::translate(model, lightTrans.position);
				model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
				light_shader->setMatrix4F("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		for (int i = 0; i < 2; i++)
		{
			glBindVertexArray(VAO_polygon[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_polygon[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * red[i].cube_size, red[i].cube2, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			red[i]._ModelTrans->setScale(red[i].cube_scale);
			redmodel = glm::mat4(1.0f);
			redmodel = glm::translate(redmodel, red[i]._ModelTrans->position);
			redmodel = glm::rotate(redmodel, glm::radians(red[i]._ModelTrans->rotation.x), glm::vec3(1.f, 0.f, 0.f));
			redmodel = glm::rotate(redmodel, glm::radians(red[i]._ModelTrans->rotation.y), glm::vec3(0.f, 1.f, 0.f));
			redmodel = glm::rotate(redmodel, glm::radians(red[i]._ModelTrans->rotation.z), glm::vec3(0.f, 0.f, 1.f));
			redmodel = glm::scale(redmodel, red[i]._ModelTrans->scale);

			polygon_shader->use();
			polygon_shader->setMatrix4F("pv", pv);
			polygon_shader->setMatrix4F("model", redmodel);
			polygon_shader->setBool("wireframeMode", wireframeMode);
			polygon_shader->setVec3("viewPos", camera.Position);
			polygon_shader->setVec3("lightPos", lightPos);
			polygon_shader->setVec3("lightColor", lightColor);
			polygon_shader->setVec3("ambientColor", ambientColor);

			glDrawArrays(GL_TRIANGLES, 0, red[i].verts);
		}


	/*	/// points
		cursor_shader->use();
		cursor_shader->setVec3("PointsColor", red.cursorColor);
		cursor_shader->setMatrix4F("pv", pv);
		cursor_shader->setMatrix4F("model", model);
		glDrawArrays(GL_POINTS, 0, red.verts);*/

	

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	delete polygon_shader;
	delete light_shader;
	delete cursor_shader;

	glfwTerminate();
	return 0;
}