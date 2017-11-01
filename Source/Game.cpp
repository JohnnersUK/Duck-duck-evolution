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
	toggleFPS();

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

	player.drawPlayer(renderer.get());
	pickup.drawPickup(renderer.get());
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
*	Stores last pos, moves to new pos, updates new pos
*/
void SnakeGame::updateSnakeBody()
{
	int length = player.getLength();
	snake_body[0]->last_pos[0] = snake_body[0]->body_sprite->position[0];
	snake_body[0]->last_pos[1] = snake_body[0]->body_sprite->position[1];
	snake_body[0]->body_sprite->position[0] = new_pos[0];
	snake_body[0]->body_sprite->position[1] = new_pos[1];
	if (length > 1)
	{
		for (int x = 1; x < length; x++)
		{
			snake_body[x]->last_pos[0] = snake_body[x]->body_sprite->position[0];
			snake_body[x]->last_pos[1] = snake_body[x]->body_sprite->position[1];
			snake_body[x]->body_sprite->position[0] = snake_body[(x - 1)]->last_pos[0];
			snake_body[x]->body_sprite->position[1] = snake_body[(x - 1)]->last_pos[1];
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
			player.player_sprite->angle = 0.0f;
		}

		if (key == ASGE::KEYS::KEY_DOWN)
		{
			game_action = GameAction::DOWN;
			player.player_sprite->angle = 3.14f;
		}

		if (key == ASGE::KEYS::KEY_LEFT)
		{
			game_action = GameAction::LEFT;
			player.player_sprite->angle = 4.71f;
		}

		if (key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::RIGHT;
			player.player_sprite->angle = 1.57f;
		}

		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_action = GameAction::SELECT;
		}
	}
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

	// gamepad input is polled
	auto& gamepad = inputs->getGamePad(0);
	if (gamepad.is_connected &&
		gamepad.buttons[1])
	{
		game_action = GameAction::EXIT;
	}

	// run the game loop
	processGameActions();

	if (game_state == GameState::PLAY)
	{
		count += 1;
		if (count == game_speed)
		{
			new_pos[0] = player.player_sprite->position[0];
			new_pos[1] = player.player_sprite->position[1];
			player.player_sprite->position[player.movment_axis] += player.direction * 64;
			if (player.getLength() > 0)
			{
				updateSnakeBody();
			}
			count = 0;
		}

		if (player.collision(pickup, snake_body))
		{
			snake_body[(player.getLength() - 1)]->drawBody(renderer.get(), new_pos);
			game_speed--;
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
	switch (menu_option)
	{
	case 0:
		renderer->renderSprite(*sprite);
		renderer->renderText("\n> Play <", 200, 375, 1.0, ASGE::COLOURS::GREEN);
		renderer->renderText("\nHelp & Options", 200, 425, 1.0, ASGE::COLOURS::DARKGREEN);
		renderer->renderText("\nExit", 200, 475, 1.0, ASGE::COLOURS::DARKGREEN);
		break;
	case 1:
		renderer->renderSprite(*sprite);
		renderer->renderText("\nPlay", 200, 375, 1.0, ASGE::COLOURS::DARKGREEN);
		renderer->renderText("\n> Help & Options <", 200, 425, 1.0, ASGE::COLOURS::GREEN);
		renderer->renderText("\nExit", 200, 475, 1.0, ASGE::COLOURS::DARKGREEN);
		break;
	case 2:
		renderer->renderSprite(*sprite);
		renderer->renderText("\nPlay", 200, 375, 1.0, ASGE::COLOURS::DARKGREEN);
		renderer->renderText("\nHelp & Options", 200, 425, 1.0, ASGE::COLOURS::DARKGREEN);
		renderer->renderText("\n> Plz no <", 200, 475, 1.0, ASGE::COLOURS::GREEN);
		break;
	}
	return;
}

void SnakeGame::renderPlay()
{
	//TODO: Make the game display the users score
	renderer->renderSprite(*sprite);
	renderer->renderSprite(*player.player_sprite);
	renderer->renderSprite(*pickup.pickup_sprite);

	for (int x = 0; x < player.getLength(); x++)
	{
		renderer->renderSprite(*snake_body[x]->body_sprite);
	}
}

void SnakeGame::renderGameOver()
{
	renderer->renderSprite(*sprite);
	renderer->renderText("\nRipperoni", 375, 525, 1.0, ASGE::COLOURS::DARKGREEN);
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
	renderer->setFont(GameFont::fonts[0]->id);

	switch (game_state)
	{
	case GameState::MAIN:
		renderMain();
		break;
	case GameState::PLAY:
		renderPlay();
		break;
	case GameState::GAMEOVER:
		renderGameOver();
		break;
	}
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
		if (game_action == GameAction::EXIT)
		{
			this->exit = true;
		}

		if (game_action == GameAction::UP)
		{
			menu_option --;
			if (menu_option < 0)
			{
				menu_option = 0;
			}
		}

		if (game_action == GameAction::DOWN)
		{
			menu_option ++;
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
				game_state = GameState::PLAY;
				if (!sprite->loadTexture("..\\..\\Resources\\Textures\\Background.png"))
				{
					break;
				}
				break;
			case 1: 
				break;
			case 2:
				this->exit = true;
				break;
			}
		}
		break;

	case GameState::PLAY:

		if (game_action == GameAction::EXIT)
		{
			game_state = GameState::PAUSE;
		}

		if (game_action == GameAction::UP)
		{
			if (!(player.movment_axis == 1 && player.direction == 1))
			{
				player.movment_axis = 1;
				player.direction = -1;
			}
		}

		if (game_action == GameAction::DOWN)
		{
			if (!(player.movment_axis == 1 && player.direction == -1))
			{
				player.movment_axis = 1;
				player.direction = 1;
			}
		}

		if (game_action == GameAction::LEFT)
		{
			if (!(player.movment_axis == 0 && player.direction == 1))
			{
				player.movment_axis = 0;
				player.direction = -1;
			}
		}

		if (game_action == GameAction::RIGHT)
		{
			if (!(player.movment_axis == 0 && player.direction == -1))
			{
				player.movment_axis = 0;
				player.direction = 1;
			}
		}
	case GameState::PAUSE:
		if (game_action == GameAction::EXIT)
		{
			game_state = GameState::PLAY;
		}
		break;
	case GameState::GAMEOVER:
		if (game_action == GameAction::SELECT)
		{
			/* TODO: this
			snake_body.reset();
			*/
			game_speed = 30;
			pickup.reset();
			player.reset();
			if (!sprite->loadTexture("..\\..\\Resources\\Textures\\snake-1200x627.png"))
			{
				break;
			}
			game_state = GameState::MAIN;
		}
		break;
	}

	game_action = GameAction::NONE;
}