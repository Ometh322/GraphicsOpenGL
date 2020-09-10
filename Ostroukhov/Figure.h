#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <vector>

struct vertex {// одна вершина
	glm::vec3 position;// координаты вершины
	glm::vec3 normal;// нормаль в вершине
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

//class path {
//private:
//	GLuint vertexBuffer; // вершинный буфер (объект OpenGL)
//	void setupPath()
//	{
//		glGenVertexArrays(1, &vertexArray); // создаем вершинный массив
//		glGenBuffers(1, &vertexBuffer); // создаем вершинный буфер
//		glBindVertexArray(vertexArray); // делаем вершинный массив активным
//		// св€зываем vertexBuffer c GL_ARRAY_BUFFER
//		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//		// копируем содержимое vertices в вершинный буфер vertexBuffer
//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
//		// описание расположени€ параметра вершинного шейдера в вершинном буфере
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
//		glEnableVertexAttribArray(0); // включение параметра 0 дл€ шейдера
//		glBindBuffer(GL_ARRAY_BUFFER, 0); // отв€зка буферного объекта
//		glBindVertexArray(0); // отключение вершинного массива
//	}
//public:
//	GLuint vertexArray; // вершинный массив (объект OpenGL)
//	std::vector<glm::vec3> vertices; //последовательность точек
//	glm::vec3 color; //цвет, разбитый на состовл€ющие RGB
//	float thickness; //толщина линии
//
//	path(std::vector<glm::vec3> verts, glm::vec3 col, float thickn)
//	{
//		vertices = verts;
//		color = col;
//		thickness = thickn;
//		setupPath();
//	}
//};

class mesh {
private:
	GLuint elementBuffer; // буфер индексов вершин (объект OpenGL)
	GLuint vertexBuffer; // вершинный буфер (объект OpenGL)
	void setupMesh()
	{
		glGenVertexArrays(1, &vertexArray); // создаем вершинный массив
		glGenBuffers(1, &vertexBuffer); // создаем вершинный буфер
		glGenBuffers(1, &elementBuffer); // создаем буфер индексов

		glBindVertexArray(vertexArray); // делаем вершинный массив активным

		// св€зываем vertexBuffer c GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// копируем содержимое vertices в вершинный буфер vertexBuffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
		// описание расположени€ параметра вершинного шейдера в вершинном буфере
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0); // включение параметра 0 дл€ шейдера

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
		glEnableVertexAttribArray(1); // включение параметра 1 дл€ шейдера

		// св€зываем elementBuffer c GL_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		// копируем содержимое indices в буфер индексов elementBuffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // отв€зка буферного объекта
		glBindVertexArray(0); // отключение вершинного массива
	}
public:
	std::vector<GLuint> indices; // последовательность индексов в наборе точек
	GLuint vertexArray; // вершинный массив (объект OpenGL)
	std::vector<vertex> vertices; //последовательность точек
	Material material;

	mesh(std::vector<vertex> verts, std::vector<GLuint> inds, Material col)
	{
		vertices = verts;
		material = col;
		indices = inds;
		setupMesh();
	}
};

class model {
public:
	std::vector<mesh> figure; //составл€ющие рисунка
	glm::mat4 modelM; //модельна€ матрица
	model(std::vector<mesh> fig, glm::mat4 mat) {
		figure = fig;
		modelM = mat;
	}
};