#pragma once

#include <cppgame/Generic.h>
#include <cppgame/rendering/VBO.h>

#include <glad/glad.h>

_INTERNAL class VAO
{
public:
	VAO(bool gen = false);

	void LinkAttribPointer(VBO& VBO, GLuint layout, GLint size, GLenum type, GLsizei stride, const void* pointer);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint m_ID;
};