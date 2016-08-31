#include "SceneOpenGL.h"
#include "Shader.h"
#include "Cube.h"

using namespace glm;

SceneOpenGL::SceneOpenGL(std::string theTitreFenetre, int theLargeurFenetre, int theHauteurFenetre)
{
	titreFenetre = theTitreFenetre;
	largeurFenetre = theLargeurFenetre;
	hauteurFenetre = theHauteurFenetre;
}


SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
	// Initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Version d'OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Création de la fenêtre
	fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeurFenetre, hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//initialisation de la fenetre
	if (fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	contexteOpenGL = SDL_GL_CreateContext(fenetre);

	if (contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(fenetre);
		SDL_Quit();

		return false;
	}

	return true;
}

bool SceneOpenGL::initGL()
{
	// On initialise GLEW

	GLenum initialisationGLEW(glewInit());


	// Si l'initialisation a échouée :

	if (initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


		// On quitte la SDL

		SDL_GL_DeleteContext(contexteOpenGL);
		SDL_DestroyWindow(fenetre);
		SDL_Quit();

		return false;
	}

	// Activation du Depth Buffer
	glEnable(GL_DEPTH_TEST);

	return true;
}

void SceneOpenGL::bouclePrincipale()
{
	bool terminer = false;
	unsigned int framerate = 1000 / 60;
	Uint32 debutBoucle = 0;
	Uint32 finBoucle = 0;
	Uint32 tempsEcoule = 0;


	// Matrices projection et modelview
	mat4 projection;
	mat4 modelview;

	// Initialisation
	projection = perspective(70.0, (double)largeurFenetre / hauteurFenetre, 1.0, 100.0);
	modelview = mat4(1.0);

	Cube cube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

	//angle du cube
	float angle = 0.0;
	float angleX = 0.0;

	while (!input.Quitter())
	{
		debutBoucle = SDL_GetTicks();

		// Gestion des évènements
		input.updateEvenements();

		if (input.GetTouche(SDL_SCANCODE_ESCAPE))
			break;

		if (input.GetTouche(SDL_SCANCODE_LEFT))
		{
			angle -= tempsEcoule / 10.0;
			if (angle <= -360)
			{
				angle += 0;
			}
		}

		if (input.GetTouche(SDL_SCANCODE_RIGHT))
		{
			angle += tempsEcoule / 10.0;
			if (angle >= 360)
			{
				angle -= 360;
			}
		}

		if (input.GetTouche(SDL_SCANCODE_DOWN))
		{
			angleX -= tempsEcoule / 10.0;
			if (angleX <= -360)
			{
				angleX += 0;
			}
		}

		if (input.GetTouche(SDL_SCANCODE_UP))
		{
			angleX += tempsEcoule / 10.0;
			if (angleX >= 360)
			{
				angleX -= 360;
			}
		}

		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Placement de la caméra
		modelview = lookAt(vec3(8, 8, 8), vec3(3, 0, 0), vec3(0, 1, 0));
		//modelview = mat4(1.0);

		// Sauvegarde de la matrice modelview
		mat4 sauvegardeModelview = modelview;

		modelview = rotate(modelview, angle, vec3(0, 1, 0));
		modelview = rotate(modelview, angleX, vec3(1, 0, 0));

		cube.afficher(projection, modelview);

		// Restauration de la matrice
		modelview = sauvegardeModelview;

		// Actualisation de la fenêtre
		SDL_GL_SwapWindow(fenetre);

		finBoucle = SDL_GetTicks();
		tempsEcoule = finBoucle - debutBoucle;

		if (tempsEcoule < framerate)
		{
			SDL_Delay(framerate - tempsEcoule);
		}
	}
}
