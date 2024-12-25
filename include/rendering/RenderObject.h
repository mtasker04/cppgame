#pragma once

#include <Generic.h>
#include <rendering/VAO.h>
#include <rendering/VBO.h>
#include <rendering/EBO.h>
#include <rendering/Shader.h>

class RenderObject
{
public:
	RenderObject(GLfloat* vertices, GLuint* indices, GLsizeiptr vCount, GLsizeiptr iCount, GLint stride, GLint offset, Shader shader);

	void Draw();

private:
	VAO m_VAO;
	VBO m_VBO;
	EBO m_EBO;

	Shader m_Shader;
};