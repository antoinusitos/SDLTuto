#include "SceneOpenGL.h"

int main(int argc, char **argv)
{

	SceneOpenGL scene("test de la premiere fenetre", 1000, 800);

	// Initialisation de la sc�ne
	if (scene.initialiserFenetre() == false)
		return -1;

	if (scene.initGL() == false)
		return -1;

	// Boucle Principale
	scene.bouclePrincipale();

	return 0;
}