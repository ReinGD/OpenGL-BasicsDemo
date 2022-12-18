/*====================
	MADE BY REINGD
====================*/
#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	enum class Mode 
	{
		Single,
		Mipmapped
	};
public:

	Texture() = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	Texture(const char* file, Mode mode);

	~Texture() = default;

	unsigned int getID() const;

private:
	unsigned int textureID;
	int datasize;
	int width;
	int height;
	Mode mode;

};
#endif // !TEXTURE_H
