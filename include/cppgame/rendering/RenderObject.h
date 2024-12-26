#pragma once

#include <cppgame/Generic.h>
#include <cppgame/rendering/VAO.h>
#include <cppgame/rendering/VBO.h>
#include <cppgame/rendering/EBO.h>
#include <cppgame/rendering/Shader.h>

_INTERNAL class RenderObject
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