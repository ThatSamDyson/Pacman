#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	// Data to represent Pacman
	Vector2* _pacmanPosition;
	Rect* _pacmanSourceRect;
	Texture2D* _pacmanTexture;

	//Input methods
	void Input(int elapsedtime);

	//Wraparound
	void WrapAround();

	//Check Methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckViewportCollision();

	//Update methods
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);

	//Constant data for Game Variables 
	const float _cPacmanSpeed;

	const int _cPacmanFrameTime;

	//Menu
	Texture2D* _menuBackground; 
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _paused;

	bool _started;

	int _pacmanFrame;

	int _pacmanCurrentFrameTime;

	int _pacmanDirection;

	bool _pKeyDown;

	// Data to represent Munchie
	int _frameCount;
	int _munchieFrame;
	int _munchieCurrentFrameTime;
	const int _cMunchieFrameTime;
	Rect* _munchieRect;
	Texture2D* _munchieBlueTexture;
	Texture2D* _munchieInvertedTexture;

	//Data for Apple
	int _appleframeCount;
	int _appleFrame;
	int _appleCurrentFrameTime;
	const int _cAppleFrameTime;
	Rect* _appleRect;
	Texture2D* _appleBlueTexture;
	Texture2D* _appleRedTexture;


	// Position for String
	Vector2* _stringPosition;

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};