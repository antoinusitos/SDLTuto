#include "Cube.h"

Cube::Cube(float taille, std::string const vertexShader, std::string const fragmentShader) : theShader(vertexShader, fragmentShader)
{
	theShader.charger();

	taille /= 2;

	// Vertices temporaires
	float verticesTmp[] = { -taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,     // Face 1
							-taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,     // Face 1

							taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,       // Face 2
							taille, -taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 2

							-taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,      // Face 3
							-taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,    // Face 3

							-taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,        // Face 4
							-taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,        // Face 4

							-taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,     // Face 5
							-taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,     // Face 5

							-taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 6
							-taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille };      // Face 6

																												   // Couleurs temporaires

	float couleursTmp[] = { 1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1
							1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1

							0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2
							0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2

							0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3
							0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3

							1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4
							1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

							0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5
							0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

							0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 6
							0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0 };          // Face 6

	// Copie des valeurs dans les tableaux finaux
	for (int i = 0; i < 108; ++i)
	{
		vertices[i] = verticesTmp[i];
		couleurs[i] = couleursTmp[i];
	}
}


Cube::~Cube()
{
}

void Cube::afficher(mat4 & projection, mat4 & modelview)
{
	// Activation du shader
	glUseProgram(theShader.getProgramID());

		// On remplie puis on active le tableau Vertex Attrib 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// On rentre les couleurs dans le tableau Vertex Attrib 1
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, couleurs);
		glEnableVertexAttribArray(1);

		// On envoie les matrices au shader
		glUniformMatrix4fv(glGetUniformLocation(theShader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(theShader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

		// On affiche le triangle
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// On désactive le tableau Vertex Attrib
		glEnableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

	// Désactivation du shader
	glUseProgram(0);
}
