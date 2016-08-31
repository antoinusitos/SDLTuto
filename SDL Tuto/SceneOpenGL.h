#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL

#include <windows.h>

// Includes GLM

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

// autres includes

#include "glew.h"
#include "SDL.h"
#include <string>
#include <iostream>

#include "Input.h"

class SceneOpenGL
{
public:
	SceneOpenGL(std::string theTitreFenetre, int theLargeurFenetre, int theHauteurFenetre);
	~SceneOpenGL();

	bool initialiserFenetre();
	bool initGL();
	void bouclePrincipale();

private:
	std::string titreFenetre;
	int largeurFenetre;
	int hauteurFenetre;

	SDL_Window* fenetre;
	SDL_GLContext contexteOpenGL;
	SDL_Event evenements;

	Input input;
};

#endif