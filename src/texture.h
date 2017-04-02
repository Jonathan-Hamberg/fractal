#include <vector>

#include <glm/glm.hpp>

class Texture
{
public:
	Texture();
	Texture(int width, int height, glm::u8vec3 *data);
	~Texture();

	GLint ID();
	void UpdateData(glm::u8vec3 *data);
private:
	unsigned _texture;
	int _width;
	int _height;
};