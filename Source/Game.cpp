#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <string>

#include "Actions.h"
#include "GameState.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Player.h"
#include "Pickup.h"


/**
*   @brief   Default Constructor.
*/
SnakeGame::SnakeGame()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
SnakeGame::~SnakeGame()
{
	this->inputs->unregisterCallback(callback_id);

	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool SnakeGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Snake - Game 2");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	//toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(ASGE::EventType::E_KEY, &SnakeGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Monkey.ttf", 42), "default", 42);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}
	// load snake background sprite
	sprite = renderer->createRawSprite();
	sprite->position[0] = 0;
	sprite->position[1] = 0;

	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\snake-1200x627.png"))
	{
		return false;
	}

	pause = renderer->createRawSprite();
	pause->position[0] = 320;
	pause->position[1] = 126;

	if (!pause->loadTexture("..\\..\\Resources\\Textures\\pause.png"))
	{
		return false;
	}

	player.drawSprite(renderer.get(), new_pos);
	pickup.drawPickup(renderer.get());
	menu_option = 1;

	snake_body = new Body[1];
	temp_body = new Body[1];

	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool SnakeGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}


/*
*	Updates the snakes body one chunk at a time
*	Stores last pos, moves to last pos of body infront
*/
void SnakeGame::updateSnakeBody()
{
	int length = player.getLength();

	snake_body[0].last_pos[0] = snake_body[0].sprite->position[0];
	snake_body[0].last_pos[1] = snake_body[0].sprite->position[1];

	snake_body[0].sprite->position[0] = new_pos[0];
	snake_body[0].sprite->position[1] = new_pos[1];

	if (length > 1)
	{
		for (int x = 1; x < length; x++)
		{
			snake_body[x].last_pos[0] = snake_body[x].sprite->position[0];
			snake_body[x].last_pos[1] = snake_body[x].sprite->position[1];
			snake_body[x].sprite->position[0] = snake_body[(x - 1)].last_pos[0];
			snake_body[x].sprite->position[1] = snake_body[(x - 1)].last_pos[1];
		}
	}
}


/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void SnakeGame::input(ASGE::SharedEventData data) const
{
	auto key_event = static_cast<ASGE::KeyEvent*>(data.get());
	auto action = key_event->action;
	auto key = key_event->key;

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}

		if (key == ASGE::KEYS::KEY_UP)
		{
			game_action = GameAction::UP;
		}

		if (key == ASGE::KEYS::KEY_DOWN)
		{
			game_action = GameAction::DOWN;

		}

		if (key == ASGE::KEYS::KEY_LEFT)
		{
			game_action = GameAction::LEFT;
		}

		if (key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::RIGHT;
		}

		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_action = GameAction::SELECT;
		}
	}
}


/*
*	Sets a new position for the pickup
*	Randoms 2 new x and y values and multiplies them by 64 (To stick them on the grid)
*	Checks this new position dosen't collide with the duck pond or snake body
*	Sets the pickup position to these new values
*/
void SnakeGame::setPickupPos()
{
	int new_x;
	int new_y;
	bool valid_pos;

	do
	{
		valid_pos = true;

		new_x = rand() % 19;
		new_y = rand() % 10;

		if (player.getLength() > 0)
		{
			for (int x = 0; x < player.getLength(); x++)
			{
				if (new_x == (snake_body[x].sprite->position[0]/64) && new_y == (snake_body[x].sprite->position[1]/64))
				{
					valid_pos = false;
				}
			}
		}
	} while (new_x > 1024 && new_y > 512 && valid_pos);

	pickup.pickup_sprite->position[0] = (new_x * 64);
	pickup.pickup_sprite->position[1] = (new_y * 64);
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return void
*/
void SnakeGame::update(const ASGE::GameTime & time)
{

	// Geting gamepad input (!NOT TESTED!)
	auto& gamepad = inputs->getGamePad(0);
	if (gamepad.is_connected)
	{
		if (gamepad.buttons[12])
		{
			game_action = GameAction::UP;
		}
		else if (gamepad.buttons[13])
		{
			game_action = GameAction::LEFT;
		}
		else if (gamepad.buttons[14])
		{
			game_action = GameAction::RIGHT;
		}
		else if (gamepad.buttons[15])
		{
			game_action = GameAction::DOWN;
		}
		else if (gamepad.buttons[0] || gamepad.buttons[1] || gamepad.buttons[2] || gamepad.buttons[3])
		{
			game_action = GameAction::SELECT;
		}
		else if (gamepad.buttons[9])
		{
			game_action = GameAction::EXIT;
		}
	}


	// run the game loop
	processGameActions();

	if (game_state == GameState::PLAY)
	{
		count += time.delta_time.count() * 00.1;

		if (count >= game_speed)
		{
			new_pos[0] = player.sprite->position[0];
			new_pos[1] = player.sprite->position[1];

			player.sprite->position[player.movment_axis] += player.direction * 64;

			if (player.getLength() > 0)
			{
				updateSnakeBody();
			}

			/*
			*	If the player.collison function returns true, they have hit a pickup
			*	therefore the game needs to draw the new body sprite
			*	and modify the game speed
			*/
			if (player.collision(pickup, snake_body, game_speed))
			{
				/*
				*	Filling a temoprary array with the contents of snake_body
				*	Expanding snake_body
				*	Refilling snake_body
				*/
				temp_body = new Body[int(player.getLength())];

				for (int i = 0; i < player.getLength(); i++)
				{
					temp_body[i] = snake_body[i];
				}

				snake_body = new Body[int(player.getLength())];

				for (int i = 0; i < player.getLength(); i++)
				{
					snake_body[i] = temp_body[i];
				}

				snake_body[(player.getLength() - 1)].drawSprite(renderer.get(), new_pos);
				setPickupPos();

				if (game_speed > 1)
				{
					game_speed--;
				}

				delete[] temp_body;
				temp_body = nullptr;
			}
			count = 0;
		}


	}
	// should we terminate the game?
	if (shouldExit())
	{
		signalExit();
	}
}


void SnakeGame::renderMain()
{
	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\snake-1200x627.png"))
	{
		return;
	}

	switch (menu_option)
	{
		case 0:
		{
			renderer->renderSprite(*sprite);
			renderer->renderText("\n> Play <", 100, 335, 1.0, ASGE::COLOURS::BROWN);
			renderer->renderText("\nHelp", 100, 385, 1.0, ASGE::COLOURS::DARKGREEN);
			renderer->renderText("\nExit", 100, 435, 1.0, ASGE::COLOURS::DARKGREEN);
			break;
		}

		case 1:
		{
			renderer->renderSprite(*sprite);
			renderer->renderText("\nPlay", 100, 335, 1.0, ASGE::COLOURS::DARKGREEN);
			renderer->renderText("\n> Help <", 100, 385, 1.0, ASGE::COLOURS::BROWN);
			renderer->renderText("\nExit", 100, 435, 1.0, ASGE::COLOURS::DARKGREEN);
			break;
		}

		case 2:
		{
			renderer->renderSprite(*sprite);
			renderer->renderText("\nPlay", 100, 335, 1.0, ASGE::COLOURS::DARKGREEN);
			renderer->renderText("\nHelp", 100, 385, 1.0, ASGE::COLOURS::DARKGREEN);
			renderer->renderText("\n> Plz no <", 100, 435, 1.0, ASGE::COLOURS::BROWN);
			break;
		}
	}

	return;
}


void SnakeGame::renderHelp()
{
	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\Help.png"))
	{
		return;
	}
	renderer->renderSprite(*sprite);

	return;
}


void SnakeGame::renderPlay()
{
	int score = player.getScore();
	std::string score_string = "\nScore: " + std::to_string(score);
	const char *score_const = score_string.c_str();

	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\Background.png"))
	{
		return;
	}
	renderer->renderSprite(*sprite);
	renderer->renderSprite(*player.sprite);
	renderer->renderSprite(*pickup.pickup_sprite);

	for (int x = 0; x < player.getLength(); x++)
	{
		renderer->renderSprite(*snake_body[x].sprite);
	}

	renderer->renderText(score_const, 15, 640, 1.0, ASGE::COLOURS::BLACK);

	return;
}


void SnakeGame::renderPause()
{
	int score = player.getScore();
	std::string score_string = "\nScore: " + std::to_string(score);
	const char *score_const = score_string.c_str();

	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\Background.png"))
	{
		return;
	}

	renderer->renderSprite(*sprite);
	renderer->renderSprite(*player.sprite);
	renderer->renderSprite(*pickup.pickup_sprite);

	for (int x = 0; x < player.getLength(); x++)
	{
		renderer->renderSprite(*snake_body[x].sprite);
	}

	renderer->renderSprite(*pause);
	renderer->renderText(score_const, 560, 290, 1.0, ASGE::COLOURS::BLACK);


	return;
}


void SnakeGame::renderGameOver()
{
	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\GameOver.png"))
	{
		return;
	}

	int score = player.getScore();
	std::string score_string = "\nYou scored: " + std::to_string(score);
	const char *score_const = score_string.c_str();

	renderer->renderSprite(*sprite);
	renderer->renderText(score_const, 375, 325, 1.0, ASGE::COLOURS::BROWN);
	renderer->renderText("\nEnter to continue", 375, 525, 1.0, ASGE::COLOURS::DARKGREEN);

	return;
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
			 Once the current frame is has finished the buffers are 
			 swapped accordingly and the image shown.
*   @return  void
*/
void SnakeGame::render(const ASGE::GameTime &)
{
	renderer->renderSprite(*sprite);
	renderer->setFont(GameFont::fonts[0]->id);

	switch (game_state)
	{
		case GameState::MAIN:
		{
			renderMain();
			break;
		}

		case GameState::HELP:
		{
			renderHelp();
			break;
		}

		case GameState::PLAY:
		{
			renderPlay();
			break;
		}

		case GameState::PAUSE:
		{
			renderPause();
			break;
		}

		case GameState::GAMEOVER:
		{
			renderGameOver();
			break;
		}
	}

	return;
}


/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void SnakeGame::processGameActions()
{
	switch (game_state)
	{
		case GameState::MAIN:
		{
			if (game_action == GameAction::EXIT)
			{
				this->exit = true;
			}

			if (game_action == GameAction::UP)
			{
				menu_option--;
				if (menu_option < 0)
				{
					menu_option = 0;
				}
			}

			if (game_action == GameAction::DOWN)
			{
				menu_option++;
				if (menu_option > 2)
				{
					menu_option = 2;
				}
			}

			if (game_action == GameAction::SELECT)
			{
				switch (menu_option)
				{
					case 0:
					{
						game_state = GameState::PLAY;
						break;
					}

					case 1:
					{
						game_state = GameState::HELP;
						break;
					}

					case 2:
					{
						this->exit = true;
						break;
					}
				}
			}
			break;
		}


		case GameState::PLAY:
		{

			if (game_action == GameAction::EXIT)
			{
				game_state = GameState::PAUSE;
			}

			if (game_action == GameAction::UP)
			{
				if (!(new_pos[1] < player.sprite->position[1]))
				{
					player.sprite->angle = 0.0f;
					player.movment_axis = 1;
					player.direction = -1;
				}
			}

			if (game_action == GameAction::DOWN)
			{
				if (!(new_pos[1] > player.sprite->position[1]))
				{
					player.sprite->angle = 3.14f;
					player.movment_axis = 1;
					player.direction = 1;
				}
			}

			if (game_action == GameAction::LEFT)
			{
				if (!(new_pos[0] < player.sprite->position[0]))
				{
					player.sprite->angle = 4.71f;
					player.movment_axis = 0;
					player.direction = -1;
				}
			}

			if (game_action == GameAction::RIGHT)
			{
				if (!(new_pos[0] > player.sprite->position[0]))
				{
					player.sprite->angle = 1.57f;
					player.movment_axis = 0;
					player.direction = 1;
				}
			}

			break;
		}

		case GameState::HELP:
		{
			if (game_action == GameAction::SELECT)
			{
				game_state = GameState::MAIN;
				menu_option = 1;
			}
			break;
		}

		case GameState::PAUSE:
		{
			if (game_action == GameAction::EXIT)
			{
				game_state = GameState::PLAY;
			}
			break;
		}

		case GameState::GAMEOVER:
		{
			if (game_action == GameAction::SELECT)
			{
				game_speed = 30;

				pickup.reset();
				player.reset();

				game_state = GameState::MAIN;
				menu_option = 1;
			}

			break;
		}
	}
	
	game_action = GameAction::NONE;

	return;
}