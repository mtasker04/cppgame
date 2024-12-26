#pragma once

#include <cppgame/Generic.h>

#include <glad/glad.h>

_INTERNAL class VBO
{
public:
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	GLuint m_ID;
};