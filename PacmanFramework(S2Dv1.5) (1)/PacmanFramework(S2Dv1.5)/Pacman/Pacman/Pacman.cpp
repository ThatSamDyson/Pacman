#include "Pacman.h"

#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f), _cPacmanFrameTime(250), _cMunchieFrameTime(500)

{

	_frameCount = 0;

	_paused = false; 

	//Initialise important Game aspects

	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();
	// Start the Game Loop - This calls Update and Draw in game loop Graphics::StartGameLoop();
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacmanTexture;
	delete _pacmanSourceRect;
	delete _munchieBlueTexture;
	delete _munchieInvertedTexture;
	delete _munchieRect;
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacmanTexture = new Texture2D();
	_pacmanTexture->Load("Textures/Pacman.tga", false);
	_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Set Menu Paramters

	_menuBackground = new Texture2D();

	_menuBackground->Load("Textures/Transparency.png", false);

	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);


	// Start the Game Loop - This calls Update and Draw in game loop Graphics::StartGameLoop();
	// 
		// Load Munchie
		_munchieBlueTexture = new Texture2D();
		_munchieBlueTexture->Load("Textures/Munchie.tga", true);
		_munchieInvertedTexture = new Texture2D();
		_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
		_munchieRect = new Rect(100.0f, 450.0f, 12, 12);
		_munchieCurrentFrameTime = 0;
		// Set string position
		_stringPosition = new Vector2(10.0f, 25.0f);

}

void Pacman::Update(int elapsedTime)
{
	if (_pacmanCurrentFrameTime > _cPacmanFrameTime)
	{
		_pacmanFrame++;

		if (_pacmanFrame >= 2)
			_pacmanFrame = 0;

		_pacmanCurrentFrameTime = 0;
	}

	Input(elapsedTime);
}
	

void Pacman::Input(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	_pacmanDirection = 0;

	if (keyboardState->IsKeyDown(Input::Keys::P))
	{

		_paused = !_paused;
	}

	if (!_paused)
	{

		// Checks if D key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::D))
			_pacmanPosition->X += 0.1f * elapsedTime; //Moves Pacman across X axis
			
		// Checks if A key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::A))
		{
			_pacmanPosition->X += -0.1f * elapsedTime; //Moves Pacman across X axis
			_pacmanDirection = 2;

		}
		// Checks if S key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::S))
		{
			_pacmanPosition->Y += 0.1f * elapsedTime; //Moves Pacman across Y axis
			_pacmanDirection = 1;
		}

		// Checks if W key is pressed
		if (keyboardState->IsKeyDown(Input::Keys::W))
		{
			_pacmanPosition->Y += -0.1f * elapsedTime; //Moves Pacman across Y axis
			_pacmanDirection = 3;
		}
		
	}
	
}


void Pacman::Draw(int elapsedTime)
{
	_pacmanCurrentFrameTime += elapsedTime;
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacmanPosition->X << " Y: " << _pacmanPosition->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_pacmanTexture, _pacmanPosition, _pacmanSourceRect); // Draws Pacman
	_pacmanSourceRect->X = _pacmanSourceRect->Width * _pacmanFrame;
	_pacmanSourceRect->Y = _pacmanSourceRect->Height * _pacmanDirection;

	if (_frameCount == 0)
	{
		// Draws Red Munchie
		SpriteBatch::Draw(_munchieInvertedTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

		_munchieCurrentFrameTime += elapsedTime;

		if (_munchieCurrentFrameTime > _cMunchieFrameTime)
		{
			_frameCount++;

			if (_frameCount >= 2)
				_frameCount = 0;

			_munchieCurrentFrameTime = 0;

		}
	}
	else
	{
		// Draw Blue Munchie
		SpriteBatch::Draw(_munchieBlueTexture, _munchieRect, nullptr, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		
		_frameCount++;

		if (_frameCount >= 60)
			_frameCount = 0;
	}
	

	// Checks if Pacman is off Screen
	// Checks if Pacman is off Screen
	if (_pacmanPosition->X > 1024) //1024 is game area width
	{
	//pacman hit right wall - reset his position
	_pacmanPosition->X = 0;
	}

	// Checks if Pacman is off Screen
	if (_pacmanPosition->X < 0) //1024 is game area width
	{
		//pacman hit left wall - reset his position
		_pacmanPosition->X = 1024;
	}

	if (_pacmanPosition->Y > 768) //1024 is game area width
	{
		//pacman hit top wall - reset his position
		_pacmanPosition->Y = 0;

	}
	
	if (_pacmanPosition->Y < 0) //1024 is game area width
	{
		//pacman hit bottom wall - reset his position
		_pacmanPosition->Y = 768;

	}

	if (_paused)
	{
		std::stringstream menuStream;
		menuStream << "PAUSED!";
		_frameCount++;

		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Red);

	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	SpriteBatch::EndDraw(); // Ends Drawing
}