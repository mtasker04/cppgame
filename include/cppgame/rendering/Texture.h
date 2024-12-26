#pragma once

#include <cppgame/Generic.h>
#include <cppgame/IHeapManaged.h>

#include <string>

enum class FilterMode {
	Nearest,
	Linear
};
enum class WrapMode {
	Repeat,
	MirroredRepeat,
	ClampToEdge,
	ClampToBorder
};
class Texture : public IHeapManaged
{
public:
	CPPGAPI Texture(const std::string& name, const char* path, FilterMode filter = FilterMode::Linear, WrapMode verticalWrap = WrapMode::Repeat, WrapMode horizontalWrap = WrapMode::Repeat);
	CPPGAPI ~Texture();

	void Init();

	void Bind(unsigned int unit);

	CPPGAPI const std::string& GetName() const;

	static unsigned int GetMaxTextureSlots();

public:
	void Register() override;

private:
	std::string m_Name;

	FilterMode m_FilterMode;
	WrapMode m_VerticalWrap, m_HorizontalWrap;

	const char* m_Path;
	int m_Width, m_Height, m_Channels;
	unsigned char* m_Data;

	unsigned int m_ID;
};