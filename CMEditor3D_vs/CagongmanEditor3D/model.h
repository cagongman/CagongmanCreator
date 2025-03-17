#pragma once

#include <vector>
#include <QOpenGLFunctions>

class Model : protected QOpenGLFunctions
{
public:
	explicit Model(const std::string& path);
	~Model();
	void Draw();

private:
	void LoadModel(const std::string& path);
	std::vector<float> vertices;
	GLuint VAO, VBO;
};

