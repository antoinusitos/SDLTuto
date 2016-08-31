#ifndef DEF_INPUT
#define DEF_INPUT

#include "SDL.h"

class Input
{
public:
	Input();
	~Input();

	void updateEvenements();

	bool Quitter() const;

	bool GetTouche(const SDL_Scancode touche) const;
	bool GetBoutonSouris(const Uint8 bouton) const;
	bool MouvementSouris() const;

	// Getters
	int GetMouseX() const;
	int GetMouseY() const;

	int GetRelativeMouseX() const;
	int GetRelativeMouseY() const;

	void AfficherPointeur(bool decision) const;
	void CapturerPointeur(bool decision) const;

private:
	SDL_Event theEvent;
	bool touches[SDL_NUM_SCANCODES];
	bool boutonsSouris[8];

	int mouseX;
	int mouseY;
	int relativeMouseX;
	int relativeMouseY;

	bool terminer;
};

#endif