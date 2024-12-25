#pragma once

#include <Generic.h>

#include <glad/glad.h>

class VBO
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