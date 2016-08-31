#include "Input.h"

Input::Input()
{
	mouseX = 0;
	mouseY = 0;
	relativeMouseX = 0;
	relativeMouseY = 0;

	terminer = false;

	// Initialisation du tableau touches[]
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
		touches[i] = false;


	// Initialisation du tableau boutonsSouris[]
	for (int i(0); i < 8; ++i)
		boutonsSouris[i] = false;
}


Input::~Input()
{
}

void Input::updateEvenements()
{
	// Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives
	relativeMouseX = 0;
	relativeMouseY = 0;

	while (SDL_PollEvent(&theEvent))
	{
		// Switch sur le type d'évènement
		switch (theEvent.type)
		{
			// Cas d'une touche enfoncée
		case SDL_KEYDOWN:
			touches[theEvent.key.keysym.scancode] = true;
			break;

			// Cas d'une touche relâchée
		case SDL_KEYUP:
			touches[theEvent.key.keysym.scancode] = false;
			break;


			// Cas de pression sur un bouton de la souris
		case SDL_MOUSEBUTTONDOWN:
			boutonsSouris[theEvent.button.button] = true;
			break;

			// Cas du relâchement d'un bouton de la souris
		case SDL_MOUSEBUTTONUP:
			boutonsSouris[theEvent.button.button] = false;
			break;

			// Cas d'un mouvement de souris
		case SDL_MOUSEMOTION:
			mouseX = theEvent.motion.x;
			mouseY = theEvent.motion.y;
			relativeMouseX = theEvent.motion.xrel;
			relativeMouseY = theEvent.motion.yrel;
			break;

			// Cas de la fermeture de la fenêtre
		case SDL_WINDOWEVENT:
			if (theEvent.window.event == SDL_WINDOWEVENT_CLOSE)
				terminer = true;
			break;

		default:
			break;
		}
	}
}

bool Input::Quitter() const
{
	return terminer;
}

bool Input::GetTouche(const SDL_Scancode touche) const
{
	return touches[touche];
}

bool Input::GetBoutonSouris(const Uint8 bouton) const
{
	return boutonsSouris[bouton];
}

bool Input::MouvementSouris() const
{
	if (relativeMouseX == 0 && relativeMouseY == 0)
		return false;

	else
		return true;
}

int Input::GetMouseX() const
{
	return mouseX;
}

int Input::GetMouseY() const
{
	return mouseY;
}

int Input::GetRelativeMouseX() const
{
	return relativeMouseX;
}

int Input::GetRelativeMouseY() const
{
	return relativeMouseY;
}

void Input::AfficherPointeur(bool decision) const
{
	if (decision)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

void Input::CapturerPointeur(bool decision) const
{
	if (decision)
		SDL_SetRelativeMouseMode(SDL_TRUE);

	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}
