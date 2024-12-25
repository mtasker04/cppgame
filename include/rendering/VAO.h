#pragma once

#include <Generic.h>
#include <rendering/VBO.h>

#include <glad/glad.h>

class VAO
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