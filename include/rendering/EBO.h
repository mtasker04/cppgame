#pragma once

#include <Generic.h>

#include <glad/glad.h>

class EBO
{
public:
	EBO();
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	GLsizei Count() const;

private:
	GLuint m_ID;
	GLsizei m_Count;
};