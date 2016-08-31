#ifndef DEF_CUBE
#define DEF_CUBE

// Includes OpenGL
#include "glew.h"

// Includes GLM
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"


// Includes
#include "Shader.h"

using namespace glm;

class Cube
{
public:
	Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
	~Cube();

	void afficher(mat4 &projection, mat4 &modelview);

private:
	Shader theShader;
	float vertices[108];
	float couleurs[108];
};

#endif