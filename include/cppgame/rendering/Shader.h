#pragma once

#include <cppgame/Generic.h>
#include <cppgame/IHeapManaged.h>
#include <cppgame/rendering/Texture.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* path);

_INTERNAL class Shader : public IHeapManaged
{
public:
	Shader();
	CPPGAPI Shader(const char* vertexPath, const char* fragmentPath);
	CPPGAPI ~Shader();

	void Use() const;
	void Delete() const;

	CPPGAPI void SetZOrder(int zOrder);
	CPPGAPI int GetZOrder() const;

	void SetUniformInt(const char* name, int value) const;

	CPPGAPI void AddTexture(Texture* texture);
	CPPGAPI void SetTexture(unsigned int index, Texture* texture);
	CPPGAPI Texture* GetTexture(unsigned int index);
	CPPGAPI void RemoveTexture(Texture* texture);

public:
	void Register() override;

private:
	unsigned int m_ID;
	int m_ZOrder;

	std::vector<Texture*> m_Textures;
};