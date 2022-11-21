#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:

	Texture() = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

	Texture(const char* file);

	~Texture() = default;

	unsigned int getID() const;

private:
	unsigned int textureID;
	int datasize;
	int width;
	int height;

};
#endif // !TEXTURE_H
